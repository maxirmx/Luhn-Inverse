/**
*  Test program for generalized Luhn algorith
*/

#include <string.h>
#include <stdio.h>

#include "luhn_inversed.h"
#include "luhn-check.h"


/**
*   function process_PAN
*
*   Runs tests for a single PAN
*/
void process_PAN(char * PAN)
{
	int  chk, j;

	printf("Processing PAN: %20s\tLuhn check: %s\n", PAN, (chk = luhn_check(PAN)) ? "passed" : "not passed");
	if (!chk)
	{
		char acc[17];
		char altd;
		for (j = 0; j < strlen(PAN)-1; j++)
		{
			printf("    Altering at position %d\t", j);
			altd = luhn_inversed(PAN, j);
			if (altd < 0) printf("\n         %25s\n", error_message(altd));
			else
			{
				strcpy(acc, PAN);
				acc[j] = altd;
				printf("\n         Altered PAN: %25s\tLuhn check: %s\n", acc, (chk = luhn_check(acc)) ? "passed" : "not passed");
			}
		}
	}
}

/**
*   function main
*
*   Test program for generalized Luhn algoritm 
*/
int main(int argc, char ** argv)
{
	char* cc[] =
	{
		"1234567812345678",       /* 15 digits PAN + check digit */
		"123456781234560",        /* 14 digits PAN + check digit */
		0
	};

	if (argc < 2 || strcmp(argv[1], "help") == 0)
	{
		printf("Generalized Luhn algorith test program.\n"
			"   Usage: luhn help | hardcoded | <PAN> [ <PAN> ...)\n"
			"          help - outputs this message\n"
			"          hardcoded - executes generalized luhn for all positions\n"
			"                      for two hardcoded strings\n"
			"          <PAN> [<PAN> ...] - executes generalized luhn for all positions\n" 
			"                              for the strings supplied\n"
			"                              PANs are supposed to be 14 or 15 digits\n" 
			"                              plus check digit in trailing position\n");

		return 0;
	}


	int i;

	if (strcmp(argv[1], "builtin") == 0)
	{
		for (i = 0; cc[i]; i++)
		{
			process_PAN(cc[i]);
		}
		return 0;
	}

	for (i = 1; i<argc; i++)
	{
		size_t l = strlen(argv[i]);
		if (l < 15 || l > 16) printf("Skipping %s  -- PAN shall be 14 or 15 digits + check digit\n", argv[i]);
		else process_PAN(argv[i]);
	}

	return 0;
}