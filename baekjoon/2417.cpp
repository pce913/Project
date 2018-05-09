#include<iostream>
using namespace std;
//long long
const long long stand = 3037000499LL;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	long long n;
	cin >> n;
	if (n > stand*stand){
		cout << "3037000500";
		return 0;
	}
	long long left = 0, right = stand;
	long long ans = 0;
	while (left <= right){
		long long mid = (left + right) >> 1;
		if (mid*mid >= n){
			right = mid - 1LL;
			ans = mid;
		}
		else{
			left = mid + 1LL;
		}
	}
	cout << ans;
	return 0;
}