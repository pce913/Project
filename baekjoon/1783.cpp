#include<stdio.h>
#include<algorithm>
using namespace std;
int main(){
	int N, M;
	scanf("%d %d",&N,&M);
	if (N == 1)
		printf("1");
	else if (N == 2){
		printf("%d", min(4, (M + 1) / 2));
	}
	else if (M < 7){
		int G[6] = { 1, 2, 3, 4, 4, 4 };
		printf("%d",G[M-1]);
	}
	else
		printf("%d",M-2);
	return 0;
}