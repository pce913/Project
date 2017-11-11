#include<stdio.h>
int parent[1000001];
int Find(int x){
	if (x == parent[x])
		return x;
	else{
		return parent[x] = Find(parent[x]);
	}
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
	for (int i = 1; i <= n; i++){
		parent[i] = i;
	}
	for (int i = 0; i < m; i++){
		int w, x, y;
		scanf("%d %d %d",&w,&x,&y);
		if (w == 0){
			Union(x, y);
		}
		else{
			x = Find(x);
			y = Find(y);
			if (x == y){
				puts("YES");
			}
			else{
				puts("NO");
			}
		}
	}
	return 0;
}