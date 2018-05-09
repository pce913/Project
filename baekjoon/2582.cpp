#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
//koosaga 코드 참조
//simulated anealing 기법
//http://koosaga.com/3
int n;
struct apple{
	char str[33][33];
	int cnt[33];
	int res(){
		int res = 0;
		for (int i = 0; i<n; i++){
			res += min(cnt[i], n - cnt[i]);
		}
		return res;
	}
}od, nw;

void change(){
	nw = od;
	int i = rand() % n;
	for (int j = 0; j<n; j++){
		if (nw.str[j][i] == 'T') nw.cnt[j]--, nw.str[j][i] = 'H';
		else nw.cnt[j]++, nw.str[j][i] = 'T';
	}
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	srand(6969696969);
	cin >> n;
	for (int i = 0; i<n; i++) {
		cin >> od.str[i];
		for (int j = 0; j<n; j++) {
			if (od.str[i][j] == 'T') od.cnt[i]++;
		}
	}
	double temp = 1;
	for (int i = 0; i<65536; i++){
		change();
		if (od.res() - nw.res()> log(rand() % 10000 / 1e4) * 1.0 * temp) od = nw;
		temp *= 0.99998;
	}
	cout << od.res();
}