#include<stdio.h>
#include<vector>
using namespace std;
vector<int> a[101];
bool check[101];
int p1, p2;
int ans=-1;

void dfs(int node,int num){
	if (node == p2){
		ans = num;
		return;
	}

	check[node] = true;
	int ans = 0;
	for (auto& next : a[node]){
		if (!check[next]){
			dfs(next,num+1);
		}
	}
	return;
}


int main(){
	int n;
	int m;
	scanf("%d",&n);
	scanf("%d %d",&p1,&p2);
	scanf("%d",&m);
	for (int i = 1; i <= m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(p1, 0);
	printf("%d",ans);
	return 0;
}