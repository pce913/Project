#include<stdio.h>

int parent[100005];

int Find(int x){
	if (x == parent[x])
		return x;
	return parent[x] = Find(parent[x]);
}

void Union(int x,int y){    //x: ·çÆ®
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
	}
}

int main(){
	int g, p;
	scanf("%d %d",&g,&p);
	for (int i = 1; i <= g; i++){
		parent[i] = i;
	}
	
	int ans = 0;
	for (int i = 1; i <= p; i++){
		int x;
		scanf("%d",&x);
		x = Find(x);
		if (x == 0){
			break;
		}
		Union(x - 1, x);
		ans++;
	}
	printf("%d",ans);
	return 0;
}