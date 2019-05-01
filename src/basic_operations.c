
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

#include <stdlib.h>
#include <string.h>

#include "basic_operations.h"

num add(num x, num y, int ope, int pwr) {
	if(x.sign != y.sign) {
		if(x.sign == 1) {
			x.sign = 0;
			return sub(x, y, ope, pwr);
		}
		else {
			y.sign = 0;
			return sub(y, x, ope, pwr);
		}
	}
	int i = 0, flag = 0;
	num res;
	res = initnum(res);
	/*addition of after decimal digits*/
	if(x.ai >= y.ai)
		res = adza(res, x.ai);
	else
		res = adza(res, y.ai);
	while(i < x.ai) {
		res.ad[i] = x.ad[i] + y.ad[i] - '0';
		i++;
	}	
	i--;
	/*clear carry for after decimal part*/
	while(i > 0) {
		if(res.ad[i] > '9') {
			res.ad[i - 1]++;
			res.ad[i] -= 10;
		}
		i--;
	}
	if(x.bi > y.bi) {
		res = adz(res, x.bi + 1);
		i = x.bi - 1;
		y = adz(y, x.bi - y.bi);
	}
	else {
		res = adz(res, y.bi + 1);
		i = y.bi - 1;
		x = adz(x, y.bi - x.bi);
	}
	/*addition of before decimal part
	 *first digit of res is reserved for carry
	 */
	while(i > -1) {
		res.bd[i + 1] = x.bd[i] + y.bd[i] - '0';
		if(flag == 1) {
			res.bd[i + 1]++;
			flag = 0;
		}
		if(res.bd[i + 1] > '9') {
			flag = 1;
			res.bd[i + 1] -= 10;
		}
		i--;
	}
	if(flag == 1) {
		res.bd[i + 1] = '1';
		flag = 0;
	}
	if(res.ad[0] > '9') {
		res.bd[res.bi - 1] += 1;
		res.ad[0] -= 10;
	}
	res = rmz(res);
	res = rmza(res);
	if(pwr == 0 && ope == 0) {
		free(x.bd);
		free(x.ad);
		free(y.bd);
		free(y.ad);
	}
	res.sign = y.sign;
	return res;
}
num sub(num x, num y, int ope, int pwr) {
	if(x.sign != y.sign) {
		if(x.sign == 1) {
			x.sign = 0;
			return add(x, y, ope, pwr);
		}
		else {
			x.sign = 1;
			return add(x, y, ope, pwr);
		}	
	}
	num res;
	res = initnum(res);
	x = rmz(x);
	y = rmz(y);
	int i = 0, bflag = 0, flag = 0;/*bflag => borrow flag*/
	i = 0;
	/*find bigger number to decide sign of result*/
	if(x.bi > y.bi)
		flag = 2;
	else if(y.bi > x.bi)
		flag = 1;
	else {
		/*if both numbers have same no. of digits then compare digit by digit*/
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
		/*if before decimal part is same compare after decimal digits*/
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
	}
	i = x.ai - y.ai;
	if(i > 0)
		y = adza(y, i);
	else
		x = adza(x, i * -1);
	res = adza(res, y.ai);
	i = y.ai - 1;
	/*if both no.s are equal retun zero*/
	if(flag == 0) {
		res.bi = 1;
		res.bd[0] = '0';
		res.bd[1] = '\0';
	}
	else if(flag == 1) {				/*y > x*/
		/*subtraction of after decimal part*/
		while(i > -1) {
			res.ad[i] = y.ad[i] - x.ad[i] + '0';
			if(bflag == 1)
				res.ad[i]--;
			bflag = 0;
			if(res.ad[i] < '0') {
				bflag = 1;
				res.ad[i] += 10;
			}
			i--;
		}
		res = rmza(res);
		x = adz(x, y.bi - x.bi);
		res = adz(res, y.bi);
		i = y.bi - 1;
		/*subtraction of after decimal part*/
		while(i > -1) {
			res.bd[i] = y.bd[i] - x.bd[i] + '0';
			if(bflag == 1)
				res.bd[i]--;
			bflag = 0;
			if(res.bd[i] < '0') {
				bflag = 1;
				res.bd[i] += 10;
			}
			i--;
		}
		res.sign = y.sign;
	}
	else {							/*x > y*/
		/*before decimal subtraction*/
		while(i > -1) {
			res.ad[i] = x.ad[i] - y.ad[i] + '0';
			if(bflag == 1)
				res.ad[i]--;
			bflag = 0;
			if(res.ad[i] < '0') {
				bflag = 1;
				res.ad[i] += 10;
			}
			i--;
		}
		res = rmza(res);
		i = x.bi - 1;
		res = adz(res, x.bi);
		y = adz(y, x.bi - y.bi);
		/*after decimal subtraction*/
		while(i > -1) {
			res.bd[i] = x.bd[i] - y.bd[i] + '0';
			if(bflag == 1)
				res.bd[i]--;
			bflag = 0;
			if(res.bd[i] < '0') {
				bflag = 1;
				res.bd[i] += 10;
			}
			i--;
		}
		if(!x.sign)
			res.sign = 1;
	}
	res = rmz(res);
	
	if(pwr == 0 && ope == 0) {
		free(y.bd);
		free(y.ad);
		free(x.bd);
		free(x.ad);
	}
	return res;
}

