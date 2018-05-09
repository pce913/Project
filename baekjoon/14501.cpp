#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

struct Info{
	int T, P;
};

int n;
Info a[16];
int D[16];    //D[n]: n부터 시작했을때의 최대 금액.
bool check[16];
int go(int day){
	int next_first = day + a[day].T;
	if (next_first > n+1){
		return -1e9;
	}
	if (check[day]){
		return D[day];
	}
	check[day] = true;

	D[day] = a[day].P;
	for (int i = next_first; i <= n; i++){
		int money = go(i);
		D[day] = max(D[day], a[day].P + money);
	}
	return D[day];
}

int main(){

	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d %d",&a[i].T,&a[i].P);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++){
		ans = max(ans, go(i));
	}
	printf("%d",ans);
	return 0;
}