/*
 * error.c
 *
 *  Created on: Sep 28, 2010
 *      Author: Lee
 */
#include "error.h"

enum errors programErrors;

void address_claim_error()
{
	programErrors |= ADDRESS_CLAIM_ERROR;
	// go to CAN listen only mode.
}
