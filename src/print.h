
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define __PRINT_H__

#ifndef __STACK_H__
#include "stack.h"
#endif

#ifndef __NUMBERS_H__
#include "numbers.h"
#endif

#ifndef __INPUT_H__
#include "input.h"
#endif


extern num variable[46];

void printans(num ans, int lflag, int dflag, int error, int stackfull);

void printusage();
