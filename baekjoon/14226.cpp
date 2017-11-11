#include<stdio.h>
#include<queue>
using namespace std;

bool check[1001][1001];            
int dist[1001][1001];        // D[s][c] : 화면에 s개의 이모티콘이 있고 클립보드에 c개의 이모티콘이 있을때 최소 거리

int S;
pair<int,int> bfs(int a,int b){
	check[a][b] = true;
	queue< pair<int, int> > q;
	q.push({a,b});
	pair< int, int > ans = {S,S};
	while (!q.empty()){
		auto p=q.front();
		int s = p.first;
		int c = p.second;
		q.pop();
		
		if (s == S){
			ans = { s, c };
			break;
		}
		int ds[] = {0,c,-1};
		int dc[] = {-c+s,0,0};
		for (int k = 0; k < 3; k++){
			int ns = s+ds[k];
			int nc = c+dc[k];
			if (ns >= 0 && nc >= 0 && ns <=S){
				if (!check[ns][nc]){
					check[ns][nc] = true;
					dist[ns][nc] = dist[s][c] + 1;
					q.push({ns,nc});
				}
			}
		}
	}
	return ans;
}

int main(){
	scanf("%d",&S);
	auto p=bfs(1, 0);
	printf("%d",dist[p.first][p.second]);
	return 0;
}