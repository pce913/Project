#include<stdio.h>
int remain = 210;

int main(){
	int k,n;
	scanf("%d %d",&k,&n);
	int i = 1;
	while (i <= n){
		int t;
		char c;
		scanf("%d %c", &t, &c);
		if (remain - t > 0){
			if (c == 'T'){
				remain -= t;
				i++;
				k = k % 8 + 1;
			}
			else if (c == 'N' || c == 'P'){
				remain -= t;
				i++;
			}
		}
		else{
			break;
		}
	}
	printf("%d",k);
	return 0;
}