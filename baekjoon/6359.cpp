#include<stdio.h>
#include<cstring>

bool isOpen[105];

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		memset(isOpen, false, sizeof(isOpen));
		int n;
		scanf("%d",&n);
		for (int i = 1; i <= n; i++){
			for (int j = i; j <= n; j += i){
				isOpen[j] = !isOpen[j];
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; i++){
			if (isOpen[i])
				ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}