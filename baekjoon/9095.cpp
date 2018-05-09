#include<stdio.h>

//int main(){
//	int T;
//	scanf("%d", &T);
//	for (int test = 0; test < T; test++){
//		int D[11];
//		int n;
//		scanf("%d", &n);
//		D[1] = 1;
//		D[2] = 2;
//		D[3] = 4;
//		for (int i = 4; i <= n; i++)
//			D[i] = D[i - 1] + D[i - 2] + D[i - 3];
//		printf("%d\n",D[n]);
//	}
//	return 0;
//}
int go(int count,int sum,int goal){
	if (sum > goal)
		return 0;
	else if (sum == goal)
		return 1;
	
	int now = 0;
	for (int i = 1; i <= 3; i++){
		now += go(count + 1, sum + i, goal);
	}
	return now;
}

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int goal;
		scanf("%d",&goal);
		printf("%d\n", go(0, 0, goal));
	}
	return 0;
}