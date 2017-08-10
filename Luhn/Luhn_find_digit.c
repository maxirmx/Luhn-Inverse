/**
*  Implementation of inversed Luhn algorith
*/

#include "luhn_inversed.h"


/**
 *  Inversed Luhn algorith:
 *    Input: 
 *       - PAN, including trailing check digit
 *       - position of the digit to alter in order to conform to Luhn check
 *    Algorithm:
 *       1. Reverse the order of PAN.
 *       2. Assume the digit in the position to alter is equal to '0' and calculate the sum of:
 *          - digits in odd positions in the reversed PAN
 *          - sum of digits of the original digits in the even positions of inversed PAN multiplied by 2
 *       3. Digit in the position to alter is:
 *          - if the last digit in the sum is 0, then 0, otherwise:
 *            - if position is odd in the inversed PAN, then 10 - (last digit in the sum), otherwise: 
 *              - if last digit of the sum is odd the problem cannot be solved, otherwise:
 *               - (10 - (last digit in the sum))/2 
 *   
 *    Output:  The new digit for altered position or error code
 *
 */

 /**
 *   function luhn_inversed  implements algorithm as described above for fixed length PAN (14 or 15 digits)
 *   Variable length is not a problem but will add an extra call to strlen
 *
 *   @param const char cc[16] - PAN to process with check digit in the trailing position
 *                              If it is 14 digits PAN char[15] shall be 0
 *   @param unsigned int position - position of the digit to alter
 *                                  It is "c-style" position, i.e.: the first byte is at position 0 
 *   @return - char - new digit at altered position 
 *                    or error code:
 *                       E_LUHN_ERROR_POSITION -1  -- position is outside of the PAN               
 *                       E_LUHN_ERROR_PROBLEM  -2  -- the problem cannot be solved
 *                       E_LUHN_ERROR_DIGIT    -3  -- invalid digit
 */


#define  E_LUHN_ERROR_POSITION   -1  
#define  E_LUHN_ERROR_PROBLEM    -2  
#define  E_LUHN_ERROR_DIGIT      -3  


char luhn_inversed(const char cc[16], unsigned int position)
{
/**
 *   m provides for table based calculation for the digits in even positions in the inversed PAN:
 *    - Take the digit
 *    - Multiply by 2
 *    - If result is larger then sum digits of the result
 *
 *   Following Rosetta code it is calculated modulo 10 here
 */
	const int m[] = { 0,2,4,6,8,1,3,5,7,9 };				

/**
 *   m_inversed provides for table based calculation for the digits in even positions in inversed PAN:
 *     - if last digit of the sum is odd the problem cannot be solved, otherwise:
 *          - (10 - (last digit in the sum))/2
 */

	const char m_inversed[] = { 0 + '0', E_LUHN_ERROR_PROBLEM, 
		                        1 + '0', E_LUHN_ERROR_PROBLEM,
		                        2 + '0', E_LUHN_ERROR_PROBLEM,
		                        3 + '0', E_LUHN_ERROR_PROBLEM,
		                        4 + '0', E_LUHN_ERROR_PROBLEM };

	unsigned int i = 16,         /* Position in the PAN being processed */
		         sum = 0;        /* Sum                                 */
	int odd = 1,                 /* Whether the current position is odd in inversed PAN */
		position_odd;            /* Whether the altered position is odd in inversed PAN */

/**
 * Check for trailing 0, if so it is 14-digits PAN
 */
	if (!cc[i-1]) i--;

/**
 * Check that position is good enough 
 * We assume that Luhn check digit cannot be altered though nothing in the algorithm prevents it
 * 
 * Of course this check can be skipped for speed
 */
	if (position > i-2) return E_LUHN_ERROR_POSITION;


	for (; i--; odd = !odd)
	{
		if (i == position) position_odd = odd;
		else
		{
			unsigned int digit = cc[i] - '0';
/**
 * Of course this check can be skipped for speed
 */
			if (digit > 9) return E_LUHN_ERROR_DIGIT;
			sum += odd ? digit : m[digit];
		}
	}

/**
 *   https://en.wikipedia.org/wiki/Luhn_algorithm#Description   
 *   ( I am not that clever)
 *	
 *	(sum * 9) % 10 is better comparing to 10 - sum % 10 because 
 * 	the last requires special handling of the case when sum % 10 == 0
 */
	return position_odd ? '0' + (sum * 9) % 10 : m_inversed[(sum * 9) % 10];
}


/**
*   function error_message  small helper to improve error output
*
*   @param error_code
*   @return error message
*/
const char * error_message(char error_code)
{
	switch (error_code)
	{
	case E_LUHN_ERROR_POSITION: return "E_LUHN_ERROR_POSITION";
	case E_LUHN_ERROR_PROBLEM:  return "E_LUHN_ERROR_PROBLEM";
	case E_LUHN_ERROR_DIGIT:    return "E_LUHN_ERROR_DIGIT";
	}
	return "This cannot happen";
}

