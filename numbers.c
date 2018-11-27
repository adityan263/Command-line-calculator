
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
#ifndef __NUMBERS_H__
#include "numbers.h"
#endif

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
