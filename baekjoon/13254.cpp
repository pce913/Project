#include<stdio.h>
#include<cstring>
#include<vector>
using namespace std;

/*
	1. 어느 한 가족이 각 도로들을 이용할 확률을 구한다.
	   이렇게 해서 각각의 가족이 각각의 도로를 이용할 확률을 구한다.
	2. 이렇게 각 도로별로 구해진 확률을 더하면 정답이다.
*/
int edge[55][55], house[55];
double temp[55];
vector<int> a[55];
int cnt;
void dfs(int node,int parent,int e_num,bool haveToCnt){
	if (haveToCnt){
		cnt++;
	}
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (next != parent){
			if (edge[node][next] == e_num || haveToCnt){
				dfs(next, node, e_num, true);
			}
			else{
				dfs(next, node, e_num, false);
			}
		}
	}
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	memset(edge, -1, sizeof(edge));
	for (int i = 0; i < n - 1; i++){
		temp[i] = 1;
	}
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
		edge[x][y] = i;
		edge[y][x] = i;
	}
	for (int i = 0; i < m; i++){
		scanf("%d",&house[i]);
	}
	double ans = 0;
	for (int i = 0; i < m ; i++){
		for (int j = 0; j < n - 1; j++){
			cnt = 0;
			dfs(house[i], -1, j, false);   //cnt: 내가 확인 할 도로 넘어에 있는 집의 갯수.
			temp[j] *= (double)cnt / (n - 1);   //자신의 집 위치는 빼서 계산해야 하므로 n-1
		}
	}
	for (int i = 0; i < n - 1; i++){
		ans += temp[i];
	}
	printf("%.10lf",ans);
	return 0;
}