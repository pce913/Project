#include<stdio.h>

bool D[1005];
int main(){
	int n;
	scanf("%d",&n);
	D[0] = true;
	for (int i = 1; i <= n; i++){
		if (i - 1 >= 0){
			if (!D[i - 1])
				D[i] = true;
		}
		if (i - 3 >= 0){
			if (!D[i - 3])
				D[i] = true;
		}
		if (i - 4 >= 0){
			if (!D[i - 4])
				D[i] = true;
		}
	}
	printf("%s",D[n] ? "SK":"CY");
	return 0;
}