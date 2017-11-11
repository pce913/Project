#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	int sum = 0;     //3의 배수임을 알기 위해서 각 자리의 합을 구한다.
	for (int i = 0; i < s.size(); i++){
		sum += s[i] - '0';
	}
	sort(s.begin(), s.end());
	if (s[0] == '0' && sum % 3 == 0){
		reverse(s.begin(), s.end());
		cout << s;
	}
	else{
		cout << "-1";
	}
	return 0;
}
//#include<iostream>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	string s;
//	cin >> s;
//	sort(s.begin(), s.end());
//	reverse(s.begin(), s.end());
//	int num = atoi(s.c_str());    //입력이 최대 10^5개의 숫자로 이루어져 있으므로
//	if (num % 30 == 0)             //숫자로 바꿀 수가 없다.
//		cout << s;
//	else
//		cout << "-1";
//	return 0;
//}