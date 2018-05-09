#include<stdio.h>
#include<vector>
using namespace std;

const int MAX = 200000;
const int MOD = 1000000007;

void update(vector<long long>& a,int p,long long diff){
	for (int i = p; i<a.size(); i += i&-i){
		a[i] += diff;
	}
}

long long sum(vector<long long>& a,int p){
	long long ans = 0;
	for (int i = p; i > 0; i -= i&-i){
		ans += a[i];
	}
	return ans;
}

long long sum(vector<long long>& a,int left,int right){
	if (left>right)
		return 0;
	return sum(a,right)-sum(a,left-1);
}

int main(){
	vector<long long> cnt(MAX+1);
	vector<long long> dist(MAX+1);
	int n;
	scanf("%d",&n);
	long long ans = 1;
	for (int i = 0; i < n; i++){
		long long x;
		scanf("%lld",&x);
		x++;                    // 왜 +1을 해주는거지? 이것을 안하면 시간초과를 받게 된다. x가 0일경우 update할때 문제가 된다.
		
		if (i != 0){                          //x를 기준으로 왼쪽과 오른쪽으로 나눠서 푼다. '거리'를 계산할때의 절댓값 처리가 귀찮기 때문이다.
			long long price = (x*sum(cnt, 1, x - 1) - sum(dist, 1, x - 1)) + (sum(dist, x + 1, MAX) - x*sum(cnt, x + 1, MAX));
			price %= MOD;
			ans = (ans*price) % MOD;
		}
		update(cnt,x,1);                     //cnt[x] : x에 심어져 있는 나무의 갯수.         
		update(dist, x, x);                  //dist[x] : x까지의 거리. x까지의 거리는 x 이다.
	}
	printf("%lld\n", ans);
	return 0;
}