#include<stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	int fm = n / 5;
	while (fm >= 0){
		if ((n - 5 * fm) % 3 == 0){
			printf("%d", fm + (n - 5 * fm) / 3);
			return 0;
		}
		fm--;
	}
	printf("-1");
	return 0;
}