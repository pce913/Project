#include<stdio.h>
int counting[10001];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		counting[x]++;
	}
	for (int i = 1; i <= 10000; i++){
		if (counting[i] > 0){
			for (int j = 0; j < counting[i]; j++){
				printf("%d\n",i);
			}
		}
	}
	return 0;
}