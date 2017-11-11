#include<stdio.h>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
int n, m, k;
int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};
struct Point{
	int row, col;
};

bool M[10001];
int parent[10001];
int size[10001];

int Find(int x){
	if (x == parent[x]){
		return x;
	}
	else{
		return parent[x] = Find(parent[x]);
	}
}

void Union(int x,int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
		size[x] += size[y];
	}
}

int main(){
	
	scanf("%d %d %d",&n,&m,&k);
	vector<Point> a(k);

	for (int i = 1; i <= 10001; i++){
		size[i] = 1;
		parent[i] = i;
	}

	for (int i = 0; i < k; i++){
		int row, col;
		scanf("%d %d",&row,&col);
		M[(row-1)*m+col ] = true;
		a[i].row = row;
		a[i].col = col;
	}
	
	for (auto& p : a){
		int point = (p.row - 1)*m + p.col;
		for (int i = 0; i < 4; i++){
			int nx = p.row + dx[i];
			int ny = p.col + dy[i];
			int npoint = (nx - 1)*m + ny;
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && M[npoint]==true){
				Union(point, npoint);
			}
		}
	}
	int sum = 0;
	int ans = 1;
	for (int i = 1; i <= 10000; i++){
		if (i == Find(i))ans = max(ans, size[i]);
	}
	printf("%d",ans);
	return 0;
}