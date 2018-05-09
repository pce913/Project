#include<stdio.h>
/*
	Sprague-Grundt Value가 이런식으로 채워진다.
	g(4K+1)=4k+1
	g(4K+2)=4K+2
	g(4K+3)=4K+4
	g(4K+4)=4K+3
*/

int main(){
	int n;
	scanf("%d",&n);
	int ans = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d",&x);
		if (x % 4 == 0){
			x -= 1;
		}
		else if (x % 4 == 3){
			x += 1;
		}
		ans ^= x;
	}
	printf("%s", ans == 0 ? "cubelover" : "koosaga");
	return 0;
}