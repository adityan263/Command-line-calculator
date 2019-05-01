
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

char ctop(stackc *b) {
	char optr = popc(b);
	pushc(b, optr);
	return optr;
}
