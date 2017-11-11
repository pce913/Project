//#include<stdio.h>
//#include<vector>
//#include<cstring>
//using namespace std;
//#define MAXN 1000000001    //31624             //1000000001 이거하면 메모리 초과
//
//long long att;
//long long A, B;
//long long N, dsize;
//bool prime[MAXN];
//long long gcd(long long a, long long b){
//	return b == 0 ? a : gcd(b, a%b);
//}
//long long lcm(long long a, long long b, long long g){
//	return a*b / g;
//}
//
//long long calc(vector<long long >& d, long long y, long long _l, long long c, long long k){
//	if (c < 2){
//		return _l;
//	}
//
//	long long g;
//	long long l;
//	for (long long x = y + 1; x < dsize; x++){
//		g = gcd(_l, d[x]);
//		l = lcm(_l, d[x], g);
//		//k가 4이상 일때부터 재귀호출.
//		long long val = calc(d, x, l, c - 1, k);
//		if (val != 0){
//			//att += (B / val - A / val)*((!(k & 1)) ? -1 : 1);
//			if (!(k & 1)){        //k가 짝수이면
//				att -= B / val - A / val;
//			}
//			else{
//				att += B / val - A / val;
//			}
//		}
//
//		//prlong longf("%lld\n", B - A + 1 - att);
//	}
//	return 0;
//}
//
//
//long long main(){
//	long long T;
//	scanf("%d", &T);
//	for (long long tc = 1; tc <= T; tc++){
//		scanf("%lld %lld %lld", &A, &B, &N);
//		att = 0;
//		// 1. N의 약수를 구한다. 정확히는 소수인 약수를 구한다.
//		vector<long long> d;
//		memset(prime, true, sizeof(bool)* MAXN);
//
//		bool isNo = true;
//		long long q = 2;
//		long long temp = N;
//
//		vector<long long> primeNum;
//		for (long long i = 2; i*i <= MAXN ; i++){
//			if (prime[i] == true){
//				primeNum.push_back(i);
//				for (long long j = i + i; j < MAXN; j += i){    
//					prime[j] = false;
//				}
//			}
//		}
//		long long next = 0;
//		long long nsize = primeNum.size();
//		while (temp != 1){             //안나눠질 경우 while문을 안빠져나오므로 시간초과 나올 수 있다.    while문을 못빠져나와서 시간초과 나는 것이다!
//			if (temp%q == 0 && q <= MAXN && q >= 0){
//				do{
//					temp = temp / q;
//				} while (temp%q == 0);
//				d.push_back(q);            //q를 이용해서 prime[] 이나 d에 접근하면 런타임 에러  -> while문을 못빠져 나오면서 값이 계속 올라가서 런타임에러가 났음.
//			}
//			if (next < nsize){
//				q = primeNum[next];
//				next++;
//			}
//		}
//
//		// 2. 약수에 대해 에라토스테네스의 체를 한다. 여기서는 갯수가 중요하므로 연산 사용.
//		//    연산 도중에 '포함-배제원리' 사용해야 함.
//		dsize = d.size();
//		for (long long i = 0; i < dsize; i++){
//			att += B / d[i] - A / d[i];
//			if (A % d[i] == 0)
//				att += 1;
//
//		}
//		for (long long k = 2; k <= dsize; k++){
//			for (long long i = 0; i < dsize - 1; i++){
//				calc(d, i, d[i], k, k);
//			}
//		}
//		prlong longf("Case #%d: %lld\n", tc, B - A + 1 - att);
//	}
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<cmath>
#include<cstring>
using namespace std;
bool prime[100001];

long long gcd(long long a, long long b){
	return b == 0 ? a : gcd(b, a%b);
}
long long lcm(long long a, long long b){
	return a*b / gcd(a, b);
}

int main(){
	vector<long long> p;           // 소수를 구해 놓는다.
	memset(prime, true, sizeof(prime));
	for (long long i = 2; i*i <= 100000; i++){
		if (prime[i] == true){
			for (long long j = i*i; j <= 100000; j += i){               // 루트 N까지만 일단 소수를 구해 놓는다.
				prime[j] = false;
			}
		}
	}
	for (long long i = 2; i <= 100000; i++){
		if (prime[i]){
			p.push_back(i);
		}
	}
	long long T;
	scanf("%lld", &T);
	for (long long test = 1; test <= T; test++){
		long long a, b, n;
		scanf("%lld %lld %lld", &a, &b, &n);
											//n을 소인수분해 한다.
		vector<long long> prime_factor;
		long long tempN = n;
		for (long long i = 0; i < p.size(); i++){               // 별로 크지 않은 숫자.
			if (tempN%p[i] == 0){
				prime_factor.push_back(p[i]);
				while (tempN%p[i] == 0){       //&& tempN !=p[i]
					tempN /= p[i];
				}
			}
		}
		if (tempN != 1){         // 루트N까지의 소수로 계속 나눠줬는데도 1이 안되었다는것은
			prime_factor.push_back(tempN);   // 아주 큰 소수가 하나 남아있다는 뜻이다. 그것을 포함시켜줌.
		}

		long long ans = b - a + 1;
		for (long long bit = 1; bit < (1 << prime_factor.size()); bit++){  //
			long long on_bit_cnt = 0;
			long long LCM = 1;
			for (long long i = 0; i < prime_factor.size(); i++){
				if (bit&(1 << i)){
					LCM = lcm(LCM, prime_factor[i]);
					on_bit_cnt++;
				}
			}
			
			if (on_bit_cnt & 1){               // 조합하는 원소의 갯수가 홀수일때
				ans -= b / LCM - ((a - 1) / LCM);
			}
			else{
				ans += b / LCM - ((a - 1) / LCM);
			}
		}
		printf("Case #%lld: %lld\n", test, ans);
	}
	return 0;
}