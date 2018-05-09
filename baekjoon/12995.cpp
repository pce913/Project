#include<stdio.h>
#include<cstring>
#include<vector>
using namespace std;

const long long MOD = 1000000007;
const int MAXN = 55;

vector<int> a[MAXN];
long long temp[MAXN];
long long D[MAXN][MAXN];    //D[n][i] : 현재보고있는 노드 n 의 서브노드갯수가 i인 서브트리 갯수.
int size[MAXN];
void dfs(int node,int parent){
	D[node][1] = 1;
	size[node] = 1;
	for (int k = 0; k < a[node].size(); k++){
		int next = a[node][k];
		if (next != parent){
			dfs(next, node);

			memset(temp, 0, sizeof(temp));
			for (int i = 1; i <= size[node]; i++){
				for (int j = 1; j <= size[next]; j++){
					temp[i + j] += D[node][i]%MOD * D[next][j]%MOD;
					temp[i + j] %= MOD;
				}
			}

			size[node] += size[next];
			for (int i = 1; i <= size[node]; i++){
				D[node][i] += temp[i];
			}
		}
	}
}

int main(){
	int n, k;
	scanf("%d %d",&n,&k);
	for (int i = 0; i < n-1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(1,-1);
	long long ans = 0;
	for (int i = 1; i <= n; i++){
		ans = (ans + D[i][k]) % MOD;
	}
	printf("%lld",ans);
	return 0;
}