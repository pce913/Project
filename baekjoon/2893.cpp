#include<stdio.h>
#include<algorithm>
using namespace std;

struct Triangle{
	int x, y, r;
	Triangle(int _x, int _y, int _r){
		x = _x, y = _y, r = _r;
	}
	Triangle(){}
	bool operator==(const Triangle& t)const{
		return x == t.x && y == t.y && r == t.r;
	}
};
Triangle triangle[15];

Triangle area_of_overlapped_triangle(Triangle a, Triangle b){
	if (a.x > b.x)
		swap(a, b);
	int dx = b.x - a.x;
	a.x += dx;    //이 코드가 반드시 있어야만 모든 경우를 처리 할 수 있다. 밑에 if (a.y > b.y)에서 swap될 경우를 처리하기 위함이다.
	a.r -= dx;
	if (a.r <= 0)  //겹치지 않는 삼각형일때
		return{ 0, 0, 0 };

	if (a.y > b.y)
		swap(a, b);
	b.r = min(b.r, a.r - (b.y - a.y));    //y부분 스왑이 일어나면 b.r이 답이 되고 안일어나면 a.r - (b.y - a.y)이 답이 된다.
	if (b.r <= 0)
		return{ 0, 0, 0 };
	else{
		return b;
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		scanf("%d %d %d", &triangle[i].x, &triangle[i].y, &triangle[i].r);
	}
	long long ans = 0;   //포함-배제 원리 사용
	for (int bit = 1; bit < (1 << n); bit++){   // 공집합은 없으므로 1부터 시작
		int cnt = 0;
		Triangle temp;
		bool isOverLap = true;
		for (int i = 0; i < n; i++){
			if (bit&(1 << i)){
				cnt++;
				if (cnt == 1){
					temp = triangle[i];
				}
				else{
					temp = area_of_overlapped_triangle(temp, triangle[i]);
				}

				if (temp == Triangle(0, 0, 0)){
					isOverLap = false;
					break;
				}
			}
		}

		if (isOverLap){
			int r = temp.r;
			if (cnt & 1){   //(1LL << (cnt - 1)) 왜 이것을 곱해주는지 그려보니깐 정확히 알겠다.
				ans += (long long)(1LL << (cnt - 1))*r*r;   //겹치는 녀석
			}
			else{
				ans -= (long long)(1LL << (cnt - 1))*r*r;
			}
		}
	}
	printf("%lld.%d",ans/2,(ans%2)*5);
}