#include<stdio.h>

int main(){
	int n;
	scanf("%d",&n);
	bool have = false;
	for (int i = 2; i*i <= n; i++){
		while ((n%i) == 0){
			have = true;
			printf("%d\n", i);
			n /= i;
		}
	}
	if (n > 1){
		printf("%d\n",n);      // 예를들어 n=6일 경우에 6의 소인수인 3은 위의 포문에 걸리지 않는다.
	}              //그런 경우에는 딱 하나 이것만 더 출력해주면 된다.
	return 0;
}