#include <stdio.h>

int main(int argc, char const *argv[])
{
	char produto1[50], produto2[50], produto3[50];
	float valor1, valor2, valor3, total, total1, total2, total3, subTotal, imposto;
	int quantidade1, quantidade2, quantidade3;
	printf("Produto 1:\n");
	printf("Digite o produto: \n");
	scanf("%s", produto1);
	printf("Digite o valor do produto: \n");
	scanf("%f", &valor1);
	printf("Digite a quantidade: \n");
	scanf("%d", &quantidade1);

	printf("Produto 2:\n");
	printf("Digite o produto: \n");
	scanf("%s", produto2);
	printf("Digite o valor do produto: \n");
	scanf("%f", &valor2);
	printf("Digite a quantidade: \n");
	scanf("%d", &quantidade2);

	printf("Produto 3:\n");
	printf("Digite o produto: \n");
	scanf("%s", produto3);
	printf("Digite o valor do produto: \n");
	scanf("%f", &valor3);
	printf("Digite a quantidade: \n");
	scanf("%d", &quantidade3);

	total1 = valor1*quantidade1;
	total2 = valor2*quantidade2;
	total3 = valor3*quantidade3;

	printf("%s: Preco total: %.2f,\n", produto1, total1);
	printf("%s: Preco total: %.2f,\n", produto2, total2);
	printf("%s: Preco total: %.2f,\n", produto3, total3);

	subTotal = total1+total2+total3;
	printf("Sub-Total: %.2f\n", subTotal);

	imposto = subTotal*0.05;
	printf("Imposto: %.2f\n", imposto);

	total = subTotal+imposto;
	printf("Total: %.2f\n", total);

	return 0;
}