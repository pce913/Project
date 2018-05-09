#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<tuple>
#include<iomanip>
#include<algorithm>
#include<functional>
#include<cmath>
#include<unordered_set>
#include<unordered_map>
using namespace std;
int a[200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, c;
	cin >> n >> c;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	sort(a + 1, a + 1 + n);
	int left = 1;
	int right = a[n] - a[1];
	int ans = 1;
	while (left <= right){
		int mid = (left + right) >> 1;
		int cnt = 1;  //설치해야 하는 공유기 갯수
		int s = a[1];  //공유기 사이의 거리르 최대로 해야 하므로 1번 자리에 무조건 하나 설치
		for (int i = 1; i + 1 <= n; i++){
			if (a[i + 1] - s >= mid){
				cnt++;
				s = a[i + 1];
			}
		}
		if (cnt >= c){   //공유기를 c개이상 설치했다면
			ans = max(ans, mid);
			left = mid + 1;   //거리를 늘려보아서 공유기를 더 적게 설치해야 한다.
		}
		else{
			right = mid - 1;
		}
	}
	cout << ans;
	return 0;
}
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<iostream>
//#include<string>
//#include<cstring>
//#include<vector>
//#include<stack>
//#include<queue>
//#include<set>
//#include<map>
//#include<tuple>
//#include<iomanip>
//#include<algorithm>
//#include<functional>
//#include<cmath>
//#include<unordered_set>
//#include<unordered_map>
//using namespace std;
//int a[200005];
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	int n, c;
//	cin >> n >> c;
//	for (int i = 1; i <= n; i++){
//		cin >> a[i];
//	}
//	sort(a + 1, a + 1 + n);
//	int left = 1;
//	int right = a[n] - a[1];
//	int ans = 1;
//	while (left <= right){
//		int mid = (left + right) >> 1;
//		int cnt = 1;  //설치해야 하는 공유기 갯수
//		int s = a[1];
//		for (int i = 1; i + 1 <= n; i++){
//			if (a[i + 1] - s >= mid){
//				cnt++;
//				s = a[i + 1];
//			}
//		}
//		if (cnt >= c){   //공유기를 c개이상 설치했다면
//			ans = max(ans, mid);
//			left = mid + 1;   //거리를 늘려보아서 공유기를 더 적게 설치해야 한다.
//		}
//		else{
//			right = mid - 1;
//		}
//	}
//	cout << ans;
//	return 0;
//}

//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//int M[200001];
//
//int main(){
//	int N, C;
//	scanf("%d %d",&N,&C);
//	for (int i = 1; i <= N; i++)
//		scanf("%d",&M[i]);
//	
//	sort(M, M + N);
//	int l = 1;
//	int r = M[N] - M[1];
//	int maxi = 1;
//	while (l <= r){
//		int m = (l + r) / 2;
//		
//		int cnt = 1;
//		int s = M[1];
//		for (int i = 1; i <= N-1; i++){
//			if (M[i + 1] - s >= m){
//				cnt++;
//				s = M[i + 1];
//			}
//		}
//
//		if (cnt >= C){
//			if (maxi < m)
//				maxi = m;
//			l = m + 1;
//		}
//		else
//			r = m - 1;
//	}
//	printf("%d",maxi);
//	return 0;
//}