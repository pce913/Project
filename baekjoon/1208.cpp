#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
                                             // 이분탐색 사용
int main(){
	int n, s;
	scanf("%d %d",&n,&s);
	vector<int> a(n);
	for (int i = 0; i < n; i++){
		scanf("%d",&a[i]);
	}
	int m = n / 2;
	n = n - m;
	vector<int> first(1 << n);    // 부분집합의 갯수 2^n
	for (int i = 0; i < (1 << n); i++){      
		for (int k = 0; k < n; k++){
			if (i&(1 << k)){                 // 비트 마스크로 원소 포함여부 확인
				first[i] += a[k];                     // i 집합에서 1의 위치를 탐색 
			}
		}
	}
	vector<int> second(1 << m);
	for (int i = 0; i < (1 << m); i++){
		for (int k = 0; k < m; k++){
			if (i&(1 << k)){              
				second[i] += a[k+n];                     
			}
		}
	}
	sort(first.begin(),first.end());   
	sort(second.begin(), second.end());

	n = (1 << n);
	m = (1 << m);
	long long ans = 0;
	for (int i = 0; i < n; i++){
		int what = s - first[i];

		int left = 0;
		int right = m-1;
		while (left <= right){
			int mid = (left + right) / 2;
			if (what < second[mid]){
				right = mid - 1;
			}
			else if (what > second[mid]){
				left = mid + 1;
			}
			else{
				long long c1 = 1;
				long long c2 = 1;             // 앞 뒤로 확인
				int& curr1 = i;
				int curr2 = mid;
				while (curr1 < n-1 && first[curr1] == first[curr1 + 1]){
					c1++;
					curr1++;
				}

				while (curr2 < m-1 && second[curr2]==second[curr2 + 1]){
					c2++;
					curr2++;
				}

				curr2 = mid;
				while (curr2 > 0  && second[curr2] == second[curr2 - 1]){
					c2++;
					curr2--;
				}
				ans +=c1*c2;
				break;
			}
		}
	}
	if (s == 0)
		ans--;
	printf("%lld",ans);
	return 0;
}
//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//int main() {
//	int n, s;
//	cin >> n >> s;
//	vector<int> a(n);
//	for (int i = 0; i<n; i++) {
//		cin >> a[i];
//	}
//	int m = n / 2;
//	n = n - m;
//	vector<int> first(1 << n);
//	for (int i = 0; i<(1 << n); i++) {
//		for (int k = 0; k<n; k++) {
//			if (i&(1 << k)) {
//				first[i] += a[k];
//			}
//		}
//	}
//	vector<int> second(1 << m);
//	for (int i = 0; i<(1 << m); i++) {
//		for (int k = 0; k<m; k++) {
//			if (i&(1 << k)) {
//				second[i] += a[k + n];
//			}
//		}
//	}
//	sort(first.begin(), first.end());
//	sort(second.begin(), second.end());
//	reverse(second.begin(), second.end());
//	n = (1 << n);
//	m = (1 << m);
//	int i = 0;
//	int j = 0;
//	long long ans = 0;
//	while (i < n && j < m) {
//		if (first[i] + second[j] == s) {
//			long long c1 = 1;
//			long long c2 = 1;
//			i += 1;
//			j += 1;
//			while (i < n && first[i] == first[i - 1]) {
//				c1 += 1;
//				i += 1;
//			}
//			while (j < m && second[j] == second[j - 1]) {
//				c2 += 1;
//				j += 1;
//			}
//			ans += c1*c2;
//		}
//		else if (first[i] + second[j] < s) {
//			i += 1;
//		}
//		else {
//			j += 1;
//		}
//	}
//	if (s == 0) ans -= 1;
//	cout << ans << '\n';
//	return 0;
//}