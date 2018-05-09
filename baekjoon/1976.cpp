#include<stdio.h>

int parent[205];
int Find(int x){
	return x == parent[x] ? x : parent[x] = Find(parent[x]);
}

void Union(int x,int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
	}
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		parent[i] = i;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			int x;
			scanf("%d",&x);
			if (x == 1){
				Union(i, j);
			}
		}
	}
	int x;
	scanf("%d",&x);
	x = Find(x);
	for (int i = 2; i <= m; i++){
		int y;
		scanf("%d",&y);
		if (x != Find(y)){
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}