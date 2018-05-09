#include<stdio.h>
#include<cstring>

int D[10005];
int a[10005];

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		memset(D, 0, sizeof(D));
		int n;
		scanf("%d",&n);
		for (int i = 1; i <= n; i++){
			int x;
			scanf("%d",&x);
			a[i] = x;
		}
		int goal;
		scanf("%d",&goal);

		D[0] = 1;
		for (int i = 1; i <= n; i++){
			for (int j = 0; j <= goal; j++){
				if (j + a[i] > goal)
					continue;
				D[j + a[i]] += D[j];
			}
		}

		printf("%d\n",D[goal]);
	}
	return 0;
}