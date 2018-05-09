#include<stdio.h>

const long long MOD = 100000;
char S[202];
long long D[201][201];
bool check[201][201];
char open[3] = {'(','{','['};
char close[3] = {')','}',']'};
bool isOver = false;
bool xcheck = false;


long long go(int i,int j){
	if (i > j)               // 확인을 다 했다.
		return 1;

	if (check[i][j])
		return D[i][j];

	check[i][j] = true;
	long long& ans = D[i][j];
	for (int k = i + 1; k <= j; k+=2){             // k++ 도 좋지만 k+=2 가 더 좋다. 짝수번째만 확인하는 것이다.
		for (int l = 0; l < 3; l++){              // 괄호 특성상 홀수 번째는 확인해 봤자 어차피 짝이 맞지 않는 괄호뿐이기 때문이다.
			if (S[i] == open[l] || S[i] == '?'){
				if (S[k] == close[l] || S[k] == '?'){
					long long temp = (go(i + 1, k - 1)%MOD)*(go(k + 1, j)%MOD);
					ans += temp%MOD;
					if (ans>MOD){
						isOver = true;
					}
					ans %= MOD;
				}
			}
		}
	}

	return ans;
}

int main(){
	int n;
	scanf("%d",&n);
	scanf("%s", &S[1]);
	long long ans=go(1, n);
	if (isOver){
		printf("%05lld",ans);
	}
	else{
		printf("%lld", ans);
	}	
	return 0;
}