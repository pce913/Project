#include<stdio.h>

int a[1000001];
int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		a[i] = i;
	}

	bool getOff = true;
	int i = 1;
	int k = n;
	while (i < k){
		if (getOff){
			getOff = false;
		}
		else{
			a[k + 1] = a[i];
			k++;
			getOff = true;
		}
		i++;
	}
	printf("%d",a[i]);
	return 0;
}