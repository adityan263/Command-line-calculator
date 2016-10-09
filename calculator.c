#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"
#include <math.h>
  
int lflag = 0, dflag = 0, stackfull = 0, error = 0;

int readline(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n' && i < len - 1) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}

#define OPERAND 10 
#define OPERATOR 20
#define	END	30
#define ERROR	40
typedef struct token {
	int type;
	num number;
	char op;
}token;


enum states { SPC, DIG, OPR, ALPH, STOP, ERR };

token *getnext(char *arr, int *reset) {
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
	a.ai = 0;
	a.bi = 0;
	a.sign = 0;
	char ope(char*);
	int x;
	char *expre;
	token *t = (token *)malloc(sizeof(token));
	if(currstate == ALPH) {
		expre = (char *)malloc(sizeof(char) * 7);
		x = 0;
		*(expre + x) = arr[i - 1];
		x++;
	}
	if(arr[i - 1] == '.') {
		dflag = 1;
		d1flag = 1;
	}
	if(currstate == DIG) {
		if(d1flag == 1) {
			a.ad[a.ai] = arr[i - 1];
			a.ai++;
		}
		else {
			a.bd[a.bi] = arr[i - 1];
			a.bi++;
		}
	}
	
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.': case 'A':
			case 'B': case 'C': case 'D': case 'E':
			case 'F':
				nextstate = DIG;
				break;
			case 'a': case 'b': case 'c': case 'd':
			case 'e': case 'f': case 'g': case 'h':
			case 'l': case 'k': case 'j': case 'i':
			case 'm': case 'n': case 'o': case 'p':
			case 't': case 's': case 'r': case 'q':
			case 'u': case 'v': case 'w': case 'x':
			case 'y': case 'z': case '&': case '|':
			case '>': case '<': case '=':
				nextstate = ALPH;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '^':
				nextstate = OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch(currstate) {
			case SPC:
				if(arr[i] == '.') {
					dflag = 1;
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
					expre = (char *)malloc(sizeof(char) * 7);
					*(expre + x) = arr[i];
					x++;
				}		
				break;
			case DIG:
				if(arr[i] == '.') {
					dflag = 1;
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
					t->op = ope(expre);
					if(t->op == '1') {
						t->type = ERROR;
						currstate = nextstate;
						return t;
					}
					free(expre);
					i++;
					currstate = nextstate;
					return t;
				}
				break;
			case OPR:
				t->type = OPERATOR;
				t->op = arr[i - 1];	
				currstate = nextstate;
				i++;
				return t;
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

char ope (char *expr) {
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
	else
		return '1';
}

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
		case 'k': case 'j': case 'i':		
		case 'A': case 'B': case 'C': case 'D':
		case 'E': case 'F': case 'G': case 'H':
		case 'I': case 'J': case 'K': case 'L':
			return 3;
			break;
	}
}

num add(num, num);
num sub(num, num);
num mul(num, num);
num divi(num, num);
num mod(num, num);

num getpi(num t) {
	t.bd[0] = '3';
	t.bd[1] = '1';
	t.bd[2] = '4';
	t.bd[3] = '1';
	t.bd[4] = '5';
	t.bd[5] = '9';
	t.bd[6] = '2';
	t.bd[7] = '6';
	t.bd[8] = '5';
	t.bd[9] = '3';
	t.bd[10] = '5';
	t.bd[11] = '8';
	t.bd[12] = '9';
	t.bd[13] = '7';
	t.bd[14] = '9';
	t.bd[15] = '3';
	t.bd[16] = '2';
	t.bd[17] = '3';
	t.bd[18] = '8';
	t.bd[19] = '4';
	t.bd[20] = '6';
	t.bd[21] = '2';
	t.bd[22] = '6';
	t.bd[23] = '4';
	t.bd[24] = '3';
	t.bd[25] = '3';
	t.bd[26] = '8';
	t.bd[27] = '3';
	t.bd[28] = '2';
	t.bd[29] = '7';
	t.bd[30] = '9';
	t.bd[31] = '5';
	t.bd[32] = '0';
	t.bd[33] = '2';
	t.bd[34] = '8';
	t.bd[35] = '8';
	t.bd[36] = '4';
	t.bd[37] = '1';
	t.bd[38] = '\0';
	t.bi = 38;
	return t;
}

num adz(num t, int i) {
	if(i == 0)
		return t; 
	int j = t.bi;
	while(j > -1)
		t.bd[j + i] = t.bd[j--];
	j = 0;
	t.bi += i; 
	while(j < i)
		t.bd[j++] = '0';
	return t;
}

num adza(num t, int i) {
	int j = 0;
	while(j < i)
		t.ad[t.ai + j++] = '0';
	t.ad[t.ai + i] = '\0';
	t.ai += i;
	return t;
}

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

num add(num x, num y) {
	if(x.sign != y.sign) {
		if(x.sign == 1) {
			x.sign = 0;
			return sub(x, y);
		}
		else {
			y.sign = 0;
			return sub(y, x);
		}
	}
	int i = 0;
	if(x.ai >= y.ai) {
		while(i < y.ai) {
			x.ad[i] = x.ad[i] + y.ad[i] - '0';
			i++;
		}
		i--;
		while(i > 0) {
			if(x.ad[i] > '9') {
				x.ad[i - 1]++;
				x.ad[i] -= 10;
			}
			i--;
		}
		if(x.ad[0] > '9') {
			x.bd[x.bi - 1]++;
			x.ad[0] -= 10;
		}
	}
	else {
		while(i < x.ai) {
			y.ad[i] = x.ad[i] + y.ad[i] - '0';
			i++;
		}
		i--;
		while(i > 0) {
			if(y.ad[i] > '9') {
				y.ad[i - 1]++;
				y.ad[i] -= 10;
			}
			i--;
		}
		if(y.ad[0] > '9') {
			y.bd[x.bi - 1]++;
			y.ad[0] -= 10;
		}
	}
	if(x.bi > y.bi) {
		i = x.bi - 1;
		y = adz(y, x.bi - y.bi + 1);
		while(i > -1) {
			y.bd[i + 1] = y.bd[i + 1] + x.bd[i] - '0';
			if(y.bd[i + 1] > '9') {
				y.bd[i]++;
				y.bd[i + 1] -= 10;
			}
			i--;
		}
		y = rmz(y);
		y = rmza(y);
		return y;
	}
	else {
		i = y.bi - 1;
		x = adz(x, y.bi - x.bi + 1);
		while(i > -1) {
			x.bd[i + 1] = x.bd[i + 1] + y.bd[i] - '0';
			if(x.bd[i + 1] > '9') {
				x.bd[i]++;
				x.bd[i + 1] -= 10;
			}
			i--;
		}
		x = rmz(x);
		x = rmza(x);
		return x;
	}
}
num sub(num x, num y) {
	if(x.sign != y.sign) {
		if(x.sign == 1) {
			x.sign = 0;
			return add(x, y);
		}
		else {
			x.sign = 1;
			return add(x, y);
		}	
	}
	x = rmz(x);
	y = rmz(y);
	int i;
	if(y.bi == x.bi) {
		i = 0;
		int flag = 0;
		while(i < x.bi) {
			if(x.bd[i] > y.bd[i]) {
				flag = 2;
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
			while(i < x.ai) {
				if(x.ad[i] > y.ad[i]) {
					flag = 2;
					break;
				}
				else if(x.ad[i] < y.ad[i]) {
					flag = 1;
					break;
				}
				i++;
			}	
		}
		if(flag == 0) {
			y.ai=0;
			y.bi=1;
			y.sign = 0;
			y.bd[0] = '0';
			y.bd[1] = '\0';
			y.ad[0] = '\0';
			return y;
		}
		else if(flag == 1) {
			i = x.ai - y.ai;
			if(i > 0)
				y = adza(y, i);
			else 
				x = adza(x, i * -1);
			i = y.ai - 1;
			while(i > -1) {
				y.ad[i] = y.ad[i] - x.ad[i] + '0';
				if(y.ad[i] < '0') {
					if(i == 0) {
						y.bd[y.bi - 1]--;
						y.ad[i] += 10;
						
					}	
					else {
						y.ad[i - 1]--;
						y.ad[i] += 10;
					}
				}
				i--;
			}
			y = rmza(y);
			i = x.bi - 1;
			while(i > -1) {
				y.bd[i] = y.bd[i] - x.bd[i] + '0';
				if(y.bd[i] < '0') {
					y.bd[i - 1]--;
					y.bd[i] += 10;
				}
				i--;
			}
			return rmz(y);
		}
		else {
			i = y.ai - x.ai;
			if(i > 0)
				x = adza(x, i);
			else
				y = adza(y, i * -1);
			i = y.ai - 1;
			while(i > -1) {
				x.ad[i] = x.ad[i] - y.ad[i] + '0';
				if(x.ad[i] < '0') {
					if(i == 0) {
						x.bd[x.bi - 1]--;
						x.ad[i] += 10;
					}	
					else {
						x.ad[i - 1]--;
						x.ad[i] += 10;
					}
				}
				i--;
			}
			x = rmza(x);
			i = x.bi - 1;
			while(i > -1) {
				x.bd[i] = x.bd[i] - y.bd[i] + '0';
				if(x.bd[i] < '0') {
					x.bd[i - 1]--;
					x.bd[i] += 10;
				}
				i--;
			}
			x.sign = 1;
			return rmz(x);
		}
	}
	else if(y.bi > x.bi) {
		i = x.ai - y.ai;
		if(i > 0)
			y = adza(y, i);
		else
			x = adza(x, i * -1);
		i = y.ai - 1;
		while(i > -1) {
			y.ad[i] = y.ad[i] - x.ad[i] + '0';
			if(y.ad[i] < '0') {
				if(i == 0) {
					y.bd[y.bi - 1]--;
					y.ad[i] += 10;					
				}	
				else {
					y.ad[i - 1]--;
					y.ad[i] += 10;
				}
			}
			i--;
		}
		y = rmza(y);
		x = adz(x, y.bi - x.bi);
		i = y.bi - 1;
		while(i > -1) {
			y.bd[i] = y.bd[i] - x.bd[i] + '0';
			if(y.bd[i] < '0') {
				y.bd[i - 1]--;
				y.bd[i] += 10;
			}
			i--;
		}
		return rmz(y);
	}
	else {
		i = y.ai - x.ai;
		if(i > 0)
			x = adza(x, i);
		else
			y = adza(y, i * -1);
		i = y.ai - 1;
		while(i > -1) {
			x.ad[i] = x.ad[i] - y.ad[i] + '0';
			if(x.ad[i] < '0') {
				if(i == 0) {
					x.bd[x.bi - 1]--;
					x.ad[i] += 10;
				}	
				else {
					x.ad[i - 1]--;
					x.ad[i] += 10;
				}
			}
			i--;
		}
		x = rmza(x);
		i = x.bi - 1;
		y = adz(y, x.bi - y.bi);
		while(i > -1) {
			x.bd[i] = x.bd[i] - y.bd[i] + '0';
			if(x.bd[i] < '0') {
				x.bd[i - 1]--;
				x.bd[i] += 10;
			}
			i--;
		}
		x.sign = 1;
		x = rmz(x);
		return x;
	}
}
num mul(num x, num y) {
	num res;
	res.bi = 0;
	res.ai = 0;
	res.ad[0] = '\0';
	res.bd[0] = '\0';
	int i = 0, j = 0, m;	
	strcat(x.bd, x.ad);
	strcat(y.bd, y.ad);
	if(x.bi + x.ai > y.bi + y.ai)
		y = adz(y, x.bi + x.ai - y.ai - y.bi);
	else if(x.bi + x.ai < y.bi + y.ai)
		x = adz(x, y.bi + y.ai - x.bi - x.ai);
	res = adz(res, x.bi + x.ai + y.ai + y.bi);
	while(i < y.bi + y.ai) {
		j = 0;
		while(j < x.bi + x.ai) {
			m = (x.bd[j] - '0') * (y.bd[i] - '0');
			res.bd[i + j + 1] += m % 10;
			res.bd[i + j] += m / 10;
			j++;
		}
		i++;
	}
	i = x.bi + y.bi + x.ai + y.ai - 1;
	while(i > -1) {
		while(res.bd[i] > '9') {
			res.bd[i - 1] += 1;
			res.bd[i] -= 10;
		}
		i--;
	}
	res.ai = x.ai + y.ai;
	res.bi -= res.ai;
	i = res.bi;
	j = 0;
	while(j < res.ai) {
		res.ad[j] = res.bd[res.bi + j];
		j++;
	}
	res.ad[res.ai] = '\0';
	res.bd[res.bi] = '\0';
	if(x.sign == y.sign)
		res.sign = 0;
	else
		res.sign = 1;
	res = rmza(res);
	return rmz(res);
}
num divi(num x, num y) {
	num q, r, b;
	q.bd[0] = '\0';
	q.sign = 0;
	q.ad[0] = '\0';
	q.ai = q.bi = 0;
	r = q;
	strcat(x.bd, x.ad);
	strcat(y.bd, y.ad);
	if(x.sign == y.sign)
		q.sign = 0;
	else
		q.sign = 1;
	x.sign = y.sign = 0;
	x.bi += x.ai;
	y.bi += y.ai;
	q.ai = y.ai - x.ai;
	x.ai = y.ai = 0;
	x.ad[0] = y.ad[0] = '0';
	int i = 0, j;
	while(i < y.bi) {
		j = -1;
		r.bd[r.bi] = y.bd[i];
		r.bd[r.bi + 1] = '\0';
		r.bi ++;
		b = r;
		while(b.sign == 0) {
			b = sub(x, b);
			j++;
		}
		r = add(x, b);
		q.bd[i] = j + 48;
		i++;
	}
	q.bd[i] = '\0';
	q.bi = i;
	r = rmz(r);
	if(lflag == 1 && r.bi != 0) {
		i = 0;
		while(i < 7) {
			j = -1;
			r.bd[r.bi] = '0';
			r.bd[r.bi + 1] = '\0';
			r.bi ++;
			b = r;
			while(b.sign == 0) {
				b = sub(x, b);
				j++;
			}
			r = add(x, b);
			q.bd[q.bi + i] = j + 48;
			i++;
		}
		q.bi += i;
		q.bd[q.bi] = '\0';
		q.ai += 7;
	}
	q.bi -= q.ai;
	if(lflag == 0) {
		q.ai = 0;
	}
	else {
		j = 0;
		while(j < q.ai) {
			q.ad[j] = q.bd[q.bi + j];
			j++;
		}
	}
	q.ad[q.ai] = '\0';
	q.bd[q.bi] = '\0';
	q = rmza(q);
	return rmz(q);
}
num mod(num x, num y) {
	num r, b;
	r.bd[0] = '\0';
	r.sign = 0;
	r.ad[0] = '\0';
	r.ai = r.bi = 0;
	int i = 0, j, k;
	if(x.ai > y.ai) {
		k = x.ai;
		j = x.ai - y.ai;
		y = adza(y, j);
	}
	else if(x.ai < y.ai) {
		k = y.ai;
		j = y.ai - x.ai;
		x = adza(x, j);
	}
	else {
		k = j = x.ai;
	}
	strcat(x.bd, x.ad);
	strcat(y.bd, y.ad);
	x.bi += x.ai;
	y.bi += y.ai;
	x.ai = y.ai = 0;
	x.ad[0] = y.ad[0] = '\0';	
	while(i < y.bi) {
		j = -1;
		r.bd[r.bi] = y.bd[i];
		r.bd[r.bi + 1] = '\0';
		r.bi ++;
		b = r;
		while(b.sign == 0) {
			b = sub(x, b);
			j++;
		}
		r = add(x, b);
		i++;
	}
	r.bi -= k;
	j = 0;
	while(j < k) {
		r.ad[j] = r.bd[r.bi + j];
		j++;
	}
	r.ai = k;
	r.ad[r.ai] = '\0';
	r.bd[r.bi] = '\0';
	r = rmza(r);
	return rmz(r);
}

num solve(char op, num x, num y) {
	int flag = 0, i = 0, j;
	char str[30];
	str[0] = '.';
	num res, t;
	long double p = 0;
	t.bi = 1;
	t.bd[0] = '1';
	t.bd[1] = '\0';
	t.ai = 0;
	t.ad[0] = '\0';
	t.sign = 0;
	switch(op) {
		case '+':
			return add(x, y);
			break;
		case '-':
			return sub(x, y);
			break;
		case '*':
			return mul(x, y);
			break;
		case '/':
			x = rmz(x);
			if(x.bi == 0 && x.ai == 0) {
				printf("division by 0 \n");
				error = 1;
				return y;
			}
			else
				return divi(x, y);
			break;
		case '%':
			x = rmz(x);
			if(x.bi == 0 && x.ai == 0) {
				printf("mod by 0 \n");
				error = 1;
				return x;
			}
			else
				return mod(x, y);
			break;
		case '^':
			x = rmz(x);
			x = rmza(x);
			if(x.ai != 0) {
				printf("exponent must be integer");
				error = 1;
				return x;
			}
			else if(x.bi == 0)
				return t;
			else if(x.bi == 1 && x.bd[0] == '1' && x.sign == 0)
				return y;
			else {
				if(x.sign == 0) {
					res = y;
					x = sub(t, x);
					while(x.bi > 0) {
						res = mul(res, y);
						x = sub(t, x);
						x=rmz(x);
					}
				}
				else {
					res = t;
					x.sign = 0;
					
					while(x.bi > 0) {
						res = divi(y, res);
						x = sub(t, x);
						x=rmz(x);
					}
				}
			}
			return res;
			break;			
		case 'a': case 'b':
			if(x.bi > 38) {
				t = getpi(t);
				while(x.bi > 38) {
					x = sub(t, x);
					x = rmz(x);
				}
				t.bi = 1;
				t.bd[0] = 1;
				t.bd[1] = '\0';
			}
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			switch(op) {
				case 'a':
					p = sin(p);
					break;
				case 'b':
					p = cos(p);
					break;
			}
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			if(((int)p))
				return t;
			while(i < 6) {
				t.ad[i] = 48 + (int)(p * 10);
				p = (p * 10) -(int)(p * 10);
				i++;
			}
			t.ad[i] = '\0';
			t.ai = 6;
			t.bd[0] = '\0';
			t.bi = 0;
			return t;
			break;
		case 'c': case 'd': case 'e': case 'f':
			if(x.bi > 38) {
				t = getpi(t);
				while(x.bi > 38) {
					x = sub(t, x);
					x = rmz(x);
				}
				t.bi = 1;
				t.bd[0] = 1;
				t.bd[1] = '\0';
			}
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			switch(op) {
				case 'c':
					p = tan(p);
					break;
				case 'd':
					p = 1 / tan(p);
					break;
				case 'e':
					p = 1 / cos(p);
					break;
				case 'f':
					p = 1 / sin(p);
					break;
			}
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			while(p > 1) {
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
			return t;
			break;
		case 'g': case 'h': case 'i':
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			if(op == 'g')
				p = log(p) / log(10);
			else if(op == 'h')
				p = log(p);
			else
				p = exp(p);
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			while(p > 1) {
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
			return t;
			break;
		case 'j':
			if(x.sign == 1) {
				error = 1;
				printf("squareroot of negative number is not real\n");
				return x;
			}
			strcat(str, x.ad);
			p = atof(x.bd) + atof(str);
			p = sqrt(p);
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			while(p > 1) {
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
			return t;
			break;
		case 'k':
			p = atof(x.bd) + atof(str);
			p = sqrt(p);
			i = 0;
			if(p < 0) {
				t.sign = 1;
				p *= -1;
			}
			while(p > 1) {
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
			return t;
			break;
		case 'l':
			x = rmz(x);
			y = rmz(y);
			if(!((x.ai + x.bi) && (y.ai + y.bi)))
				t.bd[0] = '0';
			return t;
			break;
		case 'm':
			x = rmz(x);
			y = rmz(y);
			if(!((x.ai + x.bi) || (y.ai + y.bi)))
				t.bd[0] = '0';
			return t;
			break;
		case 'n': case 'p':
			x = rmz(x);
			y = rmz(y);
			if(x.bi > y.bi)
				t.bd[0] = '0';
			else if(x.bi == y.bi) {
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
			return t;
			break;
		case 'o': case 'q':
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
			return t;
			break;
		case 'r':
			return x;// '=' optr
			break;
		case 's':
			x = rmz(x);
			y = rmz(y);
			x = rmza(x);
			y = rmza(y);
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
			return t;
			break;
		case 'A':
			i = x.bi % 3;
			if(i)
				x = adz(x, 3 - i);
			i = 0;
			while(i < x.bi) {
				t.bd[i / 3] = 48;
				if(x.bd[i] == '1')
					t.bd[i / 3] += 4;
				else if(x.bd[i] != '0')
					error = 1;
				if(x.bd[i + 1] == '1')
					t.bd[i / 3] += 2;
				else if(x.bd[i + 1] != '0')
					error = 1;
				if(x.bd[i + 2] == '1')
					t.bd[i / 3] += 1;
				else if(x.bd[i + 2] != '0')
					error = 1;
				i += 3;
			}
			t.bd[i / 3] = '\0';
			t.bi = i / 3;
			if(lflag == 1) {
				i = x.ai % 3;
				if(i)
					x = adza(x, 3 - i);
				i = 0;
				while(i < x.ai) {
					t.ad[i / 3] = 48;
					if(x.ad[i] == '1')
						t.ad[i / 3] += 4;
					else if(x.ad[i] != '0')
						error = 1;
					if(x.ad[i + 1] == '1')
						t.ad[i / 3] += 2;
					else if(x.ad[i + 1] != '0')
						error = 1;
					if(x.ad[i + 2] == '1')
						t.ad[i / 3] += 1;
					else if(x.ad[i + 2] != '0')
						error = 1;
					i += 3;
				}
				t.ad[i / 3] = '\0';
				t.ai = i / 3;
			}
			return t;/*bo*/
			break;
		case 'B':
			while(i < x.bi) {
				if(x.bd[i] == '1')
					p += pow(2, x.bi - i - 1);
				else if(x.bd[i] != '0') {
					error = 1;
					return x;
				}
				i++;
			}
			if(lflag == 1) {
				i = 0;
				while(i < x.ai) {
					if(x.ad[i] == '1')
						p += pow(2, -(1 + i));
					else if(x.ad[i] != '0') {
						error = 1;
						return x;
					}
					i++;
				}
			}
			i = 0;
			while(p > 1) {
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
			return t;/*bd*/
			break;
		case 'C':
			i = x.bi % 4;
			if(i)
				x = adz(x, 4 - i);
			i = 0;
			while(i < x.bi) {
				t.bd[i / 4] = 48;
				if(x.bd[i] == '1')
					t.bd[i / 4] += 8;
				else if(x.bd[i] != '0')
					error = 1;
				if(x.bd[i + 1] == '1')
					t.bd[i / 4] += 4;
				else if(x.bd[i + 1] != '0')
					error = 1;
				if(x.bd[i + 2] == '1')
					t.bd[i / 4] += 2;
				else if(x.bd[i + 2] != '0')
					error = 1;
				if(x.bd[i + 3] == '1')
					t.bd[i / 4] += 1;
				else if(x.bd[i + 3] != '0')
					error = 1;
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
				while(i < x.ai) {
					t.ad[i / 4] = 48;
					if(x.ad[i] == '1')
						t.ad[i / 4] += 8;
					else if(x.ad[i] != '0')
						error = 1;
					if(x.ad[i + 1] == '1')
						t.ad[i / 4] += 4;
					else if(x.ad[i + 1] != '0')
						error = 1;
					if(x.ad[i + 2] == '1')
						t.ad[i / 4] += 2;
					else if(x.ad[i + 2] != '0')
						error = 1;
					if(x.ad[i + 3] == '1')
						t.ad[i / 4] += 1;
					else if(x.ad[i + 3] != '0')
						error = 1;
					if(t.ad[i / 4] > '9')
						t.ad[i / 4] += 7;
					i += 4;
				}
				t.ad[i / 4] = '\0';
				t.ai = i / 4;
			}
			return t;/*bh*/
			break;
		case 'D':
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
						error = 1;
						return x;
						break;
				}
				i++;
			}
			t.bi = 3 * x.bi;
			if(lflag == 1) {
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
							error = 1;
							return x;
							break;
					}
					i++;
				}
				t.ai = 3 * x.ai;
			}
			return t;/*ob*/
			break;
		case 'E':
			while(i < x.bi) {
				if(x.ad[i] >= '0' || x.ad[i] <= '9')
					p += ((pow(8, x.bi - i - 1)) * (x.bd[i] - 48));
				else {
					error = 1;
					return x;
				}
				i++;
			}
			if(lflag == 1) {
				i = 0;
				while(i < x.ai) {
					if(x.ad[i] >= '0' || x.ad[i] <= '9')
						p += ((pow(8, -(1 + i))) * (x.ad[i] - 48));
					else {
						error = 1;
						return x;
					}
					i++;
				}
			}
			i = 0;
			while(p > 1) {
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
			return t;/*bd*/
			break;
		case 'F':
			x = solve('D', x, x);
			x = solve('C', x, x);
			return x;/*oh*/
			break;
		case 'G':
			return x;/*db*/
			break;
		case 'H':
			return x;/*do*/
			break;
		case 'I':
			return x;/*dh*/
			break;
		case 'J':
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
						error = 1;
						break;
				}
				i++;
			}
			t.bi = 4 * x.bi;
			if(lflag == 1) {
				t.ad[0] = '\0';
				while(i < x.ai) {
					switch(x.bd[i]) {
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
							error = 1;
							break;
					}
				i++;
				}
				t.ai = 4 * x.ai;
			}
			return t;/*hb*/
			break;
		case 'K':
			x = solve('J', x, x);
			x = solve('A', x, x);
			return x;/*ho*/
			break;
		case 'L':
			while(i < x.bi) {
				if(x.ad[i] >= '0' && x.ad[i] <= '9')
					p += ((pow(16, x.bi - i - 1)) * (x.bd[i] - 48));
				else if(x.ad[i] >= 'A' && x.ad[i] <= 'F')
					p += ((pow(16, x.bi - i - 1)) * (x.bd[i] - 'A' + 10));
				else {
					error = 1;
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
						error = 1;
						return x;
					}
					i++;
				}
			}
			i = 0;
			while(p > 1) {
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
			return t;/*bd*/
			break;
		default:
			error = 1;
			return x;
			break;				
	}

}


char ctop(stackc *b) {
	char optr = popc(b);
	pushc(b, optr);
	return optr;
}



num infixeval(char *str) {
	token *t;
	num result, x, y;
	int  pretok = 0, flag = 0, curtok = 0;
	stacki a;
	initi(&a);
	stackc b;
	initc(&b);
	char optr;
	int reset = 1, h = 0, p, q;
	while(1) {
		t = getnext(str, &reset);
		if(error == 1)
			return x;
		curtok = t->type;
		if(curtok == pretok && pretok == OPERAND) {
			error = 1;
			return x;
		}
		if((curtok == pretok || emptyi(&a)) && t->op == '-') {		/*if int_stack is empty then '-' is 1st char of string*/
			if(!fulli(&a)) {
				x.bd[0] = '1';
				x.bi = 1;
				x.ad[0] = '\0';
				x.ai = 0;
				x.bd[1] = '\0';
				x.sign = 1;
				pushi(&a, x);
			}
			else {
				error = 1;
				stackfull = 1;
				return x;
			}
			if(!fullc(&b))
				pushc(&b, '*');
			else {
				error = 1;
				stackfull = 1;
				return x;
			}
			continue;
		}
		if(t->type == END && h != 0) {
			error = 1;
			return x;
		}
		if(t->type == OPERAND) {
			if(!fulli(&a))
				pushi(&a, t->number);
			else {
				error = 1;
				stackfull = 1;
				return x;
			}
		}
		else if (t->type == OPERATOR) {
			if(t->op == '(')
				h++;
			else if(t->op == ')')
				h--;
			if(!emptyc(&b)) {
				optr = ctop(&b);
				if(optr == 'r') {
					error = 1;
					return x;
				}
				p = precedence(optr);
				q = precedence(t->op);
				if(q > p) {
					if(!fullc(&b))	
						pushc(&b, t->op);
					else {
						error = 1;
						stackfull = 1;
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
						        optr == 'J' || optr == 'K' || optr == 'L') {
							if(!emptyi(&a))
								x = popi(&a);
							else {
								error = 1;
								return x;						
							}
							result = solve(optr, x, x);
//							free(x);
							pushi(&a, result);
							if(!emptyc(&b)) {
								optr = ctop(&b);
								p = precedence(optr);
							}
							else
								break;
						}
						else{
							if(!emptyi(&a))
								x = popi(&a);
							else {
								error = 1;
								return x;
							}
							if(!emptyi(&a))
								y = popi(&a);
							else {
								error = 1;
								return x;
							}
							result = solve(optr, x, y);
//							free(x);
//							free(y);
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
					   optr == 'J' || optr == 'K' || optr == 'L') {
						if(!emptyi(&a))
							x = popi(&a);
						else {
							error = 1;
							return x;
						}
						result = solve(optr, x, x);
//						free(x);
						pushi(&a, result);
					}
					else {
						if(!emptyi(&a))
							x = popi(&a);
						else {
							error = 1;
							return x;
						}
						if(!emptyi(&a))
							y = popi(&a);
						else {
							error = 1;
							return x;
						}
						result = solve(optr, x, y);
//						free(y);
//						free(x);
						pushi(&a, result);
					}
				}
				return result;
			}
			else {
				x = popi(&a);		/*no need to check if int_stack is empty because there has to be a number*/	
				if(!emptyi(&a)) {
					error = 1;
					return x;
				}
				else 
					return x;
			}
		} 
		else if (t->type == ERROR) {
			error = 1;
			return x; 
		}
		pretok = curtok;
	}
	free(t);
}

void printusage() {
	printf("usage:  ./a.out  [option]\n\noption\tdescription\n-l    \ttrigonometric, log, ln and e^(expression) options\n-h    \thelp and exit\n--help\thelp and exit\n");
}

int main(int argc,char *argv[]) {
	char str[128];
	int q = 1;
	while(q < argc) {
		if((strcmp(argv[q], "-h") == 0) || (strcmp(argv[q], "--help") == 0)) {
			printusage();
			return 0;
		}
		else if(strcmp(argv[q], "-l") == 0)
			lflag = 1;
		else {
			printf("invalid option ... '%s'\n", argv[q]);
			printusage();
			return 0;
		}
		q++;
	}
	num ans;
	int x;
	num infixeval(char *infix);
	while(printf("> ") && (x = readline(str, 128))) {
		ans = infixeval(str);
		if(error == 1) {
			if(stackfull == 1) {
				fprintf(stderr, "exprression is too long ... stack is full\n");
				stackfull = 0;
			}
			else
				fprintf(stderr, "Error in expression\n");
			error = 0;
		}
		else {
			if(ans.sign == 1) 
				printf("-");
			if(ans.bi == 0)
				printf("0");
			if((dflag == 1 || lflag == 1) && (ans.ai != 0)) {
				strcat(ans.bd, ".");
				strcat(ans.bd, ans.ad);
				puts(ans.bd);
			}	
			else {
				puts(ans.bd);				
			}
		}
		dflag = 0;
	}
//	free(ans);
	return 0;
}
