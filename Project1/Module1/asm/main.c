/**
* @file squareroot.c
* @brief This source file basically contains a c program to compute squareroot; an assembly language call is been made to compute the square root
*
* @author Vikrant Waje and Preshit Harlikar
*
* @date 09/25/2017
*/


 
#include<stdio.h>


/**
 * @brief This function computes the squareroot of any number
 * @param num:This basically is the number whose squarerrot is to be computed
 * 
 */

 void squareroot(int num);

/**@briefThe main function starts here*/
 int main(void){

 squareroot(22);
 }


/**
 * @brief The assembly language function named squareroot computes squareroot of num which was passed via main function
 * 
 * 
 */
 __asm void squareroot(int num){
	///
			MOVS R4,#0
	/**value of a ,that is the lowerbound*/
			MOVS R1,#0
	/**value of maximum number upto which squareroot can be obtained*/
			MOVS R2,#65536
	/**value of c ,that is the variable in which average is stored*/
			MOVS R3,#0
	/**Maximum number of iterations to be done*/
			MOVS R7,#20
	 
UP	/** Take backup*/
			MOVS R5,R3
	/**Generate average*/
			ADDS R3,R1,R2
	/**Division by 2*/
			LSRS R3,R3,#1
	/**Take backup in R6*/
			MOVS R6,R3
	/**Multiply value of c to compute square*/
			MULS R6,R3,R6
	/**Check for bounds*/
			CMP R6,R0
	/**Branch to elseif*/
			BNE ELSEIF
	/** Set done bit to 1*/
			MOVS R4,#1
	/**Branch to last*/
			B LAST
ELSEIF	
	
			CMP R0,R6
			BLT ELSE
	/** Move value of cold as lowerbound*/
			MOVS R1,R3
	/**Branch to last*/
			B LAST
ELSE
			MOVS R2,R3
LAST	/**reduce the number of iteration by 1*/
			SUBS R7,R7,#1
	/**If iterations are reduced to zero then exit*/
			CMP R7,#0

			BEQ RETURN
	/**Check whether value of c is 1*/
			CMP R4,#1
			BNE UP
	/**Check whether done bit is 1 and c =cold*/
			CMP R3,R5
			BNE UP
			
			
RETURN/**Move value to R as it is return value*/
			MOV R0,R3
	/**Return Value of R0*/
			BX LR
 
 }


