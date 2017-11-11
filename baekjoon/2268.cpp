#include<stdio.h>
#include<algorithm>
using namespace std;

const long long MAXN = 1000005;

long long tree[MAXN];
long long a[MAXN];
long long n, m;

long long query(long long x){
	long long ans = 0;
	for (long long i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

void update(long long x,long long value){
	for (long long i = x; i <= n; i += i&-i){
		tree[i] += value;
	}
}

int main(){
	scanf("%lld %lld",&n,&m);
	for (long long q = 0; q < m; q++){
		long long querys, x, y;
		scanf("%lld %lld %lld",&querys,&x,&y);

		if (querys == 0){   // sum 함수
			if (x>y)
				swap(x, y);
			printf("%lld\n", query(y) - query(x - 1));
		}
		else{    //update 함수
			long long value = y - a[x];
			a[x] = y;
			update(x, value);
		}
	}
	return 0;
}