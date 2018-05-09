#include<stdio.h>
//http://blog.myungwoo.kr/27   여기에 상세히 설명되어 있다.
//동전을 x칸 옮기는 것을 돌더미를 x개 가져간다고 생각하면 된다.
int main(){
	int n;
	scanf("%d", &n);
	int ans = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		ans ^= x;
	}
	printf("%s", ans == 0 ? "cubelover" : "koosaga");
	return 0;
}