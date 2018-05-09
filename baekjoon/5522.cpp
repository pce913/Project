#include<stdio.h>

int main(){
	int ans = 0;
	for (int i = 0; i < 5; i++){
		int x;
		scanf("%d",&x);
		ans += x;
	}
	printf("%d",ans);
	return 0;
}