#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"
#include <math.h>
  
int lflag = 0, dflag = 0, stackfull = 0;

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
	long double number;
	char op;
}token;



enum states { SPC, DIG, OPR, ALPH, STOP, ERR };
token *getnext(char *arr, int *reset) {
	static int currstate = SPC;
	int nextstate;
	static int i = 0;
	static long double bd, ad;
	if(*reset == 1) {
		i = 0;
		currstate = SPC;
		*reset = 0;
	}
	
	char *expre = (char *)malloc(sizeof(char) * 7);
	char ope(char*);
	int x, flag = 0;
	token *t = (token *)malloc(sizeof(token));
	if(currstate == ALPH) {
		x = 0;
		*(expre + x) = arr[i - 1];
		x++;
	}
	if(arr[i] == '.') {
		dflag = 1;
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
				if(nextstate == DIG && arr[i] != '.')
					bd = arr[i] - '0';	
				else if(nextstate == ALPH) {
					x = 0;
					*(expre + x) = arr[i];
					x++;
				}		
				break;
			case DIG:
				if(arr[i] == '.') {
				flag = 1;
				break;
				}
				if(nextstate == DIG && flag != 1) 
					bd = bd * 10 + arr[i] - '0';
				else if(nextstate == DIG && flag == 1) {
					ad = ad * 10 + arr[i] - '0';
				}	
				else if(nextstate == ALPH) {
					x = 0;
					*(expre + x) = arr[i];
					x++;
				}
				else  {
					flag = 0;
					while(((int)ad))
						ad /= 10;
					t->type = OPERAND;
					t->number = bd + ad;
					ad = 0;
					i++;
					currstate = nextstate;
					return t;
				}
				break;
			case ALPH:
				if(nextstate == DIG && arr[i] != '.')
					bd = arr[i] - '0';
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
					i++;
					currstate = nextstate;
					return t;
				}
				break;
			case OPR:
				if(nextstate == DIG && arr[i] != '.')
					bd = arr[i] - '0';
				t->type = OPERATOR;
				t->op = arr[i - 1];	
				currstate = nextstate;
				i++;
				return t;
				break;
			case STOP:
				t->type = END;
				currstate = nextstate;
				free(expre);
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
	else
		return '1';
}

int precedence(char b) {
	switch(b) {
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
		case 'l': case 'k': case 'j': case 'i':
		case 'm': case 'n': case 'o':		
			return 3;
			break;
		default:
			return INT_MIN;
			break;
	}
}

long double solve(char op, long double x, long double y) {
	switch(op) {
		case '+':
			return (y + x);
			break;
		case '-':
			return (y - x);
			break;
		case '*':
			return (y * x);
			break;
		case '/':
			if(x == 0) {
				printf("division by 0 ");
				return INT_MIN;
			}
			if(lflag == 1)
				return (y / x);
			else {
				if(((int)x) == 0) {
					printf("division by 0 ");
					return INT_MIN;
				}
				else
					return ((int)y / (int)x);
			}
			break;
		case '%':
			if(((int)x) == 0) {
				printf("mod by 0 ");
				return INT_MIN;
			}
			else
				return ((int)y % (int)x);
			break;
		case '^':
			if(x == 0)
				return 1;
			else
				return powf(y, x);
			break;			
		case 'a':
			return sin(x);
			break;
		case 'b':
			return cos(x);
			break;
		case 'c':
			return tan(x);
			break;
		case 'd':
			return (1 / tan(x));
			break;
		case 'e':
			return (1 / cos(x));
			break;
		case 'f':
			return (1 / sin(x));
			break;
		case 'g':
			return (log(x) / log(10));
			break;
		case 'h':
			return log(x);
			break;
		case 'i':
			return exp(x);
			break;
		case 'j':
			return sqrt(x);
			break;
		case 'k':
			return cbrt(x);
			break;
		case 'l':
			return (y && x);
			break;
		case 'm':
			return (y || x);
			break;
		case 'n':
			return (y > x);
			break;
		case 'o':
			return (y < x);
			break;
		case 'p':
			return (y >= x);
			break;			
		case 'q':
			return (y <= x);
			break;			
		default:
			return INT_MIN;
			break;				
	}

}


char ctop(stackc *b) {
	char optr = popc(b);
	pushc(b, optr);
	return optr;
}



long double infixeval(char *str) {
	token *t;
	long double result, x, y;
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
		if(curtok == pretok && pretok == OPERAND)
			return INT_MIN;
		if((curtok == pretok || emptyi(&a)) && t->op == '-') {		/*if int_stack is empty then '-' is 1st char of string*/
			if(!fulli(&a))		
				pushi(&a, -1);
			else {
				stackfull = 1;
				return INT_MIN;
			}
			if(!fullc(&b))
				pushc(&b, '*');
			else {
				stackfull = 1;
				return INT_MIN;
			}
			continue;
		}
		if(t->type == END && h != 0)
			return INT_MIN;
		if(t->type == OPERAND) {
			if(!fulli(&a))
				pushi(&a, t->number);
			else {
				stackfull = 1;
				return INT_MIN;
			}
		}
		else if (t->type == OPERATOR) {
			if(t->op == '(')
				h++;
			else if(t->op == ')')
				h--;
			if(!emptyc(&b)) {
				optr = ctop(&b);
				p = precedence(optr);
				q = precedence(t->op);
				if(q > p) {
					if(!fullc(&b))	
						pushc(&b, t->op);
					else {
						stackfull = 1;
						return INT_MIN;
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
						        optr == 'i' || optr == 'j' || optr == 'k' || optr == 'l' || 
						        optr == 'o' || optr == 'n' || optr == 'm') {
							if(!emptyi(&a))
								x = popi(&a);
							else
								return INT_MIN;						
							result = solve(optr, x, 1);
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
							else
								return INT_MIN;
							if(!emptyi(&a))
								y = popi(&a);
							else
								return INT_MIN;
							result = solve(optr, x, y);
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
					   optr == 'i' || optr == 'j' || optr == 'k' || optr == 'l' || 
					   optr == 'o' || optr == 'n' || optr == 'm') {
						if(!emptyi(&a))
							x = popi(&a);
						else
							return INT_MIN;						
						result = solve(optr, x, 1);
						pushi(&a, result);
					}
					else {
						if(!emptyi(&a))
							x = popi(&a);
						else
							return INT_MIN;
						if(!emptyi(&a))
							y = popi(&a);
						else
							return INT_MIN;
						result = solve(optr, x, y);
						pushi(&a, result);
					}
				}
				return result;
			}
			else {
				x = popi(&a);		/*no need to check if int_stack is empty because there has to be a number*/	
				if(!emptyi(&a))
					return INT_MIN;
				else 
					return x;
			}
		} 
		else if (t->type == ERROR) 
			return INT_MIN; 
		pretok = curtok;
	}
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
	long double ans;
	int x;
	long double infixeval(char *infix);
	while(printf("> ") && (x = readline(str, 128))) {
		ans = infixeval(str);
		if(ans == INT_MIN) {
			if(stackfull == 1) {
				fprintf(stderr, "exprression is too long ... stack is full\n");
				stackfull = 0;
			}
			else
				fprintf(stderr, "Error in expression\n");
		}
		else {
			if(dflag == 1 || lflag == 1)
				fprintf(stdout, "\t%Lf\n", ans);
			else
				fprintf(stdout, "\t%.0Lf\n", ans);
		}
		dflag = 0;
	}
	return 0;
}
