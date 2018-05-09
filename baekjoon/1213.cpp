#include<stdio.h>

int count[256];
char a[55];
char ans[55];
int r, l = -1;
int main(){
	scanf("%s",a);
	for (int i = 0; a[i] != '\0'; i++){
		count[a[i]]++;
		++l;
	}
	int ocnt = 0;
	for (int i = 'A'; i <= 'Z'; i++){
		if (count[i] & 1)
			ocnt++;
	}
	if (ocnt > 1)
		printf("I'm Sorry Hansoo");
	else{
		int m = l / 2;
		for (int i = 'A'; i <= 'Z'; i++){
			if (count[i] & 1){
				count[i] -= 1;
				ans[m] = i;
			}
			while (count[i] > 0){
				ans[r++] = i;
				ans[l--] = i;
				count[i] -= 2;
			}
		}
	}
	printf("%s",ans);
	return 0;
}