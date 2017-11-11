//#include<stdio.h>
//#include<set>
//using namespace std;
//int main(){
//	set<int> s;
//	int n;
//	scanf("%d",&n);
//	for (int i = 0; i < n; i++){
//		int x;
//		scanf("%d",&x);
//		s.insert(x);
//	}
//	for (auto p : s){
//		printf("%d ",p);
//	}
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	int n;
	scanf("%d", &n);
	vector<int> a(n);
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(),a.end()),a.end());

	for (auto p : a){
		printf("%d ", p);
	}
	return 0;
}