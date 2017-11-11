#include<stdio.h>
#include<cstring>
#include<queue>
#include<vector>
#include<set>
using namespace std;

struct Point{
	int x, y;
	/*bool operator < (const Point p)const{
		if (x != p.x)return x < p.x;
		return y < p.y;
	}*/
};




set<Point> asd;
int M[9][9];
//bool check[9][9];

vector<Point> p;
int n, m;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
                              // 0번: 길, 1번: 벽 , 2번: 바이러스, 3번 새로운 벽, 4번: 방문한곳.
void bfs(){
	queue<Point> q;
	for (int i = 0; i < p.size(); i++){
		q.push(p[i]);
	}
	while (!q.empty()){
		auto& node = q.front();
		q.pop();
		for (int i = 0; i < 4; i++){
			int nx = node.x + dx[i];
			int ny = node.y + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] == 0){
					M[nx][ny] = 4;
					q.push({ nx, ny });
				}
			}
		}
		
	}

}

int main(){
	asd.insert({ 1, 2 });
	asd.insert({ 1, 2 });
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%d",&M[i][j]);
			if (M[i][j] == 2){
				p.push_back({i,j});
			}
		}
	}
	int ans = 0;
	int cnt = 0;

	int one_x,one_y;
	int two_x, two_y;
	int three_x, three_y;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			one_x = i;
			one_y = j;
			if (M[one_x][one_y] !=0){
				continue;
			}
			for (int a = 1; a <= n; a++){
				for (int b = 1; b <= m; b++){
					if ((a<=i && b<=j)){ 
						continue;
					}

					two_x = a;
					two_y = b;
					if (M[two_x][two_y] !=0){
						continue;
					}
					for (int k = 1; k <= n; k++){
						for (int l = 1; l <= m; l++){
							if ((k <= a && l <= b)){ 
								continue;
							}

							three_x = k;
							three_y = l;
							if (M[three_x][three_y] !=0){
								continue;
							}
							M[one_x][one_y] = 3;
							M[two_x][two_y] = 3;
							M[three_x][three_y] = 3;
							

							bfs();
							for (int w = 1; w <= n; w++){
								for (int z = 1; z <= m; z++){
									if (M[w][z]==0){
										cnt++;
									}
									else if (M[w][z] == 4){
										M[w][z] = 0;
									}
								}
							}
							if (ans < cnt){
								ans = cnt;
							}

							cnt = 0;
							M[one_x][one_y] = 0;
							M[two_x][two_y] = 0;
							M[three_x][three_y] = 0;
						}
					}
				}
			}

		}
	}
	
	printf("%d",ans);
	return 0;
}