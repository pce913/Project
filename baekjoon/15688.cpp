#include<iostream>
using namespace std;

const int MAXN = 1000000;
int cnt[2 * MAXN + 5];  //Àý´ñ°ª.
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		int x;
		cin >> x;
		cnt[x + MAXN]++;
	}

	int tot = 0;
	for (int i = 0; i <= 2000000 && tot < n; i++){
		for (int j = 0; j < cnt[i]; j++){
			cout << i - MAXN << "\n";
			tot++;
		}
	}
	return 0;
}