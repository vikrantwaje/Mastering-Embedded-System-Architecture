/* Freescale Semiconductor Inc.
 *
 * mbed Microcontroller Library
 * (c) Copyright 2009-2012 ARM Limited.
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

#ifndef TSISENSOR_H
#define TSISENSOR_H

/**
* TSISensor example
*
* @code
* #include "mbed.h"
* #include "TSISensor.h"
*
* int main(void) {
*    DigitalOut led(LED_GREEN);
*    TSIElectrode elec0(9);
*    TSIElectrode elec1(10);
*    TSIAnalogSlider tsi(elec0, elec1, 40);
*
*    while (true) {
*        printf("slider percentage: %f%\r\n", tsi.readPercentage());
*        printf("slider distance: %dmm\r\n", tsi.readDistance());
*        wait(1);
*        led = !led;
*    }
* }
* @endcode
*/
#define NO_TOUCH 0

/** TSI Electrode with simple data required for touch detection.
 */
class TSIElectrode {
public:
    /** Initialize electrode.
     */
    TSIElectrode(PinName pin) : _threshold(100) {
        _channel = getTSIChannel(pin);
    }

    /** Initialize electrode.
     */
    TSIElectrode(uint32_t tsi_channel) : _threshold(100) {
        _channel = (uint8_t)tsi_channel;
    }
    /** Set baseline.
     */
    void setBaseline(uint32_t baseline) {
        _baseline = (uint16_t)baseline;
    }
    /** Set threshold.
     */
    void setThreshold(uint32_t threshold) {
        _threshold = (uint16_t)threshold;
    }
    /** Set signal.
     */
    void setSignal(uint32_t signal) {
        _signal = (uint16_t)signal;
    }
    /** Get baseline.
     */
    uint32_t getBaseline() {
        return _baseline;
    }
    /** Get delta.
     */
    uint32_t getDelta() {
        int32_t delta = getSignal() - getBaseline();
        if (delta < 0) {
            return 0;
        } else {
            return delta;
        }
    }
    /** Get signal.
     */
    uint32_t getSignal() {
        return _signal;
    }
    /** Get threshold.
     */
    uint32_t getThreshold() {
        return _threshold;
    }
    /** Get channel.
     */
    uint32_t getChannel() {
        return _channel;
    }
    /** Get TSI Channel for PinName.
     *
     * @returns TSI channel ID for use in constructor of TSIAnalogSlider and TSIElectrode.
     * @throws compile-time error if target is not supported, or runtime error if pin does not match any channel.
     */
    static uint8_t getTSIChannel(PinName pin) {
#if   defined(TARGET_KL25Z) || defined(TARGET_KL46Z) || defined (TARGET_KL05Z)       
        switch(pin) {
            //these are 
            case PTA0: return 1;
            case PTA1: return 2;
            case PTA2: return 3;
            case PTA3: return 4;
            case PTA4: return 5;
            case PTB0: return 0;
            case PTB1: return 6;
            case PTB2: return 7;
            case PTB3: return 8;
            case PTB16: return 9;
            case PTB17: return 10;
            case PTB18: return 11;
            case PTB19: return 12;
#if   defined(TARGET_KL25Z) || defined(TARGET_KL46Z)
            case PTC0: return 13;
            case PTC1: return 14;
            case PTC2: return 15;
#endif
            default: error("PinName provided to TSIElectrode::getTSIChannel() does not correspond to any known TSI channel.");
        }
# else
    #error "Unknown target for TSIElectrode::getTSIChannel() - only supports KL25Z so far."
# endif   
        return 0xFF; //should never get here
    }
    
private:
    uint8_t  _channel;
    uint16_t _signal;
    uint16_t _baseline;
    uint16_t _threshold;
};

/** Analog slider which consists of two electrodes.
 */
class TSIAnalogSlider {
public:
    /**
     *
     *   Initialize the TSI Touch Sensor with the given PinNames
     */
    TSIAnalogSlider(PinName elec0, PinName elec1, uint32_t range);
    /**
     *   Initialize the TSI Touch Sensor
     */
    TSIAnalogSlider(uint32_t elec0, uint32_t elec1, uint32_t range);
    /**
     * Read Touch Sensor percentage value
     *
     * @returns percentage value between [0 ... 1]
     */
    float readPercentage();
    /**
     * Read Touch Sensor distance
     *
     * @returns distance in mm. The value is between [0 ... _range]
     */
    uint32_t readDistance();
    /** Get current electrode.
     */
    TSIElectrode* getCurrentElectrode() {
        return _current_elec;
    }
    /** Set current electrode which is being measured.
     */
    void setCurrentElectrode(TSIElectrode *elec){
        _current_elec = elec;
    }
    /** Get next electrode.
     */
    TSIElectrode* getNextElectrode(TSIElectrode* electrode) {
        if (electrode->getChannel() == _elec0.getChannel()) {
            return &_elec1;
        } else {
            return &_elec0;
        }
    }
    /** Return absolute distance position.
     */
    uint32_t getAbsoluteDistance() {
        return  _absolute_distance_pos;
    }
    /** Return absolute precentage position.
     */
    uint32_t getAbsolutePosition() {
        return _absolute_percentage_pos;
    }
    /** Set value to the scan in progress flag.
     */
    void setScan(uint32_t scan) {
        _scan_in_progress = scan;
    }
    /** Return instance to Analog slider. Used in tsi irq.
     */
    static TSIAnalogSlider *getInstance() {
        return _instance;
    }
private:
    void initObject(void); //shared constructor code
    void sliderRead(void);
    void selfCalibration(void);
    void setSliderPercPosition(uint32_t elec_num, uint32_t position) {
        _percentage_position[elec_num] = position;
    }
    void setSliderDisPosition(uint32_t elec_num, uint32_t position) {
        _distance_position[elec_num] = position;
    }
    void setAbsolutePosition(uint32_t position) {
        _absolute_percentage_pos = position;
    }
    void setAbsoluteDistance(uint32_t distance) {
        _absolute_distance_pos = distance;
    }
private:
    TSIElectrode  _elec0;
    TSIElectrode  _elec1;
    uint8_t       _scan_in_progress;
    TSIElectrode* _current_elec;
    uint8_t       _percentage_position[2];
    uint8_t       _distance_position[2];
    uint32_t      _absolute_percentage_pos;
    uint32_t      _absolute_distance_pos;
    uint8_t       _range;
protected:
    static TSIAnalogSlider *_instance;
};

#endif
