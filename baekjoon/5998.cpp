#include<stdio.h>
#include<map>
using namespace std;
#define min(a,b) ((a) < (b) ? (a): (b))
//meet in the middle 테크닉 사용
long long lights[35];   //lights[i]: 전구 i가 다른 전구들과 어떻게 연결되어있는지 비트마스크로 저장.
map<long long, long long> mp;   //DP는 아니지만 map을 사용해서 저장하므로 반복문으로 처리하기 힘들다. 반복문으로 처리하면 long long 범위 이므로 시간초과 날거다.
long long n, m;
long long ans = 1e18;
void go1(long long i, long long mask, long long cost){
	if (i == n / 2){
		if (mp.count(mask) > 0){
			mp[mask] = min(mp[mask], cost);
		}
		else{
			mp[mask] = cost;
		}
		return;
	}

	go1(i + 1, mask, cost);
	go1(i + 1, mask^lights[i], cost + 1);
}

void go2(long long i, long long mask, long long cost){
	if (i == n){
		mask ^= (1LL << n) - 1;     //  B그룹에서 켜진 불은 A그룹에선 꺼져있어야 한다는 의미. 아하.
		if (mp.count(mask) > 0){
			ans = min(ans, mp[mask] + cost);
		}
		return;
	}

	go2(i + 1, mask, cost);
	go2(i + 1, mask^lights[i], cost + 1);
}

int main(){
	scanf("%lld %lld", &n, &m);
	for (long long i = 0; i < n; i++){
		lights[i] = (1LL << i);            //LL 안붙이면 틀린다.
	}
	for (long long i = 0; i < m; i++){
		long long x, y;
		scanf("%lld %lld", &x, &y);
		x--, y--;
		lights[x] |= (1LL << y);
		lights[y] |= (1LL << x);
	}

	//A와 B. 두 그룹으로 나눔.
	go1(0, 0, 0);
	go2(n / 2, 0, 0);
	printf("%lld", ans);
	return 0;
}