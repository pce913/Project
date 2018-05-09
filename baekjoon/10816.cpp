//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//int main(){
//	int n, m;
//	scanf("%d", &n);
//	vector<int> a(n);
//	for (int i = 0; i < n; i++){
//		scanf("%d", &a[i]);
//	}
//	sort(a.begin(), a.end());
//
//	scanf("%d", &m);
//	for (int i = 0; i < m; i++){
//		int q;
//		scanf("%d", &q);
//		auto p = equal_range(a.begin(),a.end(),q);
//		printf("%d ", p.second-p.first);
//	}
//	return 0;
//
#include<stdio.h>
#include<set>
using namespace std;

int main(){
	int n, m;
	scanf("%d", &n);
	multiset<int> s;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		s.insert(x);
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		int q;
		scanf("%d", &q);
		printf("%d ", s.count(q));
	}
	return 0;
}
