#include<iostream>
using namespace std;

char s[1000005];
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, sn;
	cin >> n >> sn >> (s + 1);

	int ans = 0;
	int io = 0;
	for (int i = 1; i + 2 <= sn;){
		if (s[i] == 'I' && s[i + 1] == 'O'){
			io++;
			if (s[i + 2] == 'I' && io == n){
				ans++;
				io--;
			}
			i += 2;
		}
		else{
			io = 0;
			i++;
		}
	}
	cout << ans;
	return 0;
}