//#include<stdio.h>
//#include<string>
//#include<vector>
//#include<iostream>
//using namespace std;
//long long D[1<<15][101];          //D[S][M]: 순열에 포함된 수 S, 그때 나머지가 M인 것의 갯수
//bool check[1 << 15][101];
//
//int a[16];
//int len[16];
//int ten[51];        //10의 거듭제곱꼴을 미리 다 구해놓음.
//int n;
//int k;       //나누는 수 k
//long long gcd(long long a, long long b){     // 기약분수 형태로 나타내기 위해 최대공약수 구해줌.
//	return b == 0 ? a : gcd(b, a%b);
//}
//
//long long go(int mask,int m){
//	
//	if (mask == 0 && m==0){       //여기 보기
//		return 1;
//	}
//
//	if (check[mask][m]){
//		return D[mask][m];
//	}
//	check[mask][m] = true;
//	long long& ans = D[mask][m];
//
//	/*for (int j = 0; j < k; j++){
//		for (int l = 0; l < n; l++){
//			if ((mask&(1 << l))==0){
//				int next = (j*ten[len[l]] % k + a[l] % k) % k;
//				ans += go(mask ^ (1 << l), next);
//			}
//		}
//	}*/
//	for (int j = 0; j < k; j++){
//		for (int l = 0; l < n; l++){
//			if (mask&(1 << l)){
//				int next = (j*ten[len[l]]%k - a[l]%k) % k;             // 이게 잘못되었음.
//				ans += go(mask & ~(1 << l), next);           //ㅣ번 비트 끄기.
//			}
//		}
//	}
//	return ans;
//}
//
//int main(){
//	scanf("%d",&n);
//	vector<string> num(n);         //입력받는 집합의 원소들 num이 필요한 이유: len을 채워야 하기 때문이다.
//	
//	for (int i = 0; i < n; i++){
//		cin >> num[i];
//		len[i] = num[i].size();
//		//a[i] = stoi(num[i]);
//		//a[i] %= k;
//	}
//
//	scanf("%d",&k);
//	for (int i = 0; i < n; i++){       //num으로 입력 받은 수를 int형으로 변환함. stoi 직접 구현
//		for (int j = 0; j < len[i]; j++){
//			a[i] = a[i] * 10 + (num[i][j] - '0');
//			a[i] %= k;
//		}
//	}
//
//
//	ten[0] = 1;
//	for (int i = 1; i <= 50; i++){
//		ten[i] = ten[i - 1] * 10;
//		ten[i] %= k;
//	}
//	long long t1=0;
//	long long t2 = 1;
//	/*for (int i = 0; i < k; i++){
//		t1 += go(0, i);
//	}*/
//	t1 = go((1<<n)-1, 0);
//
//
//
//	for (int i = 2; i <= n; i++){         //분모로 할 n!을 구함
//		t2 *= (long long)i;
//	}
//
//	long long g = gcd(t1, t2);
//	t1 /= g;
//	t2 /= g;
//	printf("%lld/%lld",t1,t2);
//	return 0;
//}
#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
long long D[1 << 15][101];          //D[S][M]: 순열에 포함된 수 S, 그때 나머지가 M인 것의 갯수
bool check[1 << 15][101];

int a[16];
int len[16];
int ten[51];        //10의 거듭제곱꼴을 미리 다 구해놓음.
int n;
int k;       //나누는 수 k
long long gcd(long long a, long long b){     // 기약분수 형태로 나타내기 위해 최대공약수 구해줌.
	return b == 0 ? a : gcd(b, a%b);
}


int main(){
	scanf("%d", &n);
	vector<string> num(n);         //입력받는 집합의 원소들 num이 필요한 이유: len을 채워야 하기 때문이다.

	for (int i = 0; i < n; i++){
		cin >> num[i];
		len[i] = num[i].size();
		//a[i] = stoi(num[i]);
		//a[i] %= k;
	}

	scanf("%d", &k);
	for (int i = 0; i < n; i++){       //num으로 입력 받은 수를 int형으로 변환함. stoi 직접 구현
		for (int j = 0; j < len[i]; j++){
			a[i] = a[i] * 10 + (num[i][j] - '0');
			a[i] %= k;
		}
	}


	ten[0] = 1;
	for (int i = 1; i <= 50; i++){
		ten[i] = ten[i - 1] * 10;
		ten[i] %= k;
	}
	D[0][0] = 1;
	for (int i = 0; i < (1 << n); i++){   // 마스크 채우기
		for (int j = 0; j < k; j++){            //나머지 값들 : 0 ~ k-1  이거 왜 쓰는거지?
			for (int l = 0; l < n; l++){        //켜져있는 비트 확인
				if ((i&(1 << l)) == 0){
					int next = (j*ten[len[l]]%k+a[l]%k)%k;
					D[i | (1 << l)][next] += D[i][j];                          //이런경우 재귀로 어떻게 나타내나.
				}
			}
		}
	}
	long long t1 = D[(1<<n)-1][0];
	long long t2 = 1;

	for (int i = 2; i <= n; i++){         //분모로 할 n!을 구함
		t2 *= (long long)i;
	}

	long long g = gcd(t1, t2);
	t1 /= g;
	t2 /= g;
	printf("%lld/%lld", t1, t2);
	return 0;
}