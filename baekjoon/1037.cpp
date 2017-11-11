#include<stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	int maxi = 0;
	int mini = 1e9;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d",&x);
		maxi = maxi > x ? maxi : x;
		mini = mini < x ? mini : x;
	}
	printf("%d",maxi*mini);
	return 0;
}