#include<stdio.h>
#include<algorithm>
using namespace std;
int A[1001][1001];
int D[1001][1001];
bool check[1001][1001];

int go(int i,int j){
	if (i == 1 && j == 1)
		return A[1][1];
	if (i < 1 || j < 1)
		return 0;
	if (check[i][j])
		return D[i][j];

	D[i][j] = max(go(i - 1, j), go(i, j - 1))+A[i][j];
	check[i][j] = true;

	return D[i][j];
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%d",&A[i][j]);
		}
	}
	printf("%d",go(n,m));
	return 0;
}