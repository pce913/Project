#include<iostream>
#include<iomanip>
#include<map>
using namespace std;
long long m;   //게임을 승리하는 최적의 전략은 각 영역에 최대한 골고루 칩을 두는 것이다.
//칩을 골고루 두게 되면 어느 영역에 k개의 칩이 있다고 할 경우 어떠한 영역은 k+1개의 칩을 가지고 있을 것이다.
map< pair<long long, long long>, double > D;    //D[n][k]: 현재 n명이 살아있고 남은 라운드가 k개 일때 이길 확률. 
double go(long long n, long long k){
	if (n <= 0)
		return 0;
	if (k == 0)
		return n >= 1;
	if (D.count({ n, k }) > 0)
		return D[{n, k}];
	double p = (double)(n%m) / m; //칩이 더 많은 영역을 선택할 확률
	double ans = p*go(n - (n / m + 1), k - 1) + (1.0 - p)*go(n - (n / m), k - 1);
	return D[{n, k}] = ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	long long n, k;
	cin >> n >> m >> k;
	cout << fixed << setprecision(10) << go(n, k);
	return 0;
}