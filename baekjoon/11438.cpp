#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 100001;

vector<int> a[MAXN];
int depth[MAXN];
bool check[MAXN];
int parent[MAXN];     //각 노드의 parent 노드를 저장.
int p[MAXN][18];  //p[i][j]: 노드 i의 2^j번째 조상 저장

void bfs(int start){
	queue<int> q;
	q.push(start);
	check[start] = true;
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			if (!check[next]){
				check[next] = true;
				depth[next] = depth[node] + 1;
				parent[next] = node;
				q.push(next);
			}
		}
	}
}

int lca(int u, int v){
	if (depth[u] < depth[v]){
		swap(u, v);
	}
	int log = 0;    //u에서부터 최대 몇칸까지 위로 올라갈 수 있는지를 구함.
	while ((1 << (log + 1)) <= depth[u]){
		log++;
	}
	for (int i = log; i >= 0; i--){
		if (depth[u] - (1 << i) >= depth[v]){
			u = p[u][i];
		}
	}
	if (u == v){   //이렇게 위로 올렸을때 노드가 같아졌다면 예외로 리턴 u를 해준다.
		return u;
	}
	else{
		for (int i = log; i >= 0; i--){
			if (p[u][i] != 0 && p[u][i] != p[v][i]){
				u = p[u][i];
				v = p[v][i];
			}
		}
		return parent[u];  // u와 v가 같아지기 바로직전까지 올라온 상태에서 u의 parent가 LCA 이다.
	}

}


int main(){
	int n; 
	scanf("%d",&n);
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	bfs(1);   //먼저 depth와 parent를 구해놓는다.
	for (int i = 1; i <= n; i++){
		p[i][0] = parent[i];   //각 노드의 2^0 조상은 바로 부모이다.
	}

	for (int j = 1; (1 << j) < n; j++){   //
		for (int i = 1; i <= n; i++){
			if (p[i][j - 1] != 0){   //2^(j-1)번째 조상이 존재하는 경우
				p[i][j] = p[p[i][j - 1]][j - 1];    //2^3 + 2^3 == 2^4 이것과 같다.
			}
		}
	}
	int m;
	scanf("%d",&m);
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%d\n",lca(x,y));
	}

	return 0;
}