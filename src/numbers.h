
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

#define __NUMBERS_H__

/*struct that stores all numbers
 *bd => digits before decimal  are stored
 *ad => digits after decimal are stored
 *v => if it is a varible then it stored variable character else '\0'
 *bi, ai => no. of digits before and after decimal
 *sign = 1 => negative | sign = 0 =>positive
 *blimit, alimit => max no. of digits it can store
 *var = 1 => it is a variable 
 */
typedef struct num{
	char *bd, *ad, v;
	int bi, ai, sign, blimit, alimit, var;
}num;


/*set initial value of number to zero and malloc memory for number*/
num initnum(num n);

/*reinitiate after decimal part*/
num breinitnum(num n);

/*reinitiate before decimal part*/
num areinitnum(num n);

/*adz => add zero
 *adds 'i' zeros before given number
 *e.g. adz(15, 2) returns (0015)
 */
num adz(num t, int i);

/*adza => add zero after(decimal)
 *adds 'i' zeros at end of given number
 *e.g. adza(15.23, 2) returns (15.2300)
 */
num adza(num t, int i);

/*rmz => remove zero
 *removes zeros before given number
 *e.g. adz(000015) returns 15
 */
num rmz(num t);


/*removes zeros after given number
 *e.g. adz(15.9800) returns 15.98
 */
num rmza(num t);
