#include<cstdio>
int min(int x, int y){ return x < y ? x : y; }
int main(){
	int n, q;
	scanf("%d %d",&n,&q);
	for (int i = 0; i < q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		x = min(x, n - x + 1);
		y = min(y, n - y + 1);
		printf("%d\n", (min(x, y) - 1) % 3 + 1);
	}
	return 0;
}