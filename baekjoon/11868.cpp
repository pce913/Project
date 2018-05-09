#include<stdio.h>
//http://blog.myungwoo.kr/27   여기에 상세히 설명되어 있다.
/*
	sprague-grundy function으로 이해해도 좋다.
	sprague-grundy value 가 모두 원래 돌더미 갯수와 같기 때문에
	그냥 입력하는대로 xor를 할 수 있는 것이다.
	백준 강의자료 참조.
*/
int main(){
	int n;
	scanf("%d",&n);
	int ans = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d",&x);
		ans ^= x;
	}
	printf("%s", ans == 0 ? "cubelover": "koosaga");
	return 0;
}