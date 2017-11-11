#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

int main(){	
	int N, L;
	scanf("%d %d",&N,&L);
	deque< pair<int, int> > d;
	for (int i = 0; i < N; i++){
		int cur;
		scanf("%d",&cur);                          // 입력과 동시에 처리 할 수 있음.
		if (!d.empty() && L <= i - d.front().second){     // 익덱스의 차이가 l보다 클때는 답이 될 수 없음.
			d.pop_front();                                // 이럴땐 앞쪽을 빼준다.
		}
		while (!d.empty() && cur < d.back().first){         // 구간에서 값의 크기가 현재크기보다 큰게 있다면
			d.pop_back();                               //뒷쪽을 빼준다.
		}
		d.push_back({cur,i});
		printf("%d ", d.front().first);          // 덱에서 맨 앞쪽에 있는 녀석이 그 구간의 최소값이다.
	}
	return 0;
}