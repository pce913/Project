#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> a[10005],ans;
int m[10005],D[10005][2];

void dfs(int node,int parent){
	for (int next : a[node]){
		if (next != parent){
			dfs(next, node);
		}
	}

	int sum1 = 0, sum0 = 0;
	for (int next : a[node]){
		sum1 += D[next][0];
		sum0 += max(D[next][0], D[next][1]);
	}
	D[node][1] = sum1 + m[node];
	D[node][0] = sum0;
}

void go(int node,int parent,int choice){
	if (choice == 1){
		ans.push_back(node);
		for (int next : a[node]){
			if (next != parent){
				go(next, node, 0);
			}
		}
	}
	else{
		for (int next : a[node]){
			if (next != parent){
				if (D[next][0] < D[next][1]){
					go(next, node, 1);
				}
				else{
					go(next, node, 0);
				}
			}
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&m[i]);
	}
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	dfs(1, -1);
	if (D[1][0] < D[1][1]){
		go(1, -1, 1);
	}
	else{
		go(1, -1, 0);
	}
	sort(ans.begin(), ans.end());
	printf("%d\n",max(D[1][0],D[1][1]));
	for (int i = 0; i < ans.size(); i++){
		printf("%d ",ans[i]);
	}
	return 0;
}