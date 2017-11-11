//#include<stdio.h>
//#include<vector>
//using namespace std;
//typedef vector< vector<long long> > matrix;
//const long long mod = 1000000007LL;
//
//matrix operator * (const matrix& a,const matrix& b){
//	int n = a.size();
//	matrix c(n,vector<long long>(n));
//	for (int i = 0; i < n; i++){
//		for (int j = 0; j < n; j++){
//			for (int k = 0; k < n; k++){
//				c[i][j] += a[i][k] * b[k][j];
//			}
//			c[i][j] %= mod;
//		}
//	}
//	return c;
//}
//
//int main(){
//	long long n;
//	scanf("%lld",&n);
//	if (n <= 1){
//		printf("%d",n);
//		return 0;
//	}
//	n -= 1;
//
//	matrix ans = { { 1, 0 }, { 0, 1 } };
//	matrix a = { { 1, 1 }, { 1, 0 } };
//	while (n > 0){
//		if (n % 2 == 1){
//			ans = ans*a;
//		}
//		a = a*a;
//		n /= 2;
//	}
//	printf("%lld",ans[0][0]);
//	return 0;
//}
#include<stdio.h>
#include<map>
using namespace std;
map<long long,long long> d;
const long long mod = 1000000007LL;

long long fibo(long long n){
	if (n <= 0){
		return 0;
	}
	else if (n == 1){
		return 1;
	}
	else if(n==2){
		return 1;
	}
	else if (d.count(n) > 0){
		return d[n];
	}
	else{
		if (n % 2 == 1){
			long long m = (n+1)/2;
			long long t1 = fibo(m);
			long long t2 = fibo(m-1);
			d[n] = t1*t1 + t2*t2;
			d[n] %= mod;
			return d[n];
		}
		else{
			long long m = n / 2;
			long long t1 = fibo(m-1);
			long long t2 = fibo(m);
			d[n] = (2LL * t1 + t2)*t2;
			d[n] %= mod;
			return d[n];
		}
	}
}

int main(){
	long long n;
	scanf("%lld",&n);
	printf("%lld",fibo(n));
	return 0;
}