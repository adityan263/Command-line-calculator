
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

#include <stdlib.h>
#include "numbers.h"

/*set initial value of number to zero and malloc memory for number*/
num initnum(num p){
	p.bd = (char *)malloc(sizeof(char) * 30);
	p.ad = (char *)malloc(sizeof(char) * 30);
	p.sign = p.ai = p.bi = p.var = 0;
	p.blimit = p.alimit = 30;
	p.bd[0] = p.ad[0] = '\0';
	return p;
}

/*reinitiate after decimal part*/
num areinitnum(num p) {
	p.alimit += 50;
	p.ad = (char *)realloc(p.ad, sizeof(char) * p.alimit);
	return p;
}

/*reinitiate before decimal part*/
num breinitnum(num p) {
	p.blimit += 50;
	p.bd = (char *)realloc(p.bd, sizeof(char) * p.blimit);
	return p;
}

/*adz => add zero
 *adds 'i' zeros before given number
 *e.g. adz(15, 2) returns (0015)
 */
num adz(num t, int i) {
	if(i == 0)
		return t; 
	int j = t.bi;
	while(i + t.bi >= t.blimit)
		t = breinitnum(t);		/*if no. of digits exceed default limit then reinitiate bd string*/
	while(j > -1) {
		t.bd[j + i] = t.bd[j];
		j--;
	}
	j = 0;
	t.bi += i; 
	while(j < i)
		t.bd[j++] = '0';
	return t;
}

/*adza => add zero after(decimal)
 *adds 'i' zeros at end of given number
 *e.g. adza(15.23, 2) returns (15.2300)
 */
num adza(num t, int i) {
	int j = 0;
	while(i + t.ai >= t.alimit)
		t = areinitnum(t);		/*if no. of digits exceeds default limit then reinitiate ad string*/
	while(j < i)
		t.ad[t.ai + j++] = '0';
	t.ad[t.ai + i] = '\0';
	t.ai += i;
	return t;
}

/*rmz => remove zero
 *removes zeros before given number
 *e.g. adz(000015) returns 15
 */
num rmz(num t) {
	int i = 0, j = 0;
	while(t.bd[i] == '0')
		i++;
	if(i == 0)
		return t;
	while(t.bd[i + j - 1] != '\0') {
		t.bd[j] = t.bd[i + j];
		j++;
	}
	t.bi = j - 1;
	return t;
}

/*removes zeros after given number
 *e.g. adz(15.9800) returns 15.98
 */
num rmza(num t) {
	int i = t.ai - 1, j = 0;
	while(t.ad[i--] == '0')
		j++;
	if(j == 0)
		return t;
	t.ad[t.ai - j] = '\0';
	t.ai -= j;
	return t;
}
