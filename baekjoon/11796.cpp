#include<stdio.h>
/*
	A: 1x1 , B: 1x1 , C: 1xp 로 두었을때
	최상: (AB)C --> p+1
	최악: A(BC) --> p+p
	최악 - 최상 = (p+p) - (p+1) = p - 1
	즉, p-1을 k라고 하면 정답은 항상
	3
	1 1 1 k+1 이 된다.
*/
int main(){
	int k;
	scanf("%d",&k);
	printf("3\n");
	printf("1 1 1 %d",k+1);
	return 0;
}