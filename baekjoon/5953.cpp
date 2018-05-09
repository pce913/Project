#include<stdio.h>
#include<algorithm>
using namespace std;

const long long MAXN = 100005;
long long D[MAXN];
long long a[MAXN];
int main(){
	long long n;
	scanf("%lld",&n);
	for (long long i = 1; i <= n; i++){
		scanf("%lld",&a[i]);
	}
	
	for (long long i = 1; i <= n; i++){
		if (D[i - 1] > 0){
			D[i] = D[i - 1] + a[i];
		}
		else{
			D[i] = a[i];
		}
	}
	long long ans = -1e9-7;
	for (long long i = 1; i <= n; i++){
		ans = max(ans, D[i]);
	}
	printf("%lld",ans);
	return 0;
}