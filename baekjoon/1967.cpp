#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge{
	int to, weight;
};
vector<Edge> a[10001];
int start=0;
int ans = 0;
int temp = 0;
void dfs2(int node, int parent,int len){
	ans = max(ans, len);
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i].to;
		int weight = a[node][i].weight;
		if (next != parent){
			dfs2(next, node,len+weight);
		}
	}
}


void dfs(int node,int parent,int len){
	if (temp < len){
		temp = len;
		start = node;
	}

	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i].to;
		int weight = a[node][i].weight;
		if (next != parent){
			dfs(next, node,len+weight);
		}
	}
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
	dfs(1,-1,0);
	dfs2(start, -1, 0);
	printf("%d",ans);
	return 0;
}