#include<stdio.h>
#include<vector>
using namespace std;

int main(){
	int n;
	scanf("%d",&n);
	vector<int> a;
	vector<bool> c(n+1);
	for (int i = 2; i <= n; i++){
		if (c[i] == false){
			a.push_back(i);            // 이 줄이 있어서 위의 for문 조건을 i*i <= n 으로 할 수가 없다.
			for (int j = i * 2; j <= n; j += i){
				c[j] = true;
			}
		}
	}

	int left = 0;
	int right = 0;
	int sum = a.empty() ? 0 : a[0];
	int ans = 0;
	while (right < a.size()){
		if (sum <= n){
			if (sum==n)
				ans++;
			right++;
			if (right<a.size())
				sum += a[right];
		}
		else if (sum > n){
			sum -= a[left];
			left++;
		}
	}
	printf("%d", ans);
	return 0;
}
//#include <iostream>
//#include <vector>
//using namespace std;
//int main() {
//	int n;
//	cin >> n;
//
//	vector<bool> c(n + 1);
//	vector<int> p;
//	for (int i = 2; i <= n; i++) {
//		if (c[i] == false) {
//			p.push_back(i);
//			for (int j = i * 2; j <= n; j += i) {
//				c[j] = true;
//			}
//		}
//	}
//
//	int l = 0;
//	int r = 0;
//	int sum = p.empty() ? 0 : p[0];
//	int ans = 0;
//
//	while (l <= r && r < p.size()) {
//		if (sum <= n) {
//			if (sum == n) {
//				ans += 1;
//			}
//			r++;
//			if (r < p.size()) {
//				sum += p[r];
//			}
//		}
//		else {
//			sum -= p[l++];
//		}
//	}
//
//	cout << ans << '\n';
//	return 0;
//}