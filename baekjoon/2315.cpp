#include<stdio.h>
#include<algorithm>
using namespace std;
const int INF = 1e9 + 7;
const int MAXN = 1005;
int D[MAXN][MAXN][2],sum[MAXN],x[MAXN],w[MAXN];
bool check[MAXN][MAXN][2];
//D[i][j][where] : i~j까지 가로등을 껐을 때, 낭비되는 전력의 최소값
//where = 0 이면 마징가는 i에 있다는 뜻
//where = 1 이면 마징가는 j에 있다는 뜻
int n, m;
int go(int left, int right, int where){
	if (left == 1 && right == n){
		return 0;
	}
	if (check[left][right][where])
		return D[left][right][where];
	check[left][right][where] = true;
	int& ans = D[left][right][where];
	int cur = where == 0 ? left : right;
	int a1 = INF, a2 = INF;
	if (left - 1 >= 1){
		a1 = go(left - 1, right, 0) + (x[cur] - x[left - 1])*(sum[n] - (sum[right] - sum[left - 1]));
	}
	if (right + 1 <= n){
		a2 = go(left, right + 1, 1) + (x[right + 1] - x[cur])*(sum[n] - (sum[right] - sum[left - 1]));
	}
	return ans = min(a1, a2);
}

int main(){
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		scanf("%d %d",&x[i],&w[i]);
		sum[i] = sum[i - 1] + w[i];
	}
	printf("%d",go(m,m,0));
	return 0;
}