#include <stdio.h>

int fibonacci(int v[], int n){
	if (n<=2){
		return 1;
	}else{
		for (int i = 2; i < n; ++i){
			if (v[i]==v[i-2]+v[i-1])
			{
				return 1;
			}
			else{
				return 0;
			}
		}
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	int n = 10;
	int v[10] = {0, 1, 1, 2, 3, 50, 8, 13, 21, 34};
	printf("%d\n", fibonacci(v, n));
	
}