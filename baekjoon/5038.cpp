#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXN = 2501;
vector<int> a[MAXN];
//n^2 으로 풀자.

int tnode;
int eccen[MAXN];
int width = 0;
int ans;
pair<int, int> cut;
pair<int, int> put;
int n;

void dfs(int node, int parent, int block, int depth){
	eccen[node] = max(eccen[node], depth);
	if (width < depth){
		width = depth;
		tnode = node;
	}

	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (next != parent && next != block){
			dfs(next, node, block, depth + 1);
		}
	}
}

void go(int node, int parent){
	int putter1 = 0;
	int putter2 = 0;

	tnode = node;
	memset(eccen, 0, sizeof(eccen));
	width = 0;
	dfs(node, -1, parent, 0);   //snode 구하기

	width = 0;
	dfs(tnode, -1, parent, 0);   //enode 구하기

	width = 0;
	dfs(tnode, -1, parent, 0);    //eccen 구하기.


	int dia1 = width;
	int radi1 = (dia1 + 1) / 2;
	if (dia1 == 0){
		putter1 = tnode;
	}
	else{
		for (int i = 1; i <= n; i++){
			if (eccen[i] == radi1)
				putter1 = i;
		}
	}

	tnode = parent;
	memset(eccen, 0, sizeof(eccen));
	width = 0;
	dfs(parent, -1, node, 0);
	width = 0;

	dfs(tnode, -1, node, 0);
	width = 0;

	dfs(tnode, -1, node, 0);
	int dia2 = width;
	int radi2 = (dia2 + 1) / 2;

	if (dia2 == 0){
		putter2 = tnode;
	}
	else{
		for (int i = 1; i <= n; i++){
			if (eccen[i] == radi2)
				putter2 = i;
		}
	}

	if (ans > max({ dia1, dia2, radi1 + radi2 + 1 })){
		ans = max({ dia1, dia2, radi1 + radi2 + 1 });
		cut.first = node;
		cut.second = parent;
		put.first = putter1;
		put.second = putter2;
	}
}

int main(){
	ans = 1e9;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for (int i = 1; i <= n; i++){
		for (int j = 0; j < a[i].size(); j++){
			int next = a[i][j];
			go(next, i);
		}
	}

	printf("%d\n", ans);
	printf("%d %d\n", cut.first, cut.second);
	printf("%d %d\n", put.first, put.second);

	return 0;
}