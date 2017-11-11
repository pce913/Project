//2667 단지번호붙이기 문제

#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N;
int M[26][26];
int check[26][26];
int dx[4] = { 0, 0, 1, -1 }, dy[4] = {1,-1,0,0};    //위 아래 오른쪽 왼쪽
int cnt = 1;
void dfs(int x,int y) {
	check[x][y] = true;
	for (int k = 0; k < 4; k++){
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx>=1 && ny<=N && ny>=1 && ny<=N){
			if (M[nx][ny] == 1 && !check[nx][ny]){
				dfs(nx, ny);
				cnt++;
			}
		}
	}
}

int main(){
	scanf("%d",&N);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++)
			scanf("%1d", &M[i][j]);
	}

	vector<int> V;
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			if (M[i][j] == 1 && !check[i][j]){
				dfs(i, j);
				V.push_back(cnt);
				cnt = 1;
			}
		}
	}
	sort(V.begin(), V.end());

	printf("%d\n", V.size());
	for (int i = 0; i < V.size(); i++)
		printf("%d\n",V[i]);
	return 0;
}