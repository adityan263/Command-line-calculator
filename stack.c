#include "stack.h"




void pushi(stacki *s, num numb) {
	s->a[s->i]= numb;
	(s->i)++;
}
num popi(stacki *s) {
	num t;
	t = s->a[s->i - 1];
	(s->i)--;
	return t;
}
int emptyi(stacki *s) {
	return s->i == 0;
}
int fulli(stacki *s) {
	return s->i == MAX;
}
void initi(stacki *s) {
	s->i = 0;
}




void pushc(stackc *s, char op) {
	s->b[s->j]= op;
	(s->j)++;
}
char popc(stackc *s) {
	char t = s->b[s->j - 1];
	(s->j)--;
	return t;
}
int emptyc(stackc *s) {
	return s->j == 0;
}
int fullc(stackc *s) {
	return s->j == MAX;
}
void initc(stackc *s) {
	s->j = 0;
}
