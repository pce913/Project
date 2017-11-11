#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
using namespace std;

//도치의 쌍의 갯수를 찾아서 정렬 후 보내버리기
//도치: i< j 이면서 A[i]> A[j] 인 것.
map< vector<int>, double > D;   //D : 현재 상태의 수열에서의 기댓값
double go(vector<int>& a){
	if (D.count(a) > 0)
		return D[a];

	double ans = 0;
	int cnt = 0;   //교환 횟수
	for (int i = 0; i < (int)a.size() - 1; i++){
		for (int j = i + 1; j < (int)a.size(); j++){
			if (a[i]>a[j]){
				swap(a[i], a[j]);
				ans += go(a) + 1;     // 여기서 +1 하는 이유는 현재 상태의 수열에서 swap을 '한번' 한 것을 더해주는 것이다. 그래야 기댓값이다.
				cnt++;
				swap(a[i], a[j]);
			}
		}
	}
	if (cnt > 0){
		ans = ans / cnt;
	}
	return D[a] = ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int> a;
	for (int i = 0; i < n; i++){
		int x;
		cin >> x;
		a.push_back(x);
	}
	cout << fixed << setprecision(10) << go(a);
	return 0;
}