num mul(num x, num y, int pwr) {
	num res;
	res = initnum(res);
	int i = 0, j = 0, m;
	/*join bd and ad part*/
	strcat(x.bd, x.ad);
	strcat(y.bd, y.ad);
	if(x.bi + x.ai > y.bi + y.ai)
		y = adz(y, x.bi + x.ai - y.ai - y.bi);
	else if(x.bi + x.ai < y.bi + y.ai)
		x = adz(x, y.bi + y.ai - x.bi - x.ai);
	res = adz(res, x.bi + x.ai + y.ai + y.bi);
	/*multiplication*/
	while(i < y.bi + y.ai) {
		j = 0;
		while(j < x.bi + x.ai) {
			m = (x.bd[j] - '0') * (y.bd[i] - '0');
			res.bd[i + j + 1] += m % 10;
			res.bd[i + j] += m / 10;
			if(((i + 1) * j) % 15 == 0)
				res = carryclr(res, i + j);
			j++;
		}
		i++;
	}
	/*fix decimal point*/
	i = x.bi + y.bi + x.ai + y.ai - 1;
	res = carryclr(res, i);
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
	if(pwr == 0) {	
		free(x.bd);
		free(x.ad);
		free(y.bd);
		free(y.ad);
	}
	return rmz(res);
}
num divi(num x, num y, int lflag, int ope, int pwr) {
	num q, r, b;
	q = initnum(q);/*quotient*/
	r = initnum(r);/*remainder*/
	b = initnum(b);
	q = adz(q, y.bi);
	r = adz(r, x.bi);
	b = adz(b, x.bi);
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
	x.ad[0] = y.ad[0] = '\0';
	ope = 1;
	int i = 0, j;
	while(i < y.bi) {
		j = -1;
		r.bd[r.bi] = y.bd[i];
		r.bd[r.bi + 1] = '\0';
		r.bi ++;
		strcpy(b.bd, r.bd);
		strcpy(b.ad, r.ad);
		b.bi = r.bi;
		b.ai = r.ai;
		b.sign = r.sign;
		while(b.sign == 0) {			/*while( b is positive )*/
			x = rmz(x);
			b = sub(x, b, ope, pwr);	/* b = b - x */
			j++;
		}
		r = add(x, b, ope, pwr);
		q.bd[i] = j + 48;
		i++;
	}
	q.bd[i] = '\0';
	q.bi = i;
	r = rmz(r);
	/*find fractional part*/
	if(lflag == 1 && r.bi != 0) {
		i = 0;
		while(i < 7) {
			j = -1;
			r.bd[r.bi] = '0';
			r.bd[r.bi + 1] = '\0';
			r.bi ++;
			strcpy(b.bd, r.bd);
			strcpy(b.ad, r.ad);
			b.bi = r.bi;
			b.ai = r.ai;b.sign = r.sign;
			while(b.sign == 0) {
				b = sub(x, b, ope, pwr);
				j++;
			}
			r = add(x, b, ope, pwr);
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
	ope = 0;
	q = rmza(q);
	free(r.bd);
	free(r.ad);
	free(b.bd);
	free(b.ad);
	if(pwr == 0) {
		free(y.bd);
		free(y.ad);
		free(x.bd);
		free(x.ad);
	}
	return rmz(q);
}
num mod(num x, num y, int ope, int pwr) {
	num r, b;
	r = initnum(r);
	b = initnum(b);
	r = adz(r, x.bi);
	b = adz(b, x.bi);
	int i = 0, j, k;
	/*same as division just returns different number*/
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
	ope = 1;
	while(i < y.bi) {
		j = -1;
		r.bd[r.bi] = y.bd[i];
		r.bd[r.bi + 1] = '\0';
		r.bi ++;
		b = r;
		while(b.sign == 0) {
			b = sub(x, b, ope, pwr);
			j++;
		}
		r = add(x, b, ope, pwr);
		i++;
	}
	r.bi -= k;
	j = 0;
	while(j < k) {
		r.ad[j] = r.bd[r.bi + j];
		j++;
	}
	ope = 0;
	r.ai = k;
	r.ad[r.ai] = '\0';
	r.bd[r.bi] = '\0';
	r = rmza(r);
	free(b.bd);
	free(b.ad);
	free(y.bd);
	free(y.ad);
	free(x.bd);
	free(x.ad);
	return rmz(r);
}


/*returns variable of n * pi i.e. (3.14 * 10 ^ 37)*/
num getpi(num t) {
	t = breinitnum(t);
	t.bd = "31415926535897932384626433832795028841";
	t.bd[38] = '\0';
	t.bi = 38;
	return t;
}


/*in multiplication sometimes character gets too big (> 255)
 *to avoid printing unknown characters carry needs to be cleared
 */
num carryclr(num res, int k) {
	int m;
	while(k > 0) {
		if(res.bd[k] > '9') {
			m = res.bd[k] - 48;
			res.bd[k] = (m % 10) + 48;
			res.bd[k - 1] += m / 10;
		}
	k--;
	}
	return res;
}
