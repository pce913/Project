#include<stdio.h>
/*각 돌더미에 대해 sprague-grundy value를 매겨주고 
그 값들을 xor 했을때의 값이 무엇인지에 따라서 답을 결정한다.
이것은 님 게임2 문제도 똑같이 적용 가능하며, 문제를 푸는 방법은 동일하다.
님 게임2 문제는 각 돌더미의 sprague-grundy value 가 모두 원래 돌더미 갯수와 같기 때문에
그냥 입력하는대로 xor를 할 수 있던 것이다.
백준 강의자료 참조.
*/
int main(){
	int n;
	scanf("%d",&n);
	int ans = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d",&x);
		if (x & 1){
			ans ^= (x + 1) / 2;
		}
		else{
			ans^=((x - 2) / 2);
		}
	}
	printf("%s", ans == 0 ? "cubelover" : "koosaga");
	return 0;
}