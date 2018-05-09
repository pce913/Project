#include<iostream>
#include<cstring>
using namespace std;

long double D[20][20][20];  //D[n][i][j] : n까지 보았을때 A가 i득점을 하고, B가 j득점을 할 확률
bool isPrime[20];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	memset(isPrime, true, sizeof(isPrime));
	isPrime[0] = false;
	isPrime[1] = false;
	for (int i = 2; i*i <= 18; i++){
		if (isPrime[i]){
			for (int j = i*i; j <= 18; j += i){
				isPrime[j] = false;
			}
		}
	}
	long double a_win, b_win;
	cin >> a_win >> b_win;
	a_win /= 100.0;
	b_win /= 100.0;
	double a_lose = 1.0 -  a_win;
	double b_lose = 1.0 - b_win;

	D[1][0][0] = a_lose*b_lose;
	D[1][1][0] = a_win*b_lose;
	D[1][0][1] = a_lose*b_win;
	D[1][1][1] = a_win*b_win;
	for (int i = 1; i <= 18; i++){
		for (int j = 0; j <= 18; j++){
			for (int k = 0; k <= 18; k++){
				if (j > i || k > i)
					break;
				if (j - 1 >= 0){
					D[i][j][k] += D[i - 1][j - 1][k] * a_win*b_lose;
				}
				if (k - 1 >= 0){
					D[i][j][k] += D[i - 1][j][k - 1] * a_lose*b_win;
				}
				if (j - 1 >= 0 && k - 1 >= 0){
					D[i][j][k] += D[i - 1][j - 1][k - 1] * a_win*b_win;
				}
				D[i][j][k] += D[i - 1][j][k] * a_lose*b_lose;
			}
		}
	}

	long double ans = 0.0;
	for (int i = 0; i <= 18; i++){
		for (int j = 0; j <= 18; j++){
			if (isPrime[i] || isPrime[j]){
				ans += D[18][i][j];
			}
		}
	}
	cout << ans;
	return 0;
}