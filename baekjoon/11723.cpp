#include<stdio.h>
#include<cstring>
int main(){
	int M,x;
	int s=0;
	char b[7];
	scanf("%d",&M);
	for (int i = 0; i < M; i++){
		scanf("%s %d",b,&x);
		x--;
		if (!strcmp(b, "add"))
			s = (s | (1 << x));
		else if (!strcmp(b, "remove"))
			s = (s & ~(1<<x));
		else if (!strcmp(b, "check"))
			printf("%d\n", s&(1 << x) ? 1 : 0);
		else if (!strcmp(b, "toggle"))
			s = (s ^ (1 << x));
		else if (!strcmp(b, "all"))
			s = (1<<20)-1;
		else 
			s = 0;
	}
	return 0;
}