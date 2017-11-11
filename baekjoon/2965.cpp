#include<stdio.h>
#include<algorithm>
using namespace std;

int main(){
	int a, b, c;
	scanf("%d %d %d",&a,&b,&c);
	printf("%d", max(abs(a - b), abs(b - c))-1);
	return 0;
}