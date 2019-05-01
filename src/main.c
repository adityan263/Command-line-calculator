
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

#include "numbers.h"
#include "input.h"
#include "evaluate.h"
#include "print.h"



int main(int argc, char *argv[]) {
	char str[500], *o;
	int q = 1;
	initvar();
	num ans;
	int x, lflag = 0, dflag = 0, error = 0, stackfull = 0;
	size_t b = 128;
	ssize_t z;
	FILE *fp;
	num infixeval(char *infix, int lflag, int *dflag, int *error, int *stackfull);
	while(q < argc) {
		if((strcmp(argv[q], "-h") == 0) || (strcmp(argv[q], "--help") == 0)) {
			printusage();
			return 0;
		}
		else if(strcmp(argv[q], "-l") == 0)
			lflag = 1;
		else {
			fp = fopen(argv[q], "r");
			if(fp == NULL) {
				if(argv[q][0] == '-') {
					printf("invalid option ... '%s'\n", argv[q]);
					printusage();
					return 0;
				}
				else {
					printf("Error: %s :No such file exists\n", argv[q]);
					return 0;
				}
			}
			while((z = getline(&o, &b, fp)) != -1) {
				str[strlen(str) - 1] = '\0';
				ans = infixeval(str, lflag, &dflag, &error, &stackfull);
				printans(ans, lflag, dflag, error, stackfull);
				error = 0;
			}
			fclose(fp);
		}
		q++;
	}
	while(printf("\n> ") && (x = readline(str))) {
		ans = infixeval(str, lflag, &dflag, &error, &stackfull);
		printans(ans, lflag, dflag, error, stackfull);
		error = 0;
	}
	for(x = 0;x < 46; x++) {
		free((variable)[x].bd);
		free((variable)[x].ad);
	}
	return 0;
}
