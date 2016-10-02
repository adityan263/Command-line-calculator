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

//printf("");getchar();

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
			case '8': case '9': case '.':
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
	else if(strcmp(expr, "sqrt") == 0)
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
	else
		return '1';
}

int precedence(char b) {
	switch(b) {
		case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'r': case 'q': 
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
			return 3;
			break;
	}
}

num add(num, num);
num sub(num, num);
num mul(num, num);
num divi(num, num);
num mod(num, num);

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
		y = rmz(y);
		return y;
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
//	float temp = atof(x.bd) + atof(x.ad);
	int flag = 0, i = 0;
	num res, t;
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
			}
			else if(x.bi == 0)
				return t;
			else if(x.bi == 1 && x.bd[0] == '1')
				return y;
			else {
				res = y;
				while(x.bd[0] != '1' && x.bi == 1) {
					res = mul(res, y);
					x = sub(t, x);
				}
			}
			return res;
			break;			
		case 'a':
return x;//			return sin(temp);
			break;
		case 'b':
return x;//			return cos(temp);
			break;
		case 'c':
return x;//			return tan(temp);
			break;
		case 'd':
return x;//			return (1 / tan(temp));
			break;
		case 'e':
return x;//			return (1 / cos(temp));
			break;
		case 'f':
return x;//			return (1 / sin(temp));
			break;
		case 'g':
return x;//			return (log(temp) / log(10));
			break;
		case 'h':
return x;//			return log(temp);
			break;
		case 'i':
return x;//			return exp(temp);
			break;
		case 'j':
return x;//			return sqrt(temp);
			break;
		case 'k':
return x;//			return cbrt(temp);
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
						        optr == 'i' || optr == 'j' || optr == 'k') {
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
					   optr == 'i' || optr == 'j' || optr == 'k') {
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
			printf("\t");
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
