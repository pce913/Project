#include<stdio.h>
#include<algorithm>
using namespace std;

int M[8];
int n;
int calc(){
	int sum = 0;
	for (int i = 1; i < n; i++)
		sum += abs(M[i]-M[i-1]);
	return sum;
}
int main(){
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		scanf("%d",&M[i]);
	}
	sort(M, M + n);
	int ans = 0;
	do{
		ans = max(ans, calc());
	} while (next_permutation(M, M + n));
	printf("%d",ans);
	return 0;
}