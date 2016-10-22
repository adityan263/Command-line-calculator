#include "stack.h"
#include <stdlib.h>



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


num initnum(num p){
	p.bd = (char *)malloc(sizeof(char) * 30);
	p.ad = (char *)malloc(sizeof(char) * 30);
	p.sign = p.ai = p.bi = 0;
	p.blimit = p.alimit = 30;
	p.bd[0] = p.ad[0] = '\0';
	return p;
}
num areinitnum(num p) {
	p.alimit += 50;
	p.ad = (char *)realloc(p.ad, sizeof(char) * p.alimit);
	return p;
}
num breinitnum(num p) {
	p.blimit += 50;
	p.bd = (char *)realloc(p.bd, sizeof(char) * p.blimit);
	return p;
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
