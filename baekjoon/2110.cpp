#include<stdio.h>
#include<algorithm>
using namespace std;
int M[200001];

int main(){
	int N, C;
	scanf("%d %d",&N,&C);
	for (int i = 1; i <= N; i++)
		scanf("%d",&M[i]);
	
	sort(M, M + N);
	int l = 1;
	int r = M[N] - M[1];
	int maxi = 1;
	while (l <= r){
		int m = (l + r) / 2;
		
		int cnt = 1;
		int s = M[1];
		for (int i = 1; i <= N-1; i++){
			if (M[i + 1] - s >= m){
				cnt++;
				s = M[i + 1];
			}
		}

		if (cnt >= C){
			if (maxi < m)
				maxi = m;
			l = m + 1;
		}
		else
			r = m - 1;
	}
	printf("%d",maxi);
	return 0;
}