#include<stdio.h>
int mark[100002];           //mark: 반전 횟수.
int a[100002];

int main(){
	int n, k;
	scanf("%d %d",&n,&k);

	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}

	int ans = 0;
	int i;
	for (i = 1; i <= n - k + 1; i++){
		mark[i] += mark[i - 1];
		if ((mark[i] + a[i]) % 2 == 1){           //전구가 켜져있는 상태.     
			mark[i] += 1;
			ans++;
			mark[i + k] -= 1;
		}
	}
	for (int j = i; j <= n; j++){
		mark[j] += mark[j - 1];
	}

	bool isAns = true;
	for (i = 1; i <= n; i++){
		if ((mark[i] + a[i]) % 2 != 0){
			isAns = false;
			break;
		}
	}

	if (isAns){
		printf("%d",ans);
	}
	else{
		printf("Insomnia");
	}
	return 0;
}