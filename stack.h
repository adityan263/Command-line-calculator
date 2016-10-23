#define MAX 128





typedef struct num{
	char *bd, *ad, v;
	int bi, ai, sign, blimit, alimit, var;
}num;


typedef struct stacki {
	num a[MAX];
	int i;
}stacki;


num initnum(num n);
num breinitnum(num n);
num areinitnum(num n);


void pushi(stacki *s, num numb);
num popi(stacki *s);
int emptyi(stacki *s);
int fulli(stacki *s);
void initi(stacki *s);


typedef struct stackc {
	char b[MAX];
	int j;
}stackc;


void pushc(stackc *s, char op);
char popc(stackc *s);
int emptyc(stackc *s);
int fullc(stackc *s);
void initc(stackc *s);
