//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//int main(){
//	int n,m;
//	scanf("%d",&n);
//	vector<int> a(n);
//	for (int i = 0; i < n; i++){
//		scanf("%d",&a[i]);
//	}
//	sort(a.begin(),a.end());
//
//	scanf("%d",&m);
//	for (int i = 0; i < m; i++){
//		int q;
//		scanf("%d",&q);
//
//		int left = 0;
//		int right = a.size() - 1;
//		bool isFind = false;
//		while (left <= right){
//			int mid = (left + right) / 2;
//			if (a[mid] > q){
//				right = mid - 1;
//			}
//			else if (a[mid] < q){
//				left = mid + 1;
//			}
//			else{
//				isFind = true;
//				break;
//			}
//		}
//		printf("%d ",isFind);
//	}
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
	int n, m;
	scanf("%d", &n);
	vector<int> a(n);
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	sort(a.begin(), a.end());

	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		int q;
		scanf("%d", &q);
		printf("%d ", binary_search(a.begin(),a.end(),q));
	}
	return 0;
}