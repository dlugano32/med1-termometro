/*
 * myString.h
 *
 *  Created on: 7 dic. 2021
 *      Author: d_lugano
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_
#include "LPC845.h"

void my_revstr (uint8_t *str, uint8_t *str_r);
void my_strcat (uint8_t *destino, uint8_t *origen);
uint8_t my_strlen(uint8_t* str1);
int my_strcmp (uint8_t *str1, uint8_t *str2);

#endif /* MYSTRING_H_ */
