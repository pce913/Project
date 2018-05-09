//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include<string>
//using namespace std;
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	string s;
//	cin >> s;
//	vector<int> num;
//	vector<int> sign;
//	int cur = 0;
//	sign.push_back(1);
//	for (int i = 0; i<s.size(); i++) {
//		if (s[i] == '+' || s[i] == '-') {
//			if (s[i] == '+') {
//				sign.push_back(1);
//			}
//			else {
//				sign.push_back(-1);
//			}
//			num.push_back(cur);
//			cur = 0;
//		}
//		else {
//			cur = cur * 10 + (s[i] - '0');
//		}
//	}
//	num.push_back(cur);
//	int ans = 0;
//	bool minus = false;
//	for (int i = 0; i<num.size(); i++) {
//		if (sign[i] == -1) {
//			minus = true;
//		}
//		if (minus) {
//			ans -= num[i];
//		}
//		else {
//			ans += num[i];
//		}
//	}
//	cout << ans;
//	return 0;
//}
#include<iostream>
#include<string>
#include<vector>
using namespace std;
vector<int> num;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	int minus_idx = 1e9;
	int cur = 0;
	bool check_minus = false;
	for (int i = 0; i < s.size(); i++){
		if (s[i] == '+' || s[i] == '-'){
			num.push_back(cur);
			cur = 0;
			if (s[i] == '-'){
				if (!check_minus){
					check_minus = true;
					minus_idx = num.size();
				}
			}
		}
		else{
			cur = cur * 10 + s[i] - '0';
		}
	}
	num.push_back(cur);

	int ans = 0;
	for (int i = 0; i < num.size(); i++){
		if (i < minus_idx){  // '-' 기호가 등장 했을때 부터 그 뒤로는 몽땅다 음수로 만들 수 있다.
			ans += num[i];
		}
		else{
			ans -= num[i];
		}
	}
	cout << ans;
	return 0;
}