
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

#define MAX 128

/*struct that stores all numbers
 *bd => digits before decimal  are stored
 *ad => digits after decimal are stored
 *v => if it is a varible then it stored variable character else '\0'
 *bi, ai => no. of digits before and after decimal
 *sign = 1 =>negative | sign = 0 =>positive
 *blimit, alimit => max no. of digits it can store
 *var = 1 =>it is a variable 
 */
typedef struct num{
	char *bd, *ad, v;
	int bi, ai, sign, blimit, alimit, var;
}num;

/*stack of operands*/
typedef struct stacki {
	num a[MAX];
	int i;
}stacki;


num initnum(num n);
num breinitnum(num n);
num areinitnum(num n);


void pushi(stacki *s, num numb);
num popi(stacki *s);
int emptyi(stacki *s);
int fulli(stacki *s);
void initi(stacki *s);

/*stac of operators*/
typedef struct stackc {
	char b[MAX];
	int j;
}stackc;


void pushc(stackc *s, char op);
char popc(stackc *s);
int emptyc(stackc *s);
int fullc(stackc *s);
void initc(stackc *s);
