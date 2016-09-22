#define MAX 128



typedef struct stacki {
	long double a[MAX];
	int i;
}stacki;
void pushi(stacki *s, long double num);
long double popi(stacki *s);
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
