#include <stdio.h>
#include <string.h>

#define NUM_CHARS 50

void semExtensao(char arquivo[], char impressao[]){
	int i, n;
	int flag = 1;
	n = strlen(arquivo);
	for (i = n; i > 0; --i)
	{
		if (arquivo[i]=='.')
		{
			flag = 0;
			for (int j = 0; j < i; ++j)
			{
				impressao[j] = arquivo[j];
			}
			impressao[i]='\0';
			printf("%s\n", impressao);
			break;
		}
	}

	if (flag)
	{
		printf("%s\n", arquivo);
	}
	
}
int main(int argc, char const *argv[])
{
	char impressao[NUM_CHARS];
	semExtensao("brasil", impressao);
	semExtensao("brasil.virus", impressao);
	semExtensao("brasil.virus.exe", impressao);
	semExtensao("brasil.virus.nao.sim", impressao);

	return 0;
}