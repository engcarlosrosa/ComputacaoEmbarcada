#include <stdio.h>

void troca(short *a, short *b){
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int main(int argc, char const *argv[])
{
	short a = 5;
	short b = 2;

	troca(&a, &b);

	printf("a = %d\n", a);
	printf("b = %d\n", b);
	return 0;
}