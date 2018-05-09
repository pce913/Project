#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

struct Point{
	int x, y;
};

struct Info{
	int x, y, num;
};

const int MAXN = 2005;
Point a[MAXN];
int D[MAXN][MAXN];
Info prevs[MAXN][MAXN];

int main(){
	int n,w;
	scanf("%d %d",&n,&w);
	for (int i = 1; i <= w; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
	}

	for (int i = 0; i <= w; i++){
		for (int j = 0; j <= w; j++){
			D[i][j] = 1e9;
		}
	}

	D[0][0] = 0;
	for (int i = 0; i <= w; i++){
		for (int j = 0; j <= w; j++){
			int x1 = (i == 0 ? 1 : a[i].x);
			int y1 = (i == 0 ? 1 : a[i].y);
			int x2 = (j==0 ? n : a[j].x);
			int y2 = (j==0 ? n : a[j].y);
			int next = max(i, j) + 1;
			int nx = a[next].x;
			int ny = a[next].y;
			if (D[next][j] > D[i][j] + abs(x1 - nx) + abs(y1 - ny)){
				D[next][j] = D[i][j] + abs(x1 - nx) + abs(y1 - ny);
				prevs[next][j] = { i, j , 1};
			}
			if (D[i][next] > D[i][j] + abs(x2 - nx) + abs(y2 - ny)){
				D[i][next] = D[i][j] + abs(x2 - nx) + abs(y2 - ny);
				prevs[i][next] = { i, j, 2 };
			}

		}
	}

	int ans = 1e9;
	int cx = 0; 
	int cy = 0;
	for (int i = 0; i < w; i++){
		if (ans > D[i][w]){
			ans = D[i][w];
			cx = i;
			cy = w;
		}
		if (ans > D[w][i]){
			ans = D[w][i];
			cx = w;
			cy = i;
		}
	}
	printf("%d\n",ans);
	vector<int> handling;
	while (!(cx==0 && cy==0)){
		handling.push_back(prevs[cx][cy].num);
		int tx = cx;
		int ty = cy;
		cx = prevs[tx][ty].x;
		cy = prevs[tx][ty].y;
	}
	for (auto it = handling.rbegin(); it != handling.rend(); it++){
		printf("%d\n", *it);
	}

	return 0;
}