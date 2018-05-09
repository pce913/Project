#include<stdio.h>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct Point{
	int x, y;
};

int dist[105][105];
vector<Point> point;

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		point.clear();
		int n;
		scanf("%d",&n);
		int sx, sy;
		int ex, ey;

		scanf("%d %d",&sx,&sy);
		point.push_back({ sx, sy });
		for (int i = 0; i < n; i++){
			int x, y;
			scanf("%d %d",&x,&y);
			point.push_back({ x, y });
		}
		scanf("%d %d",&ex,&ey);
		point.push_back({ ex, ey });
		for (int i = 0; i < n + 2; i++){
			for (int j = 0; j < n + 2; j++){
				if (i == j)
					continue;
				dist[i][j] = 1e9;
			}
		}
		for (int i = 0; i < point.size(); i++){
			for (int j = 0; j < point.size(); j++){
				int ux = point[i].x;
				int uy = point[i].y;
				int vx = point[j].x;
				int vy = point[j].y;
				dist[i][j] = abs(ux - vx) + abs(uy - vy);
				if (dist[i][j]>1000)
					dist[i][j] = 1e9;
			}
		}
		for (int k = 0; k < point.size(); k++){
			for (int i = 0; i < point.size(); i++){
				for (int j = 0; j < point.size(); j++){
					if (dist[i][j] > dist[i][k] + dist[k][j]){
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}

		if (dist[0][point.size() - 1] >= 1e9){
			printf("sad\n");
		}
		else{
			printf("happy\n");
		}
	}
	return 0;
}