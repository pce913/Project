#include<stdio.h>
#include<algorithm>
using namespace std;
int M[9];
int main(){
	int N;
	scanf("%d",&N);
	for (int i = 1; i <= N; i++){
		M[i] = i;
		printf("%d ",i);
	}
	printf("\n");
	while (next_permutation(&M[1], (&M[N])+1)){
		for (int i = 1; i <= N; i++)
			printf("%d ", M[i]);
		printf("\n");
	}
	return 0;
}