#include<stdio.h>
#include<vector>
using namespace std;

struct Edge{
	int to, weight;
};

const int MOD = 1000000007;
const int MAXN = 100001;
vector<Edge> a[MAXN];
bool check[MAXN];
long long ans = 0;

long long dfs(int node){
	check[node] = true;
	long long sum = 1;   //누적합 변수.
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i].to;
		int weight = a[node][i].weight;
		if (!check[next]){
			long long temp = (dfs(next)*weight%MOD)%MOD;
			ans += (temp*sum) % MOD;
			sum =(sum+temp)%MOD;
		}
	}
	return sum;
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n - 1; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back({ y, z });
		a[y].push_back({ x, z });
	}
	dfs(1);
	printf("%lld",ans%MOD);
	return 0;
}
