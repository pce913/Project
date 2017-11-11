#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//http://codersbrunch.blogspot.kr/2016/08/2385-secret-sharing.html
//345와 34512 중에서 사전순으로 큰 녀석은 34512 이다.
vector<string> a;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	int front_zero_cnt = 0;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		a.push_back(s);
		if (s[0] == '0')
			front_zero_cnt++;
	}
	if (front_zero_cnt == n){   //모든 원소의 앞부분이 0으로 시작하면 이것은 불가능한 경우이다.
		cout << "INVALID";
		return 0;
	}
	//공백문자열에 의해 순서가 뒤바뀔 수 있는 쌍(p,q)에 대하여 둘중에 어떤게 앞에 올지는 p+q < q+p로 알 수 있다.
	sort(a.begin(), a.end(), [](const string& x, const string& y){return x + y < y + x; });
	string temp = "";
	int k;
	for (k = 0; k < a.size(); k++){
		if (a[k][0] == '0')
			temp += a[k];
		else
			break;
	}
	//0으로 시작하는 녀석들을 제외하고 맨 앞에 누가 와야 하는지는 p+temp+q < q+temp+p로 알 수 있다.
	int p = min_element(a.begin() + k, a.end(), [&](const string& x, const string&y){return x + temp + y < y + temp + x; }) - a.begin();   //원소의 최소값의 위치를 알려준다.
	//물론 min_element를 안쓰고 pair를 이용해서 인덱스를 함께 저장하는 방법도 있지만 번거롭기 때문에 이 방법을 사용했다.
	cout << a[p];
	for (int i = 0; i < a.size(); i++){
		if (i != p){
			cout << a[i];
		}
	}
	return 0;
}