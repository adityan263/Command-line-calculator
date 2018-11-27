
/*****************************************************************************
 * Copyright (C) Aditya Neralkar neralkarad15.it@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#define __INPUT_H__


#ifndef __NUMBERS_H__
#include "numbers.h"
#endif


#define OPERAND 10 
#define OPERATOR 20
#define VARIABLE 30
#define	END	40
#define ERROR	50

typedef struct token {
	int type;
	num number;
	char op;
}token;


enum states { SPC, DIG, OPR, ALPH, STOP, ERR };


/*reads line from the terminal and converts it to a string*/
int readline(char *arr);


/*converts string into tokens*/
token *getnext(char *arr, int *reset, int lflag, int *dflag);


/*assigns unique character to each operation
 *these characters are later used as operator 
 */
char operator(char *expr, int lflag);


/*returns precedence of operator*/
int precedence(char b);
