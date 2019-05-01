
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

#ifndef __EVALUATE_H__
#define __EVALUATE_H__

#include "stack.h"
#include "numbers.h"
#include "input.h"
#include "basic_operations.h"


/*46 variables (a to z) and (G to Z)*/
num variable[46];

/*Deafault value of all variables is set to 0*/
void initvar();

/*does all operations*/
num solve(char op, num x, num y, int lflag, int *error);

num infixeval(char *str, int lflag, int *dflag, int *error, int *stackfull);

#endif
