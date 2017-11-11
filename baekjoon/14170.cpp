#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> a;

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		a.push_back(x);
	}
	sort(a.begin(), a.end());
	for (int i = 0; i < q; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		int left = lower_bound(a.begin(), a.end(), x) - a.begin();
		int right = upper_bound(a.begin(), a.end(), y) - a.begin();
		printf("%d\n",right-left);
	}
	return 0;
}
//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//struct Line{
//	int l, r;
//};
//
//vector<int> a;
//vector<Line> qlist;
//vector<int> xpos;
//int fn;
//int tree[500005];
//
//void update(int x,int value){
//	for (int i = x; i <= fn; i += i&-i){
//		tree[i] += value;
//	}
//}
//
//int query(int x){
//	int ans = 0;
//	for (int i = x; i > 0; i -= i&-i){
//		ans += tree[i];
//	}
//	return ans;
//}
//
//int main(){
//	int n, q;
//	scanf("%d %d",&n,&q);
//	for (int i = 0; i < n; i++){
//		int x;
//		scanf("%d",&x);
//		a.push_back(x);
//		xpos.push_back(x);
//	}
//	for (int i = 0; i < q; i++){
//		int x, y;
//		scanf("%d %d",&x,&y);
//		qlist.push_back({x,y});
//		xpos.push_back(x);
//		xpos.push_back(y);
//	}
//
//	fn = xpos.size();
//	sort(xpos.begin(), xpos.end());
//	xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
//	for (int i = 0; i < a.size(); i++){
//		a[i] = lower_bound(xpos.begin(), xpos.end(), a[i]) - xpos.begin() + 1;  //1 º£ÀÌ½º
//		update(a[i], 1);
//	}
//	for (int i = 0; i < qlist.size(); i++){
//		qlist[i].l = lower_bound(xpos.begin(), xpos.end(), qlist[i].l) - xpos.begin() + 1;
//		qlist[i].r = lower_bound(xpos.begin(), xpos.end(), qlist[i].r) - xpos.begin() + 1;
//		printf("%d\n", query(qlist[i].r) - query(qlist[i].l - 1));
//	}
//	return 0;
//}