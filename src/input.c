
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

#ifndef __INPUT_H__
#include "input.h"
#endif


/*reads line from the terminal and converts it to a string*/
int readline(char *arr) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n') {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}


/*converts string into tokens*/
token *getnext(char *arr, int *reset, int lflag, int *dflag) {
	static int currstate = SPC;
	int nextstate;
	int d1flag = 0; 
	static int i = 0;
	if(*reset == 1) {
		i = 0;
		currstate = SPC;
		*reset = 0;
	}
	num a;
	a = initnum(a);
	char operator(char*, int);
	int x, y;
	char *expre, *opr, delim[2] = "()", *tmp;
	static char optr = '\0';
	token *t = (token *)malloc(sizeof(token));
	if(currstate == ALPH) {
		expre = (char *)malloc(sizeof(char) * 9);
		x = 0;
		*(expre + x) = arr[i - 1];
		x++;
	}
	else if(currstate == OPR) {
		opr = (char *)malloc(sizeof(char) * 4);
		y = 0;
		*(opr + y) = arr[i - 1];
		y++;
	}
	else if(currstate == DIG) {
		if(d1flag == 1) {
			a.ad[a.ai] = arr[i - 1];
			a.ai++;
		}
		else {
			a.bd[a.bi] = arr[i - 1];
			a.bi++;
		}
	}
	if(arr[i - 1] == '.') {
		*dflag = 1;
		d1flag = 1;
	}
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.':
				nextstate = DIG;
				break;
			case 'a': case 'b': case 'c': case 'd':
			case 'e': case 'f': case 'g': case 'h':
			case 'l': case 'k': case 'j': case 'i':
			case 'm': case 'n': case 'o': case 'p':
			case 't': case 's': case 'r': case 'q':
			case 'u': case 'v': case 'w': case 'x':
			case 'y': case 'z': case 'G': case 'H':
			case 'L': case 'K': case 'J': case 'I':
			case 'M': case 'N': case 'O': case 'P':
			case 'T': case 'S': case 'R': case 'Q':
			case 'U': case 'V': case 'W': case 'X':
			case 'Y': case 'Z':
				nextstate = ALPH;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '^':
			case '&': case '|': case '>': case '<': 
			case '=': case '!':
				nextstate = OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				if((optr == 'J' || optr == 'K' || optr == 'L') && arr[i] >= 'A' && arr[i] <= 'F') {
					nextstate = DIG;
					break;
				}
				else {
					nextstate = ERR;
					break;
				}
		}
		switch(currstate) {
			case SPC:
				if(arr[i] == '.') {
					*dflag = 1;
					d1flag = 1;
					break;
				}
				if(nextstate == DIG && d1flag != 1) {
					a.bd[a.bi] = arr[i];
					a.bi++;
				}
				else if(nextstate == DIG && d1flag == 1) {
					a.ad[a.ai] = arr[i];
					a.ai++;
				}
				else if(nextstate == ALPH) {
					x = 0;
					expre = (char *)malloc(sizeof(char) * 9);
					*(expre + x) = arr[i];
					x++;
				}		
				else if(nextstate == OPR) {
					y = 0;
					opr = (char *)malloc(sizeof(char) * 4);
					*(opr + y) = arr[i];
					y++;
				}		
				break;
			case DIG:
				if(arr[i] == '.') {
					*dflag = 1;
					d1flag = 1;
					break;
				}
				if(nextstate == DIG && d1flag != 1) {
					a.bd[a.bi] = arr[i];
					a.bi++;
					if(a.bi == a.blimit)
						a = breinitnum(a);
				}
				else if(nextstate == DIG && d1flag == 1) {
					a.ad[a.ai] = arr[i];
					a.ai++;
					if(a.ai == a.alimit)
						a = areinitnum(a);
				}	
				else  {
					if(a.bi == 0) {
						a.bd[a.bi] = '0';
						a.bi++;
					}
					a.bd[a.bi] = '\0';
					a.ad[a.ai] = '\0';
					t->type = OPERAND;
					t->number = a;
					i++;
					currstate = nextstate;
					return t;
				}
				break;
			case ALPH:
				if(nextstate == ALPH) {
					*(expre + x) = arr[i];
					x++;
				}
				else {
					*(expre + x) = '\0';
					t->type = OPERATOR;
					t->op = operator(expre, lflag);
					optr = t->op;
					if(t->op == '1') {
						if(strlen(expre) != 1)
							t->type = ERROR;
						else {
							t->type = OPERAND;
							a.bd[0] = '0';
							a.bi = 1;
							a.v = expre[0];
							a.var = 1;
							t->number = a;
						}
					}
					free(expre);
					i++;
					currstate = nextstate;
					return t;
				}
				break;
			case OPR:
				if(nextstate == OPR) {
					*(opr + y) = arr[i];
					y++;
				}
				else {
					*(opr + y) = '\0';
					t->type = OPERATOR;
					t->op = operator(opr, lflag);
					optr = t->op;
					if(t->op == '1') {
						if(opr[0] == '(' || opr[0] == ')') {
							optr = t->op = opr[0];	
							currstate = OPR;
							i = i - strlen(opr) + 2;
							free(opr);
							return t;
						}
						else {
							y = strlen(opr);
							tmp = strtok(opr, delim);
							t->op = operator(tmp, lflag);
							optr = t->op;
							currstate = OPR;
							i = i - y + strlen(tmp) + 1;
							free(opr);
							return t;
						}
						t->type = ERROR;
					}
					free(opr);
					currstate = nextstate;
					i++;
					return t;
				}
				break;
			case STOP:
				t->type = END;
				currstate = nextstate;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				return t;
				break;
		}
		currstate = nextstate;
		i++;
	}
}

