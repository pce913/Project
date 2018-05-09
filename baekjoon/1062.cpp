#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int to[26] = { -1, 0, -1, 1, 2, 3, 4, 5, -1, 6, 7, 8, 9, -1, 10, 11, 12, 13, 14, -1, 15, 16, 17, 18, 19, 20 };
char s[20];
int a[55];

int ctz(int x){
	int ret = 0;
	while (!(x & 1)){
		x >>= 1;
		ret++;
	}
	return ret;
}
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++){
		cin >> s;
		int len = strlen(s);
		int t = 0;
		for (int j = 4; j < len - 4; j++){
			int val = to[s[j] - 'a'];
			if (val != -1)
				t |= (1 << val);
		}
		a[i] = t;
	}
	k -= 5;
	if (k == 0){
		int ans = 0;
		for (int i = 0; i < n; i++){
			if (a[i] == 0)
				ans++;
		}
		cout << ans;
		return 0;
	}
	else if (k < 0){
		cout << '0';
		return 0;
	}
	int bit = (1 << k) - 1;
	int max_bit = bit << (21 - k);
	int ans = 0;
	while (bit <= max_bit){
		int temp = 0;
		for (int i = 0; i < n; i++){
			if ((bit&a[i]) == a[i])
				temp++;
		}
		ans = max(ans, temp);
		int t = bit | (bit - 1);     //next_permutation을 bit로 구현.
		bit = (t + 1) | (((~t & -~t) - 1) >> (ctz(bit) + 1));
	}
	cout << ans;
	return 0;
}