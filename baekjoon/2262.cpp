#include<stdio.h>
#include<algorithm>
using namespace std;
const int INF = 1e9;
int a[300];
int D[300][300];   //D[i][j] : i~j까지 토너먼트를 했을때 나올 수 있는 랭킹 차이의 합의 최소값.
bool check[300][300];
int winner[300][300];   //winner[i][j]: i~j까지 토너먼트를 했을때 우승자.

int go(int i,int j){
	if (i >= j)
		return 0;

	if (check[i][j])
		return D[i][j];
	check[i][j] = true;
	for (int k = i; k <= j; k++){
		int temp = go(i, k) + go(k + 1, j);
		temp += abs(winner[i][k] - winner[k + 1][j]);
		D[i][j] = min(D[i][j], temp);
	}
	return D[i][j];
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	for (int i = 1; i <= n; i++){
		winner[i][i] = a[i];
		for (int j = i + 1; j <= n; j++){
			winner[i][j] = min(winner[i][j - 1], a[j]);
			D[i][j] = INF;
		}
	}
	printf("%d",go(1,n));
	return 0;
}