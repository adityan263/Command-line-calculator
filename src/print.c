
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

#ifndef __PRINT_H__
#include "print.h"
#endif


void printans(num ans, int lflag, int dflag, int error, int stackfull) {
	if(ans.var == 1) {
		ans.var = 0;
		/*if number is a varible then get its value stored in variable array*/
		if(ans.v >= 'a' && ans.v <= 'z') {
			strcpy(ans.bd, variable[ans.v - 'a'].bd);
			ans.bi = variable[ans.v - 'a'].bi;
			ans.sign = variable[ans.v - 'a'].sign;
			strcpy(ans.ad, variable[ans.v - 'a'].ad);
			ans.ai = variable[ans.v - 'a'].ai;
			ans.alimit = variable[ans.v - 'a'].alimit;
			ans.blimit = variable[ans.v - 'a'].blimit;
		}
		else if(ans.v >= 'G' && ans.v <= 'Z') {
			strcpy(ans.bd, variable[ans.v - 'G' + 26].bd);
			ans.bi = variable[ans.v - 'G' + 26].bi;
			ans.sign = variable[ans.v - 'G' + 26].sign;
			strcpy(ans.ad, variable[ans.v - 'G' + 26].ad);
			ans.ai = variable[ans.v - 'G' + 26].ai;
			ans.alimit = variable[ans.v - 'G' + 26].alimit;
			ans.blimit = variable[ans.v - 'G' + 26].blimit;
		}
		else
			error = 1;
	}
	if(error == 1) {
		if(stackfull == 1) {
			fprintf(stderr, "exprression is too long ... stack is full\n");
			stackfull = 0;
		}
		else
			fprintf(stderr, "Error in expression\n");
	}
	else {
		ans = rmz(ans);
		ans = rmza(ans);
		if(ans.sign == 1) 
			printf("-");
		if(ans.bi == 0)
			printf("0");
		if((dflag == 1 || lflag == 1) && (ans.ai != 0)) {
			printf("%s.%s\n", ans.bd, ans.ad);
		}	
		else {
			puts(ans.bd);				
		}
	}
	dflag = 0;
	free(ans.ad);
	free(ans.bd);
	
}
void printusage() {
	printf("usage:  ./project  [option] [filename]\n\noption\tdescription\n-l    \ttrigonometric, log, ln and e^(expression) options\n-h    \thelp and exit\n--help\thelp and exit\n");
}
