
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
#include <string.h>
#include <limits.h>

#define __BASIC_OPERATIONS_H__

#ifndef __NUMBERS_H__
#include "numbers.h"
#endif


num add(num, num, int, int);

num sub(num, num, int, int);

num mul(num, num, int);

num divi(num, num, int, int, int);

num mod(num, num, int, int);


/*returns variable of n * pi i.e. (3.14 * 10 ^ 37)*/
num getpi(num t);


/*in multiplication sometimes character gets too big (> 255)
 *to avoid printing unknown characters carry needs to be cleared
 */
num carryclr(num res, int k);
