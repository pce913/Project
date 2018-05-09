#include<stdio.h>
#include<queue>
using namespace std;
 int cap[3];
bool check[201][201];
bool ans[201];
int from[] = { 0, 0, 1, 1, 2, 2 };
int to[] = { 1, 2, 2, 0, 0, 1 };

void dfs(pair<int,int> p){
	check[p.first][p.second] = true;
	ans[cap[2]] = true;
	int x = p.first;
	int y = p.second;
	int z = cap[2] - x - y;

	for (int i = 0; i < 6; i++){
		int next[3] = { x, y, z };
		next[to[i]] += next[from[i]];
		next[from[i]] = 0;
		if (next[to[i]] > cap[to[i]]){
			next[from[i]] = next[to[i]] - cap[to[i]];
			next[to[i]] = cap[to[i]];
		}
		if (check[next[0]][next[1]] == false){
			check[next[0]][next[1]] = true;
			if (next[0] == 0){
				ans[next[2]] = true;
			}
			dfs(make_pair(next[0],next[1]));
		}
	}
}

int main(){
	scanf("%d %d %d",&cap[0],&cap[1],&cap[2]);
	dfs(make_pair(0,0));
	for (int i = 0; i <= 200; i++){
		if (ans[i])
			printf("%d ", i);
	}
	printf("\n");
	return 0;
}