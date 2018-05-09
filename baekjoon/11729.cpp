#include<stdio.h>
void hanoi(int n, int x, int y){
	if (n == 0) 
		return;
	hanoi(n - 1, x, 6 - x - y);
	printf("%d %d\n",x,y);
	hanoi(n-1,6-x-y,y);
}

int main(){
	int n;
	scanf("%d",&n);
	printf("%d\n",(1<<n)-1);   //2의 제곱을 쉬프트 연산으로 표현
	hanoi(n, 1, 3);
	return 0;
}