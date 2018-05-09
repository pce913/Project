#include<stdio.h>

int main(){
	int P;
	scanf("%d",&P);
	for (int test = 1; test <= P; test++){
		int n, m;
		scanf("%d %d",&n,&m);
		int d1, d2;
		int period = 0;
		d1 = 1;
		d2 = 1;
		do{
			int temp = d1;
			d1 = d2;
			d2 = (temp + d2) % m;
			period++;
		} while (!(d1==1 && d2==1));
		printf("%d %d\n",n,period);
	}
	return 0;
}