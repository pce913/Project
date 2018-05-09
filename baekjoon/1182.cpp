//#include<stdio.h>
//int N, S,ans=0;
//int a[20];
//
//void go(int i,int sum){
//	if (i >= N){
//		if (S == sum)
//			ans++;
//		return;
//	}
//
//	go(i+1,sum);
//	go(i + 1, sum + a[i]);
//}
//
//int main(){
//	scanf("%d %d",&N,&S);
//	for (int i = 0; i < N; i++)
//		scanf("%d",&a[i]);
//	go(0, 0);
//	if (S == 0)
//		ans--;
//	printf("%d",ans);
//	return 0;
//}

#include<stdio.h>
int N, S, ans = 0;
int a[20];
int main(){
	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; i++)
		scanf("%d",&a[i]);
	for (int i = 1;i<(1<<N); i++){
		int sum = 0;
		for (int k = 0; k < N; k++){
			if (i&(1 << k)){
				sum += a[k];
			}
		}
		if (sum == S)
			ans++;
	}
	printf("%d",ans);
	return 0;
}