/*assigns unique character to each operation
 *these characters are later used as operator 
 */
char operator (char *expr, int lflag) {
	if(lflag == 1) {
		if(strcmp(expr, "sin") == 0)
			return 'a';
		else if(strcmp(expr, "cos") == 0)
			return 'b';
		else if(strcmp(expr, "tan") == 0)
			return 'c';
		else if(strcmp(expr, "cot") == 0)
			return 'd';		
		else if(strcmp(expr, "sec") == 0)
			return 'e';
		else if(strcmp(expr, "cosec") == 0)
			return 'f';
		else if(strcmp(expr, "log") == 0)
			return 'g';		
		else if(strcmp(expr, "ln") == 0)
			return 'h';		
		else if(strcmp(expr, "exp") == 0)
			return 'i';
	}		
	if(strcmp(expr, "sqrt") == 0)
		return 'j';		
	else if(strcmp(expr, "cbrt") == 0)
		return 'k';		
	else if(strcmp(expr, "&&") == 0)
		return 'l';						
	else if(strcmp(expr, "||") == 0)
		return 'm';
	else if(strcmp(expr, ">") == 0)
		return 'n';
	else if(strcmp(expr, "<") == 0)
		return 'o';				
	else if(strcmp(expr, ">=") == 0)
		return 'p';
	else if(strcmp(expr, "<=") == 0)
		return 'q';
	else if(strcmp(expr, "=") == 0)
		return 'r';
	else if(strcmp(expr, "==") == 0)
		return 's';
	else if(strcmp(expr, "!") == 0)
		return 't';
	else if(strcmp(expr, "floor") == 0)
		return 'u';
	else if(strcmp(expr, "ceiling") == 0)
		return 'v';
	else if(strcmp(expr, "bo") == 0)
		return 'A';		
	else if(strcmp(expr, "bd") == 0)
		return 'B';						
	else if(strcmp(expr, "bh") == 0)
		return 'C';
	else if(strcmp(expr, "ob") == 0)
		return 'D';
	else if(strcmp(expr, "od") == 0)
		return 'E';				
	else if(strcmp(expr, "oh") == 0)
		return 'F';
	else if(strcmp(expr, "db") == 0)
		return 'G';
	else if(strcmp(expr, "do") == 0)
		return 'H';
	else if(strcmp(expr, "dh") == 0)
		return 'I';
	else if(strcmp(expr, "hb") == 0)
		return 'J';
	else if(strcmp(expr, "ho") == 0)
		return 'K';
	else if(strcmp(expr, "hd") == 0)
		return 'L';
	else if(strcmp(expr, "+") == 0)
		return '+';
	else if(strcmp(expr, "-") == 0)
		return '-';
	else if(strcmp(expr, "/") == 0)
		return '/';
	else if(strcmp(expr, "*") == 0)
		return '*';
	else if(strcmp(expr, "^") == 0)
		return '^';
	else if(strcmp(expr, "%") == 0)
		return '%';
	else if(strcmp(expr, "(") == 0)
		return '(';
	else if(strcmp(expr, ")") == 0)
		return ')';
	else if(strcmp(expr, "++") == 0)
		return 'M';
	else if(strcmp(expr, "--") == 0)
		return 'N';
	else if(strcmp(expr, "+=") == 0)
		return 'O';
	else if(strcmp(expr, "-=") == 0)
		return 'P';
	else if(strcmp(expr, "*=") == 0)
		return 'Q';
	else if(strcmp(expr, "/=") == 0)
		return 'R';
	else
		return '1';
}

/*returns precedence of operator*/
int precedence(char b) {
	switch(b) {
		case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'r': case 'q': case 's':
			return -1;
			break;
		case '(':
			return 4;
			break;
		case ')':
			return 0;
			break;
		case '+': case '-':
			return 1;
			break;
		case '*': case '/': case '%': case '^':
			return 2;
			break;
		case 'a': case 'b': case 'c': case 'd':
		case 'e': case 'f': case 'g': case 'h':
		case 'k': case 'j': case 'i': case 't':	
		case 'A': case 'B': case 'C': case 'D':
		case 'E': case 'F': case 'G': case 'H':
		case 'I': case 'J': case 'K': case 'L':
		case 'S': case 'T': case 'U': case 'V':
		case 'u': case 'v':
			return 3;
			break;
	}
	return -2;
}
