#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
	int n;
	while (scanf("%d", &n) == 1){
		vector<int> a;
		for (int i = 1; i <= n; i++){
			int x;
			scanf("%d", &x);
			auto it = lower_bound(a.begin(), a.end(),x);
			if (it == a.end()){
				a.push_back(x);
			}
			else{
				*it = x;
			}
		}
		printf("%d\n", a.size());
	}
	return 0;
}
//#include<stdio.h>
//#include<cstring>
//#include<algorithm>
//using namespace std;
//
////int a[100005];
//const int MAXN = 100005;
//int tree[4 * MAXN];
//
//void update(int node,int start,int end,int i,int value){
//	if (i > end || i < start)
//		return;
//	tree[node] = max(tree[node], value);
//	if (start != end){
//		update(2 * node, start, (start + end) / 2, i, value);
//		update(2 * node + 1, (start + end) / 2 + 1, end, i, value);
//	}
//}
//
//int query(int node,int start,int end,int i,int j){
//	if (i > end || j < start)
//		return 0;
//	if (start >= i && end <= j){
//		return tree[node];
//	}
//	int m1=query(2 * node, start, (start + end) / 2, i, j);
//	int m2=query(2 * node + 1, (start + end) / 2+1,end , i, j);
//	return max(m1, m2);
//}
//
//int main(){
//	int n;
//	while (scanf("%d", &n) == 1){
//		memset(tree, 0, sizeof(tree));
//		int ans = 0;
//		for (int i = 1; i <= n; i++){
//			int x;
//			scanf("%d",&x);
//			int temp = query(1, 1, MAXN, 1, x - 1);
//			ans = max(ans, temp + 1);
//			update(1, 1, MAXN, x, temp + 1);
//		}
//		printf("%d\n",ans);
//	}
//	return 0;
//}