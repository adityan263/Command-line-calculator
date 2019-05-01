
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

#include "evaluate.h"



/*Deafault value of all variables is set to 0*/
void initvar() {
	int i = 0;
	for(i = 0; i < 46; i++) {
		variable[i] = initnum(variable[i]);
		variable[i].bd[0] = '0';
		variable[i].bi = 1;
	}
}


/*does all operations*/
num solve(char op, num x, num y, int lflag, int *error) {
	int flag = 0, i = 0, j = 0, pwr = 0, ope = 0;
	char str[30], c;
	str[0] = '.';
	str[1] = '\0';
	num res, t;
	long double p = 0;
	/*if y is a variable convert to number*/
	if(op != 'r' && y.var == 1) {
		if(y.v >= 'a' && y.v <= 'z') {
			strcpy(y.bd, variable[y.v - 'a'].bd);
			y.bi = variable[y.v - 'a'].bi;
			y.sign = variable[y.v - 'a'].sign;
			strcpy(y.ad, variable[y.v - 'a'].ad);
			y.ai = variable[y.v - 'a'].ai;
			y.alimit = variable[y.v - 'a'].alimit;
			y.blimit = variable[y.v - 'a'].blimit;
		}
		else if(y.v >= 'G' && y.v <= 'Z') {
			strcpy(y.bd, variable[y.v - 'G' + 26].bd);
			y.bi = variable[y.v - 'G' + 26].bi;
			y.sign = variable[y.v - 'G' + 26].sign;
			strcpy(y.ad, variable[y.v - 'G' + 26].ad);
			y.ai = variable[y.v - 'G' + 26].ai;
			y.alimit = variable[y.v - 'G' + 26].alimit;
			y.blimit = variable[y.v - 'G' + 26].blimit;
		}
		else
			*error = 1;
	}
	/*if x is a variable*/
	if(x.var == 1) {
		if(x.v >= 'a' && x.v <= 'z') {
			strcpy(x.bd, variable[x.v - 'a'].bd);
			x.bi = variable[x.v - 'a'].bi;
			x.sign = variable[x.v - 'a'].sign;
			strcpy(x.ad, variable[x.v - 'a'].ad);
			x.ai = variable[x.v - 'a'].ai;
			x.alimit = variable[x.v - 'a'].alimit;
			x.blimit = variable[x.v - 'a'].blimit;
		}
		else if(x.v >= 'G' && x.v <= 'Z') {
			strcpy(x.bd, variable[x.v - 'G' + 26].bd);
			x.bi = variable[x.v - 'G' + 26].bi;
			x.sign = variable[x.v - 'G' + 26].sign;
			strcpy(x.ad, variable[x.v - 'G' + 26].ad);
			x.ai = variable[x.v - 'G' + 26].ai;
			x.alimit = variable[x.v - 'G' + 26].alimit;
			x.blimit = variable[x.v - 'G' + 26].blimit;
		}
		else
			*error = 1;
	}
	switch(op) {
		case '+':					/* y + x */
			return add(x, y, ope, pwr);
			break;
		case '-':					/* y - x */
			return sub(x, y, ope, pwr);
			break;
		case '*':					/* y * x */
			return mul(x, y, pwr);
			break;
		case '/':					/* y / x */
			x = rmz(x);
			if(x.bi == 0 && x.ai == 0) {
				printf("division by 0 \n");
				*error = 1;
				free(x.bd);
				free(x.ad);
				return y;
			}
			else
				return divi(x, y, lflag, ope, pwr);
			break;
		case '%':					/* y % x */
			x = rmz(x);
			if(x.bi == 0 && x.ai == 0) {
				printf("mod by 0 \n");
				*error = 1;
				free(y.bd);
				free(y.ad);
				return x;
			}
			else
				return mod(x, y, ope, pwr);
			break;
		case '^':					/* y ^ x */
			x = rmz(x);
			x = rmza(x);
			if(x.ai != 0) {
				printf("exponent must be integer");
				*error = 1;
				free(y.bd);
				free(y.ad);
				return x;
			}
			else if(x.bi == 0) {			/*if exponent is 0 return 1*/
				t = initnum(t);
				t.bi = 1;
				t.bd[0] = '1';
				t.bd[1] = '\0';
				free(y.bd);
				free(y.ad);
				free(x.bd);
				free(x.ad);
				return t;
			}
			else if(x.bi == 1 && x.bd[0] == '1' && x.sign == 0) {
				free(x.bd);			/* if x = 1 return y */
				free(x.ad);
				return y;
			}
			else {
				t = initnum(t);
				t.bi = 1;			/* t = 2 */
				t.bd[0] = '2';
				t.bd[1] = '\0';
				pwr = 1;
				if(x.sign == 0) {		/* x is positive */
					res = y;
					x.bd[x.bi - 1]++;
					x = sub(t, x, ope, pwr);
					while(x.bi > 0) {	/* y ^ x with logarithmic time complexity*/
						if(x.bd[x.bi - 1] % 2 == 1)
							res = mul(res, y, pwr);
						x = divi(t, x, lflag, ope, pwr);
						y = mul(y, y, pwr);
						x = rmz(x);
						y = rmz(y);
					}
				}
				else {				/* x is negative */
					res = t;
					while(x.bi > 0) {
						res = divi(y, res, lflag, ope, pwr);
						x = sub(t, x, ope, pwr);
						x = rmz(x);
					}
				}
			}
			pwr = 0;
			free(t.bd);
			free(t.ad);
			free(x.bd);
			free(x.ad);
			free(y.bd);
			free(y.ad);
			return res;
			break;	
		case 'a': case 'b':					/*sin and cos*/
			t = initnum(t);
			ope = 1;
			/*subtract n*pi till x is has > 38 digits */
			if(x.bi > 38) {
				t = getpi(t);
				while(x.bi > 38) {
					x = sub(t, x, ope, pwr);
					x = rmz(x);
				}
			}
			ope = 0;
			/*convert to long double*/
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			if(x.sign == 1)
				p *= -1;
			/*find sine*/
			switch(op) {
				case 'a':
					p = sinl(p);
					break;
				case 'b':
					p = cosl(p);
					break;
			}
			/*convert long double to string */
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			if(((int)p)) {
				free(x.bd);
				free(x.ad);
				return t;
			}
			while(i < 6) {
				t.ad[i] = 48 + (int)(p * 10);
				p = (p * 10) - (int)(p * 10);
				i++;
			}
			t.bd[0] = '\0';
			t.bi = 0;
			t.ad[i] = '\0';
			t.ai = 6;
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'c': case 'd': case 'e': case 'f':		/*tan, cot, sec, cosec*/
			t = initnum(t);
			ope = 1;
			if(x.bi > 38) {
				t = getpi(t);
				while(x.bi > 38) {
					x = sub(t, x, ope, pwr);
					x = rmz(x);
				}
			}
			ope = 0;
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			if(x.sign == 1)
				p *= -1;
			switch(op) {
				case 'c':
					p = tanl(p);
					break;
				case 'd':
					p = 1 / tanl(p);
					break;
				case 'e':
					p = 1 / cosl(p);
					break;
				case 'f':
					p = 1 / sinl(p);
					break;
			}
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			while(p >= 1) {
				p = p / 10;
				i++;
			}
			t.bd[i] = '\0';
			t.bi = i;
			j = 0;
			while(i > j) {
				t.bd[j] = 48 + (int)(p * 10);
				p = (p * 10) -(int)(p * 10);
				j++;
			}
			i = 0;
			while(i < 6) {
				t.ad[i] = 48 + (int)(p * 10);
				p = (p * 10) -(int)(p * 10);
				i++;
			}
			t.ad[i] = '\0';
			t.ai = 6;
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'g': case 'h': case 'i':				/*log, ln, e^*/
			t = initnum(t);
			if(x.bi > 38) {
				printf("number is too big");
				*error = 1;
				return x;
			}
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			if(x.sign == 1)
				p *= -1;
			if(op == 'g')
				p = logl(p) / log(10);
			else if(op == 'h')
				p = logl(p);
			else
				p = expl(p);
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			while(p >= 1) {
				p = p / 10;
				i++;
			}
			t.bd[i] = '\0';
			t.bi = i;
			j = 0;
			while(i > j) {
				t.bd[j] = 48 + (int)(p * 10);
				p = (p * 10) -(int)(p * 10);
				j++;
			}
			i = 0;
			while(i < 6) {
				t.ad[i] = 48 + (int)(p * 10);
				p = (p * 10) -(int)(p * 10);
				i++;
			}
			t.ad[i] = '\0';
			t.ai = 6;
			free(x.ad);
			free(x.bd);
			return t;
			break;
		case 'j': case 'k':					/*squareroot, cuberoot*/
			t = initnum(t);
			if(x.sign == 1 && op == 'j') {
				*error = 1;
				printf("squareroot of negative number is not real\n");
				return x;
			}
			if(x.bi > 38) {
				printf("number is too big");
				*error = 1;
				return x;
			}
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			if(x.sign == 1)
				p *= -1;
			if(op == 'j')
				p = sqrtl(p);
			else
				p = cbrtl(p);
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			while(p >= 1) {
				p = p / 10;
				i++;
			}
			t.bd[i] = '\0';
			t.bi = i;
			j = 0;
			while(i > j) {
				t.bd[j] = 48 + (int)(p * 10);
				p = (p * 10) -(int)(p * 10);
				j++;
			}
			i = 0;
			while(i < 6) {
				t.ad[i] = 48 + (int)(p * 10);
				p = (p * 10) -(int)(p * 10);
				i++;
			}
			t.ad[i] = '\0';
			t.ai = 6;
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'l': case 'm':					/* && and || */
			t = initnum(t);
			t.bi = 1;
			t.bd[0] = '1';
			t.bd[1] = '\0';
			x = rmz(x);
			x = rmza(x);
			y = rmz(y);
			y = rmza(y);
			/*if no. of digits are > 0 then true*/
			if(op == 'l') {
				if(!((x.ai + x.bi) && (y.ai + y.bi)))
					t.bd[0] = '0';
			}
			else
				if(!((x.ai + x.bi) || (y.ai + y.bi)))
					t.bd[0] = '0';
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'n': case 'p':			/*> and >=*/
			t = initnum(t);
			t.bi = 1;
			t.bd[0] = '1';
			t.bd[1] = '\0';
			x = rmz(x);
			y = rmz(y);
			/*if no. of digits are different then return 0*/
			if(x.bi > y.bi)
				t.bd[0] = '0';
			else if(x.bi == y.bi) {
				/*check digit by digit*/
				while(i < x.bi) {
					if(x.bd[i] > y.bd[i]) {
						flag = 2;
						t.bd[0] = '0';
						break;
					}
					else if(x.bd[i] < y.bd[i]) {
						flag = 1;
						break;
					}
					i++;
				}
				if(flag == 0) {
					i = 0;
					while((i < x.ai) || (i < y.ai)) {
						if(x.ad[i] > y.ad[i]) {
							flag = 2;
							t.bd[0] = '0';
							break;
						}
						else if(x.ad[i] < y.ad[i]) {
							flag = 1;
							break;
						}
						i++;
					}	
				}
				if(op == 'n' && flag == 0)
					t.bd[0] = '0';
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'o': case 'q':				/*< and <=*/
			t = initnum(t);
			t.bi = 1;
			t.bd[0] = '1';
			t.bd[1] = '\0';
			x = rmz(x);
			y = rmz(y);
			if(x.bi < y.bi)
				t.bd[0] = '0';
			else if(x.bi == y.bi) {
				while(i < x.bi) {
					if(x.bd[i] > y.bd[i]) {
						flag = 2;
						break;
					}
					else if(x.bd[i] < y.bd[i]) {
						flag = 1;
						t.bd[0] = '0';
						break;
					}
					i++;
				}
				if(flag == 0) {
					i = 0;
					while(i < x.ai ) {
						if(x.ad[i] > y.ad[i]) {
							flag = 2;
							break;
						}
						else if(x.ad[i] < y.ad[i]) {
							flag = 1;
							t.bd[0] = '0';
							break;
						}
						i++;
					}	
				}
				if((flag == 0) && (op == 'o'))
					t.bd[0] = '0';
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'r':						/* = */
			if(y.var == 0)
				*error = 1;
			else {
				if(y.v >= 'a' && y.v <= 'z') {
					strcpy(variable[y.v - 'a'].bd, x.bd);
					variable[y.v - 'a'].bi = x.bi;
					variable[y.v - 'a'].sign = x.sign;
					strcpy(variable[y.v - 'a'].ad, x.ad);
					variable[y.v - 'a'].ai = x.ai;
					variable[y.v - 'a'].alimit = x.alimit;
					variable[y.v - 'a'].blimit = x.blimit;
				}
				else if(y.v >= 'G' && y.v <= 'Z') {
					strcpy(variable[y.v - 'G' + 26].bd, x.bd);
					variable[y.v - 'G' + 26].bi = x.bi;
					variable[y.v - 'G' + 26].sign = x.sign;
					strcpy(variable[y.v - 'G' + 26].ad, x.ad);
					variable[y.v - 'G' + 26].ai = x.ai;
					variable[y.v - 'G' + 26].alimit = x.alimit;
					variable[y.v - 'G' + 26].blimit = x.blimit;
				}
				else
					*error = 1;
			}
			return x;
			break;
		case 's': case 't':				/* == and !*/
			t = initnum(t);
			t.bi = 1;
			t.bd[0] = '1';
			t.bd[1] = '\0';
			x = rmz(x);
			y = rmz(y);
			x = rmza(x);
			y = rmza(y);
			if(op == 't') {
				if(x.bi != 0 || x.ai != 0)
					t.bd[0] = '0';
				free(x.bd);
				free(x.ad);
				return t;
			}
			if((x.bi != y.bi) || (x.ai != y.ai)) {
				t.bd[0] = '0';
				return t;
			}
			while(i < x.bi) {
				if(x.bd[i] != y.bd[i]) {
					t.bd[0] = '0';
					return t;
				}
				i++;
			}
			while(i < x.ai) {
				if(x.ad[i] != y.ad[i]) {
					t.bd[0] = '0';
					return t;
				}
				i++;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'u':case 'v':			/*floor and ceiling*/
			t = initnum(t);
			t.bi = 1;
			t.bd[0] = '1';
			t.bd[1] = '\0';
			if(x.sign == 1) {
				if(op == 'u') {
					op = 'v';
					t.sign = 1;
				}
				else
					op = 'u';
			}
			if(op == 'v' && x.ai != 0)
				x = add(t, x, ope, pwr);
			x.ai = 0;
			x.ad[0] = '\0';
			return x;
			break;
		case 'A':					/*bo*/
			t = initnum(t);
			i = x.bi % 3;
			if(i)
				x = adz(x, 3 - i);
			i = 0;
			t = adz(t, x.bi / 3);
			while(i < x.bi) {
				if(x.bd[i] == '1')
					t.bd[i / 3] += 4;
				else if(x.bd[i] != '0')
					*error = 1;
				if(x.bd[i + 1] == '1')
					t.bd[i / 3] += 2;
				else if(x.bd[i + 1] != '0')
					*error = 1;
				if(x.bd[i + 2] == '1')
					t.bd[i / 3] += 1;
				else if(x.bd[i + 2] != '0')
					*error = 1;
				i += 3;
			}
			t.bd[i / 3] = '\0';
			t.bi = i / 3;
			if(lflag == 1) {
				i = x.ai % 3;
				if(i)
					x = adza(x, 3 - i);
				i = 0;
				t = adza(t, x.ai / 3);
				while(i < x.ai) {
					if(x.ad[i] == '1')
						t.ad[i / 3] += 4;
					else if(x.ad[i] != '0')
						*error = 1;
					if(x.ad[i + 1] == '1')
						t.ad[i / 3] += 2;
					else if(x.ad[i + 1] != '0')
						*error = 1;
					if(x.ad[i + 2] == '1')
						t.ad[i / 3] += 1;
					else if(x.ad[i + 2] != '0')
						*error = 1;
					i += 3;
				}
				t.ad[i / 3] = '\0';
				t.ai = i / 3;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'C':					/*bh*/
			t = initnum(t);
			i = x.bi % 4;
			if(i)
				x = adz(x, 4 - i);
			i = 0;
			t = adz(t, x.bi / 4);
			while(i < x.bi) {
				if(x.bd[i] == '1')
					t.bd[i / 4] += 8;
				else if(x.bd[i] != '0')
					*error = 1;
				if(x.bd[i + 1] == '1')
					t.bd[i / 4] += 4;
				else if(x.bd[i + 1] != '0')
					*error = 1;
				if(x.bd[i + 2] == '1')
					t.bd[i / 4] += 2;
				else if(x.bd[i + 2] != '0')
					*error = 1;
				if(x.bd[i + 3] == '1')
					t.bd[i / 4] += 1;
				else if(x.bd[i + 3] != '0')
					*error = 1;
				if(t.bd[i / 4] > '9')
					t.bd[i / 4] += 7;
				i += 4;
			}
			t.bd[i / 4] = '\0';
			t.bi = i / 4;
			if(lflag == 1) {
				i = x.ai % 4;
				if(i)
					x = adza(x, 4 - i);
				i = 0;
				t = adza(t, x.ai / 4);
				while(i < x.ai) {
					if(x.ad[i] == '1')
						t.ad[i / 4] += 8;
					else if(x.ad[i] != '0')
						*error = 1;
					if(x.ad[i + 1] == '1')
						t.ad[i / 4] += 4;
					else if(x.ad[i + 1] != '0')
						*error = 1;
					if(x.ad[i + 2] == '1')
						t.ad[i / 4] += 2;
					else if(x.ad[i + 2] != '0')
						*error = 1;
					if(x.ad[i + 3] == '1')
						t.ad[i / 4] += 1;
					else if(x.ad[i + 3] != '0')
						*error = 1;
					if(t.ad[i / 4] > '9')
						t.ad[i / 4] += 7;
					i += 4;
				}
				t.ad[i / 4] = '\0';
				t.ai = i / 4;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'D':					/*ob*/
			t = initnum(t);
			/*if x.bi*3 > default no. of digits limit then adz will reinitiate*/
			t = adz(t, x.bi * 3);
			/*as we're using strcat 1st char  must be '\0'*/
			t.bd[0] = '\0';
			while(i < x.bi) {
				switch(x.bd[i]) {
					case '0':
						strcat(t.bd, "000");
						break;
					case '1':
						strcat(t.bd, "001");
						break;
					case '2':
						strcat(t.bd, "010");
						break;
					case '3':
						strcat(t.bd, "011");
						break;
					case '4':
						strcat(t.bd, "100");
						break;
					case '5':
						strcat(t.bd, "101");
						break;
					case '6':
						strcat(t.bd, "110");
						break;
					case '7':
						strcat(t.bd, "111");
						break;
					default :
						*error = 1;
						return x;
						break;
				}
				i++;
			}
			t.bi = 3 * x.bi;
			if(lflag == 1) {
				i = 0;
				t = adza(t, x.ai * 3);
				t.ad[0] = '\0';
				while(i < x.ai) {
					switch(x.ad[i]) {
						case '0':
							strcat(t.ad, "000");
							break;
						case '1':
							strcat(t.ad, "001");
							break;
						case '2':
							strcat(t.ad, "010");
							break;
						case '3':
							strcat(t.ad, "011");
							break;
						case '4':
							strcat(t.ad, "100");
							break;
						case '5':
							strcat(t.ad, "101");
							break;
						case '6':
							strcat(t.ad, "110");
							break;
						case '7':
							strcat(t.ad, "111");
							break;
						default :
							*error = 1;
							return x;
							break;
					}
					i++;
				}
				t.ai = 3 * x.ai;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'E':case 'B':				/*bd and od*/
			t = initnum(t);
			if(op == 'B')
				j = 2;
			else
				j = 8;
			while(i < x.bi) {
				if(x.bd[i] >= '0' && x.bd[i] < ('0' + j))
					p += ((pow(j, x.bi - i - 1)) * (x.bd[i] - 48));
				else {
					*error = 1;
					return x;
				}
				i++;
			}
			if(lflag == 1) {
				i = 0;
				while(i < x.ai) {
					if(x.ad[i] >= '0' && x.ad[i] <= ('0' + j))
						p += ((pow(j, -(1 + i))) * (x.ad[i] - 48));
					else {
						*error = 1;
						return x;
					}
					i++;
				}
			}
			i = 0;
			while(p >= 1) {
				p = p / 10;
				i++;
			}
			t.bd[i] = '\0';
			t.bi = i;
			j = 0;
			while(i > j) {
				t.bd[j] = 48 + ((int)(p * 10) % 10);
				p = p * 10;
				j++;
			}
			i = 0;
			while(i < 6) {
				t.ad[i] = 48 + ((int)(p * 10) % 10);
				p = p * 10;
				i++;
			}
			t.ai = 6;
			t.ad[i] = '\0';
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'F':					/*oh*/
			x = solve('D', x, x, lflag, error);
			x = solve('C', x, x, lflag, error);
			return x;
			break;
		case 'G':					/*db*/
			t = initnum(t);
			p = atof(x.bd);
			while(p) {
				t.bd[i] = ((int)p % 2) + 48;
				i++;
				p = (int)(p / 2);
			}
			t.bi = i;
			t.bd[i] = '\0';
			i--;
			while(i != j) {
				c = t.bd[i];
				t.bd[i] = t.bd[j];
				t.bd[j] = c;
				i--;
				if(i == j)
					break;
				j++;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'H':					/*do*/
			t = initnum(t);
			p = atof(x.bd);
			while(p) {
				t.bd[i] = ((int)p % 8) + 48;
				i++;
				p = (int)(p / 8);
			}
			t.bi = i;
			t.bd[i] = '\0';
			i--;
			while(i != j) {
				c = t.bd[i];
				t.bd[i] = t.bd[j];
				t.bd[j] = c;
				i--;
				if(i == j)
					break;
				j++;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'I':					/*dh*/
			t = initnum(t);
			p = atof(x.bd);
			while(p) {
				t.bd[i] = ((int)p % 16) + 48;
				if(t.bd[i] > '9')
					t.bd[i] += 'A' - '9' - 1;
				i++;
				p = (int)(p / 16);
			}
			t.bi = i;
			t.bd[i] = '\0';
			i--;
			while(i != j) {
				c = t.bd[i];
				t.bd[i] = t.bd[j];
				t.bd[j] = c;
				i--;
				if(i == j)
					break;
				j++;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'J':						/*hb*/
			t = initnum(t);
			t = adz(t, x.bi * 4);
			t.bd[0] = '\0';
			while(i < x.bi) {
				switch(x.bd[i]) {
					case '0':
						strcat(t.bd, "0000");
						break;
					case '1':
						strcat(t.bd, "0001");
						break;
					case '2':
						strcat(t.bd, "0010");
						break;
					case '3':
						strcat(t.bd, "0011");
						break;
					case '4':
						strcat(t.bd, "0100");
						break;
					case '5':
						strcat(t.bd, "0101");
						break;
					case '6':
						strcat(t.bd, "0110");
						break;
					case '7':
						strcat(t.bd, "0111");
						break;
					case '8':
						strcat(t.bd, "1000");
						break;
					case '9':
						strcat(t.bd, "1001");
						break;
					case 'A':
						strcat(t.bd, "1010");
						break;
					case 'B':
						strcat(t.bd, "1011");
						break;
					case 'C':
						strcat(t.bd, "1100");
						break;
					case 'D':
						strcat(t.bd, "1101");
						break;
					case 'E':
						strcat(t.bd, "1110");
						break;
					case 'F':
						strcat(t.bd, "1111");
						break;
					default :
						*error = 1;
						break;
				}
				i++;
			}
			t.bi = 4 * x.bi;
			if(lflag == 1) {
				i = 0;
				t = adza(t, x.ai * 4);
				t.ad[0] = '\0';
				while(i < x.ai) {
					switch(x.ad[i]) {
						case '0':
							strcat(t.ad, "0000");
							break;
						case '1':
							strcat(t.ad, "0001");
							break;
						case '2':
							strcat(t.ad, "0010");
							break;
						case '3':
							strcat(t.ad, "0011");
							break;
						case '4':
							strcat(t.ad, "0100");
							break;
						case '5':
							strcat(t.ad, "0101");
							break;
						case '6':
							strcat(t.ad, "0110");
							break;
						case '7':
							strcat(t.ad, "0111");
							break;
						case '8':
							strcat(t.ad, "1000");
							break;
						case '9':
							strcat(t.ad, "1001");
							break;
						case 'A':
							strcat(t.ad, "1010");
							break;
						case 'B':
							strcat(t.ad, "1011");
							break;
						case 'C':
							strcat(t.ad, "1100");
							break;
						case 'D':
							strcat(t.ad, "1101");
							break;
						case 'E':
							strcat(t.ad, "1110");
							break;
						case 'F':
							strcat(t.ad, "1111");
							break;
						default :
							*error = 1;
							break;
					}
				i++;
				}
				t.ai = 4 * x.ai;
			}
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'K':					/*ho*/
			x = solve('J', x, x, lflag, error);
			x = solve('A', x, x, lflag, error);
			return x;
			break;
		case 'L':					/*hd*/
			t = initnum(t);
			while(i < x.bi) {
				if(x.bd[i] >= '0' && x.bd[i] <= '9')
					p += ((pow(16, x.bi - i - 1)) * (x.bd[i] - 48));
				else if(x.bd[i] >= 'A' && x.bd[i] <= 'F')
					p += ((pow(16, x.bi - i - 1)) * (x.bd[i] - 'A' + 10));
				else {
					*error = 1;
					return x;
				}
				i++;
			}
			if(lflag == 1) {
				i = 0;
				while(i < x.ai) {
					if(x.ad[i] >= '0' && x.ad[i] <= '9')
						p += ((pow(16, -(1 + i))) * (x.ad[i] - 48));
					else if(x.ad[i] >= 'A' && x.ad[i] <= 'F')
						p += ((pow(16, -(1 + i))) * (x.ad[i] - 'A' + 10));
					else {
						*error = 1;
						return x;
					}
					i++;
				}
			}
			i = 0;
			while(p >= 1) {
				p = p / 10;
				i++;
			}
			t.bd[i] = '\0';
			t.bi = i;
			j = 0;
			while(i > j) {
				t.bd[j] = 48 + ((int)(p * 10) % 10);
				p = p * 10;
				j++;
			}
			i = 0;
			while(i < 6) {
				t.ad[i] = 48 + ((int)(p * 10) % 10);
				p = p * 10;
				i++;
			}
			t.ai = 6;
			t.ad[i] = '\0';
			free(x.bd);
			free(x.ad);
			return t;
			break;
		case 'O': case 'P': case 'Q': case 'R':		/* +=, -=, *=, /= */
			if(y.var == 0) {
				*error = 1;
				return y;
			}
			c = y.v;
			switch(op) {
				case 'O':
					y = add(x, y, ope, pwr);
					break;
				case 'P':
					y = sub(x, y, ope, pwr);
					break;
				case 'Q':
					y = mul(x, y, pwr);
					break;
				case 'R':
					x = rmz(x);
					if(x.bi == 0 && x.ai == 0) {
						printf("division by 0 \n");
						*error = 1;
						free(x.bd);
						free(x.ad);
						return y;
					}
					else
						y = divi(x, y, lflag, ope, pwr);
					break;
			}
			if(c >= 'a' && c <= 'z') {
				strcpy(variable[c - 'a'].bd, y.bd);
				variable[c - 'a'].bi = y.bi;
				variable[c - 'a'].sign = y.sign;
				strcpy(variable[c - 'a'].ad, y.ad);
				variable[c - 'a'].ai = y.ai;
				variable[c - 'a'].alimit = y.alimit;
				variable[c - 'a'].blimit = y.blimit;
			}
			else if(c >= 'G' && c <= 'Z') {
				strcpy(variable[c - 'G' + 26].bd, y.bd);
				variable[c - 'G' + 26].bi = y.bi;
				variable[c - 'G' + 26].sign = y.sign;
				strcpy(variable[c - 'G' + 26].ad, y.ad);
				variable[c - 'G' + 26].ai = y.ai;
				variable[c - 'G' + 26].alimit = y.alimit;
				variable[c - 'G' + 26].blimit = y.blimit;
			}
			else
				*error = 1;
			return y;
			break;
		case 'S': case 'U':				/* ++ pre and post */
			if(y.var != 1) {
				*error = 1;
				return y;
			}
			t = initnum(t);
			t.bi = 1;
			t.bd[0] = '1';
			t.bd[1] = '\0';
			c = y.v;
			ope = 1;
			y = add(y, t, ope, pwr);
			if(c >= 'a' && c <= 'z') {
				strcpy(variable[c - 'a'].bd, y.bd);
				variable[c - 'a'].bi = y.bi;
				variable[c - 'a'].sign = y.sign;
				strcpy(variable[c - 'a'].ad, y.ad);
				variable[c - 'a'].ai = y.ai;
				variable[c - 'a'].alimit = y.alimit;
				variable[c - 'a'].blimit = y.blimit;
			}
			else if(c >= 'G' && c <= 'Z') {
				strcpy(variable[c - 'G' + 26].bd, y.bd);
				variable[c - 'G' + 26].bi = y.bi;
				variable[c - 'G' + 26].sign = y.sign;
				strcpy(variable[c - 'G' + 26].ad, y.ad);
				variable[c - 'G' + 26].ai = y.ai;
				variable[c - 'G' + 26].alimit = y.alimit;
				variable[c - 'G' + 26].blimit = y.blimit;
			}
			else
				*error = 1;
			ope = 0;
			if(op == 'U')
				y = sub(t, y, ope, pwr);
			y.var = 0;
			return y;
			break;
		case 'T': case 'V':				/* -- pre and post */
			if(y.var != 1) {
				*error = 1;
				return y;
			}
			t = initnum(t);
			t.bi = 1;
			t.bd[0] = '1';
			t.bd[1] = '\0';
			c = y.v;
			ope = 1;
			y = sub(t, y, ope, pwr);
			if(c >= 'a' && c <= 'z') {
				strcpy(variable[c - 'a'].bd, y.bd);
				variable[c - 'a'].bi = y.bi;
				variable[c - 'a'].sign = y.sign;
				strcpy(variable[c - 'a'].ad, y.ad);
				variable[c - 'a'].ai = y.ai;
				variable[c - 'a'].alimit = y.alimit;
				variable[c - 'a'].blimit = y.blimit;
			}
			else if(c >= 'G' && c <= 'Z') {
				strcpy(variable[c - 'G' + 26].bd, y.bd);
				variable[c - 'G' + 26].bi = y.bi;
				variable[c - 'G' + 26].sign = y.sign;
				strcpy(variable[c - 'G' + 26].ad, y.ad);
				variable[c - 'G' + 26].ai = y.ai;
				variable[c - 'G' + 26].alimit = y.alimit;
				variable[c - 'G' + 26].blimit = y.blimit;
			}
			else
				*error = 1;
			ope = 0;
			if(op == 'V')
				y = add(t, y, ope, pwr);
			y.var = 0;
			return y;
			break;
		default:
			*error = 1;
			return x;
			break;				
	}

}



num infixeval(char *str, int lflag, int *dflag, int *error, int *stackfull) {
	token *t;
	num result, x, y;
	y = initnum(y);
	x = initnum(x);
	int  pretok = 0, curtok = 0;
	stacki a;
	initi(&a);
	stackc b;
	initc(&b);
	char optr;
	int reset = 1, h = 0, p, q;
	while(1) {
		t = getnext(str, &reset, lflag, dflag);
		if(*error == 1)
			return x;
		curtok = t->type;
		/*if there are two consecutive operands...to avoid cases like "5 2 +"*/
		if(curtok == OPERAND && pretok == OPERAND) {
			*error = 1;
			return x;
		}
		if((curtok == pretok || emptyi(&a)) && t->op == '-') {		/*if int_stack is empty then '-' is 1st char of string*/
			if(!fulli(&a) && !fullc(&b)) {
				x.bd[0] = '1';
				x.bi = 1;
				x.ad[0] = '\0';
				x.ai = 0;
				x.bd[1] = '\0';
				x.sign = 1;
				pushi(&a, x);
				pushc(&b, '*');
			}
			else {
				*error = 1;
				*stackfull = 1;
				return x;
			}
			continue;
		}
		/*if no. of opening and closing brackets don't match*/
		if(t->type == END && h != 0) {
			*error = 1;
			return x;
		}
		if(t->type == OPERAND) {
			if(!fulli(&a))
				pushi(&a, t->number);
			else {
				*error = 1;
				*stackfull = 1;
				return x;
			}
		}
		else if (t->type == OPERATOR) {
			switch(t->op) {
				case '(':
					h++;
					break;
				case ')':
					h--;
					break;
				case 'M':case 'N':		/*to determine ++ or -- is pre or post operator*/
					t->op += 'S' - 'M'; 
					if(pretok == OPERAND)
						(t->op) += 2;
					break;
			}
			if(!emptyc(&b)) {
				optr = ctop(&b);
				if(t->op == 'r') {		/*there shouldn't be any operator before '=' */
					*error = 1;
					return x;
				}
				p = precedence(optr);
				q = precedence(t->op);
				if(p == -2 || q == -2) {
					*error = 1;
					return x;
				}
				if(q > p) {
					if(!fullc(&b))	
						pushc(&b, t->op);
					else {
						*error = 1;
						*stackfull = 1;
						return x;
					}
				} 	
				else {	
					while(q <= p) {
						optr = popc(&b);
						if(optr == '(') {
							pushc(&b, optr);
							break;
						}
						else if(optr == 'a' || optr == 'b' || optr == 'c' || optr == 'd' || 
						        optr == 'h' || optr == 'g' || optr == 'f' || optr == 'e' || 
						        optr == 'i' || optr == 'j' || optr == 'k' || optr == 'A' ||
						        optr == 'B' || optr == 'C' || optr == 'D' || optr == 'E' || 
						        optr == 'F' || optr == 'G' || optr == 'H' || optr == 'I' || 
						        optr == 'J' || optr == 'K' || optr == 'L' || optr == 'T' ||
							optr == 'S' || optr == 'u' || optr == 'v' || optr == 'U' ||
							optr == 'V' || optr == 't') {		/*unary operators*/
							if(!emptyi(&a))
								x = popi(&a);
							else {
								*error = 1;
								return x;						
							}
							result = solve(optr, x, x, lflag, error);
							pushi(&a, result);
							if(!emptyc(&b)) {
								optr = ctop(&b);
								p = precedence(optr);
							}
							else
								break;
						}
						else {				/*binary operators*/
							if(!emptyi(&a))
								x = popi(&a);
							else {
								*error = 1;
								return x;
							}
							if(!emptyi(&a))
								y = popi(&a);
							else {
								*error = 1;
								return x;
							}
							result = solve(optr, x, y, lflag, error);
							pushi(&a, result);
							if(!emptyc(&b)) {
								optr = ctop(&b);
								p = precedence(optr);
							}
							else
								break;
						}
					}
					if(t->op != ')')
						pushc(&b, t->op);
					else
						optr = popc(&b);
				}
			}
			else {
				pushc(&b, t->op);
			}
		}
		else if (t->type == END) {
			if(!emptyc(&b)) {
				while(!emptyc(&b)){
					optr = popc(&b);
					if(optr == 'a' || optr == 'b' || optr == 'c' || optr == 'd' || 
					   optr == 'h' || optr == 'g' || optr == 'f' || optr == 'e' || 
					   optr == 'i' || optr == 'j' || optr == 'k' || optr == 'A' ||
					   optr == 'B' || optr == 'C' || optr == 'D' || optr == 'E' || 
					   optr == 'F' || optr == 'G' || optr == 'H' || optr == 'I' || 
					   optr == 'J' || optr == 'K' || optr == 'L' || optr == 'S' ||
					   optr == 'T' || optr == 'u' || optr == 'v' || optr == 'U' ||
					   optr == 'V' || optr == 't') {			/*unary operators*/
						if(!emptyi(&a))
							x = popi(&a);
						else {
							*error = 1;
							return x;
						}
						result = solve(optr, x, x, lflag, error);
						pushi(&a, result);
					}
					else {					/*binary operators*/
						if(!emptyi(&a))
							x = popi(&a);
						else {
							*error = 1;
							return x;
						}
						if(!emptyi(&a))
							y = popi(&a);
						else {
							*error = 1;
							return x;
						}
						result = solve(optr, x, y, lflag, error);
						pushi(&a, result);
					}
				}
				return result;
			}
			else {
				x = popi(&a);		/*no need to check if int_stack is empty because there has to be a number*/	
				if(!emptyi(&a)) {
					*error = 1;
					return x;
				}
				else 
					return x;
			}
		} 
		else if (t->type == ERROR) {
			*error = 1;
			return x; 
		}
		pretok = curtok;
	}
	free(t);
}
