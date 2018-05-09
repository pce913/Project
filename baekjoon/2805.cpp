#include<stdio.h>
#include<algorithm>
using namespace std;
int tree[1000005];
const int MAX = 2000000000;
int n, m;
long long go(long long len){
	long long ret = 0;
	for (int i = 1; i <= n; i++){
		if (tree[i] > len){
			ret += tree[i] - len;
		}
	}
	return ret;
}

int main(){

	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		scanf("%d",&tree[i]);
	}
	long long left = 1;
	long long right = MAX;
	long long ans = 0;
	while (left <= right){
		long long mid = (left + right) / 2;
		if (go(mid) >= m){
			ans = max(ans,mid);
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}

	}
	printf("%lld",ans);
	return 0;
}