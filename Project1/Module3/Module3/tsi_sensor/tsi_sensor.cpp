/* Freescale Semiconductor Inc.
 * mbed Microcontroller Library
 * (c) Copyright 2014 ARM Limited.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mbed.h"
#include "tsi_sensor.h"

void tsi_irq(void);
TSIAnalogSlider *TSIAnalogSlider::_instance;

TSIAnalogSlider::TSIAnalogSlider(PinName pin0, PinName pin1, uint32_t range): _elec0(pin0), _elec1(pin1), _range(range) {
    initObject();
}
TSIAnalogSlider::TSIAnalogSlider(uint32_t elec0, uint32_t elec1,
                                 uint32_t range)
: _elec0(elec0), _elec1(elec1), _range(range) {
    initObject();
}

void TSIAnalogSlider::initObject(void) {    
    _instance = this;
    _current_elec = &_elec0;
    SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;

    TSI0->GENCS |= (TSI_GENCS_ESOR_MASK | TSI_GENCS_MODE(0) | TSI_GENCS_REFCHRG(4)
                   | TSI_GENCS_DVOLT(0) | TSI_GENCS_EXTCHRG(7) | TSI_GENCS_PS(4)
                   | TSI_GENCS_NSCN(11) | TSI_GENCS_TSIIEN_MASK | TSI_GENCS_STPE_MASK);
    TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;

    NVIC_SetVector(TSI0_IRQn, (uint32_t)&tsi_irq);
    NVIC_EnableIRQ(TSI0_IRQn);

    selfCalibration();
}

static void initBaseline(TSIElectrode& elec)
{
    uint32_t channel0 = elec.getChannel();
    TSI0->DATA = ((channel0 << TSI_DATA_TSICH_SHIFT) );
    TSI0->DATA |= TSI_DATA_SWTS_MASK;
    while(!(TSI0->GENCS & TSI_GENCS_EOSF_MASK));
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
    elec.setBaseline(TSI0->DATA & TSI_DATA_TSICNT_MASK);
}

void TSIAnalogSlider::selfCalibration(void)
{
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;      // Clear End of Scan Flag
    TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module

    uint32_t trigger_backup;
    if(TSI0->GENCS & TSI_GENCS_STM_MASK) {     // Back-up TSI Trigger mode from Application
        trigger_backup = 1;
    } else {
        trigger_backup = 0;
    }

    TSI0->GENCS &= ~TSI_GENCS_STM_MASK;    // Use SW trigger
    TSI0->GENCS &= ~TSI_GENCS_TSIIEN_MASK; // Enable TSI interrupts
    TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;   // Enable TSI module

    initBaseline(_elec0);
    initBaseline(_elec1);

    TSI0->DATA = ((_elec0.getChannel() << TSI_DATA_TSICH_SHIFT));

    TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module
    TSI0->GENCS |= TSI_GENCS_TSIIEN_MASK;     // Enale TSI interrupt
    if (trigger_backup) {                     // Restore trigger mode
        TSI0->GENCS |= TSI_GENCS_STM_MASK;
    } else {
        TSI0->GENCS &= ~TSI_GENCS_STM_MASK;
    }

    TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;     // Enable TSI module
    TSI0->DATA |= TSI_DATA_SWTS_MASK;
}


void TSIAnalogSlider::sliderRead(void ) {
    if (_scan_in_progress) {
        _scan_in_progress = 0;
        uint32_t delta0 = _elec0.getDelta();
        uint32_t delta1 = _elec1.getDelta();

        if ((delta0 > _elec0.getThreshold()) || (delta1 > _elec1.getThreshold())) {
            uint32_t perc_pos0 = (delta0 * 100) / (delta0 + delta1);
            uint32_t perc_pos1 = (delta1 * 100) / (delta0 + delta1);
            setSliderPercPosition(0, perc_pos0);
            setSliderPercPosition(1, perc_pos1);
            uint32_t dist_pos0 = (perc_pos0 * _range) / 100;
            uint32_t dist_pos1 = (perc_pos1 * _range) / 100;
            setSliderDisPosition(0, dist_pos0);
            setSliderDisPosition(1, dist_pos1);

            setAbsolutePosition(((100 - perc_pos0) + perc_pos1) / 2);
            setAbsoluteDistance(((_range - dist_pos0) + dist_pos1) / 2);
        } else {
            setSliderPercPosition(0, 0);
            setSliderPercPosition(1, 0);
            setSliderDisPosition(0, 0);
            setSliderDisPosition(1, 0);
            setAbsolutePosition(0);
            setAbsoluteDistance(0);
        }
    }
}

float TSIAnalogSlider::readPercentage() {
    sliderRead();
    return (float)getAbsolutePosition() / 100.0;
}

uint32_t TSIAnalogSlider::readDistance() {
    sliderRead();
    return getAbsoluteDistance();
}

static void changeElectrode(TSIAnalogSlider *analog_slider)
{
    TSIElectrode* elec = analog_slider->getCurrentElectrode();
    uint32_t signal = (TSI0->DATA & TSI_DATA_TSICNT_MASK);
    elec->setSignal(signal);

    TSIElectrode *next_elec =  analog_slider->getNextElectrode(elec);

    analog_slider->setCurrentElectrode(next_elec);
    TSI0->DATA = ((next_elec->getChannel() << TSI_DATA_TSICH_SHIFT) );
    TSI0->DATA |= TSI_DATA_SWTS_MASK;
}


void tsi_irq(void)
{
    TSIAnalogSlider *analog_slider = TSIAnalogSlider::getInstance();
    analog_slider->setScan(1);
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK; // Clear End of Scan Flag
    changeElectrode(analog_slider);
}
