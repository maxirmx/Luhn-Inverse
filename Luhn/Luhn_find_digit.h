#pragma once

/**
*   function luhn_inversed  implements inversed Luhn algorithm for fixed length PAN (14 or 15 digits)
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
*
*    More details @ Luhn.c
*/


#define  E_LUHN_ERROR_POSITION   -1  
#define  E_LUHN_ERROR_PROBLEM    -2  
#define  E_LUHN_ERROR_DIGIT      -3  

char luhn_inversed(const char cc[16], unsigned int position);

/**
*   function error_message  small helper to improve error output
*
*   @param error_code
*   @return error message
*/
const char * error_message(char error_code);