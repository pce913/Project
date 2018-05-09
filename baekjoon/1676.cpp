#include<stdio.h>
                  //팩토리얼에서 2와 5의 갯수를 찾아주면된다.
                 //5의 갯수는 2의 갯수보다 항상 적으므로 5의 갯수만 찾아주면 된다.
                 //강의자료보니깐 확실히 이해 되었다.
int main() {
	int n;
	int ans = 0;
	scanf("%d",&n);
	for (int i = 5; i <= n; i *= 5) {
		ans += n / i;
	}
	printf("%d",ans);
	return 0;
}