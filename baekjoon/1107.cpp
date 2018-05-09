#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int N, M;
bool b[10];
int len;

bool possible(int N){
	bool isPossible=true;
	len = 0;
	if (N == 0){
		if (b[0]){
			isPossible = false;
		}
		else{
			len++;
		}

	}
	while (N>0){    //N>0
		if (b[N % 10]){
			isPossible = false;
			break;
		}
		len++;
		N /= 10;
	}
	
	return isPossible;
}

int main(){
	scanf("%d %d", &N,&M);
	int t,att,ans=1000000;
	for (int i = 0; i < M; i++){
		scanf("%d",&t);
		b[t] = true;
	}
	for (int i = 0; i <= 1000000; i++){
		if (possible(i)){
			ans = min(ans, abs(N - i) + len);
		}
	}
	printf("%d",min(ans,abs(N-100)));
	return 0;
}