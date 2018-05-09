#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

char M[51][51];
bool check[51][51];
int flood[51][51];
int dist[51][51];
pair<int, int> S;
pair<int, int> D;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
int r, c;

void find(int a,int b){
	check[a][b] = true;
	queue< pair<int, int> > q;
	q.push({a,b});
	while (!q.empty()){
		auto p = q.front();
		int x = p.first;
		int y = p.second;
		q.pop();
		for (int k = 0; k < 4; k++){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx == D.first && ny == D.second){
				cout << dist[x][y] + 1;
				exit(0);
				return;
			}
			if (nx >= 0 && nx < r && ny >= 0 && ny < c){
				if (!check[nx][ny] && dist[x][y]+1 < flood[nx][ny] && M[nx][ny]!='X'){
					check[nx][ny] = true;
					dist[nx][ny] = dist[x][y] + 1;
					q.push({ nx, ny });
				}
			}
		}
	}
}

void bfs(vector< pair<int,int> >& puddle){
	queue< pair<int, int> > q;
	for (auto& node : puddle){
		q.push(node);
		check[node.first][node.second] = true;
	}
	while (!q.empty()){
		auto p=q.front();
		int x = p.first;
		int y = p.second;
		q.pop();
		//cout << x << ' ' << y << endl;
		for (int k = 0; k < 4; k++){
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 0 && nx < r && ny >= 0 && ny < c){
				if (!check[nx][ny] && !(nx==D.first && ny == D.second) && M[nx][ny]!='X'){
					check[nx][ny] = true;
					flood[nx][ny] = flood[x][y] + 1;
					q.push({nx,ny});
				}
			}
		}
	}
}

int main(){
	vector< pair<int, int> > v;
	cin >> r >> c;
	scanf("%d %d",&r,&c);
	for (int i = 0; i < r; i++){
		scanf("%s",&M[i]);
	}
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++){
			if (M[i][j] == 'S'){
				S = {i,j};
			}
			else if (M[i][j]=='D'){
				D = {i,j};
			}
			else if (M[i][j] == '*'){
				v.push_back({i,j});
			}
		}
	}
	bfs(v);
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++){
			if (!check[i][j]){
				flood[i][j] = 100000000;
			}
		}
	}
	memset(check,false,sizeof(check));
	find(S.first,S.second);
	printf("KAKTUS\n");
	return 0;
}