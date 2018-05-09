#include<stdio.h>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 1005;

vector<int> a[MAXN];
vector<int> r[MAXN];
vector<int> group[MAXN];
int what_group[MAXN];
vector<int> v;
bool check[MAXN];
int D[MAXN][MAXN];     //D[n]: n까지 보았을때 담은 물건의 최대 갯수.
                       //여기서 n은 connected_cnt. 즉, connected component의 갯수이다.
vector<int> sac[MAXN];
int ccnt;

void dfs3(int node){
	check[node] = true;
	ccnt++;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next]){
			dfs3(next);
		}
	}
}

void dfs2(int node,int gnum){
	check[node] = true;
	what_group[node] = gnum;
	group[gnum].push_back(node);
	for (int i = 0; i < r[node].size(); i++){
		int next = r[node][i];
		if (!check[next]){
			dfs2(next,gnum);
		}
	}
}

void dfs(int node){
	check[node] = true;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next]){
			dfs(next);
		}
	}
	v.push_back(node);
}

int main(){
	int n, k;
	scanf("%d %d",&n,&k);
	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		a[x].push_back(i);
		r[i].push_back(x);
	}
	for (int i = 1; i <= n; i++){
		if (!check[i]){
			dfs(i);
		}
	}

	
	reverse(v.begin(), v.end());
	memset(check, false, sizeof(check));
	int gnum = 1;
	for (int node : v){
		if (!check[node]){
			dfs2(node, gnum++);
		}
	}

	memset(check, false, sizeof(check));
	for (int i = 0; i < MAXN; i++){
		sac[i].push_back(0);
	}

	int connected_cnt = 1;
	for (int node : v){
		if (!check[node]){
			ccnt = 0;
			dfs3(node);
			int g=what_group[node];
			int ssize=group[g].size();
			for (int i = ssize; i <= ccnt; i++){
				sac[connected_cnt].push_back(i);    //connected component별로 sac이 있어야 함.
			}
			connected_cnt++;
		}
	}
	connected_cnt--;

	D[0][0] = true;
	for (int i = 1; i <= connected_cnt; i++){
		for (int j = 0; j<=k; j++){
			bool what1 = D[i - 1][j];
			D[i][j] |= D[i - 1][j];  //선택 안한 경우.
			for (int w = 1; w <= sac[i].size() - 1; w++){
				if (j + sac[i][w] <= k && D[i-1][j]){
					D[i][j + sac[i][w]] |= D[i][j];
				}
			}
		}

	}

	int ans = 0;
	for (int j = k; j >= 0; j--){
		if (D[connected_cnt][j]){
			ans = j;
			break;
		}
	}

	printf("%d",ans);
	return 0;
}