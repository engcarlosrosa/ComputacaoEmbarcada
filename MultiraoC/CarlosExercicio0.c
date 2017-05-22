#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	float soma = 0, real;
	printf("Digite um numero inteiro positivo: ");
	scanf("%d", &n);
	printf("%d\n", n);
	for (int i = 0; i < n; ++i)
	{
		printf("Digite o valor do numero %d: ", i);
		scanf("%f", &real);
		soma=soma+real;
	}
	printf("Media:%f\n", soma/ (float) n);
	
	return 0;
}