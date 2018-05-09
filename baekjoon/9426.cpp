#include<stdio.h>
#include<cmath>
#include<vector>
using namespace std;
const int MAX = 65536;

void update(vector<int>& tree,int node,int start,int end,int i,int diff){
	if (i > end || i < start) {
		return;
	}
	tree[node] += diff;
	if (start != end) {
		update(tree, node * 2, start, (start + end) / 2, i, diff);
		update(tree, node * 2 + 1, (start + end) / 2 + 1, end, i, diff);
	}
}

int query(vector<int>& tree,int node,int start,int end,int k){          // 몇번째가 어떤 값인지를 구하는 트리
	if (start == end){
		return start;
	}
	if (k <= tree[2 * node]){
		return query(tree,2*node,start,(start+end)/2,k);
	}
	else{
		return query(tree,2*node+1,(start+end)/2+1,end,k-tree[2*node]);
	}
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	int h = (int)ceil(log2(MAX));
	int tree_size = (1 << (h + 1));
	vector<int> a(n);
	vector<int> tree(tree_size);
	for (int i = 0; i < n; i++){
		scanf("%d",&a[i]);
	}
	for (int i = 0; i < k-1; i++){
		update(tree, 1, 0, MAX-1, a[i], 1);
	}
	long long ans = 0;
	for (int i = k-1; i < n; i++){	
		update(tree, 1, 0, MAX-1, a[i], 1);
		ans += (long long)query(tree, 1, 0, MAX-1, (k + 1) / 2);
		update(tree, 1, 0, MAX-1, a[i - k + 1], -1);
	}
	printf("%lld",ans);
	return 0;
}
//#include <cstdio>
//#include <cmath>
//#include <cassert>
//#include <vector>
//#include <algorithm>
//using namespace std;
//const int MAX = 65536;
//void update(vector<int> &tree, int node, int start, int end, int i, int diff) {
//	if (i > end || i < start) {
//		return;
//	}
//	if (start == end) {
//		tree[node] += diff;
//		return;
//	}
//	update(tree, node * 2, start, (start + end) / 2, i, diff);
//	update(tree, node * 2 + 1, (start + end) / 2 + 1, end, i, diff);
//	tree[node] = tree[node * 2] + tree[node * 2 + 1];
//}
//int kth(vector<int> &tree, int node, int start, int end, int k) {
//	if (start == end) {
//		return start;
//	}
//	if (k <= tree[node * 2]) {
//		return kth(tree, node * 2, start, (start + end) / 2, k);
//	}
//	else {
//		return kth(tree, node * 2 + 1, (start + end) / 2 + 1, end, k - tree[node * 2]);
//	}
//}
//int main() {
//	int n, k;
//	scanf("%d %d", &n, &k);
//	int h = (int)ceil(log2(MAX));
//	int tree_size = (1 << (h + 1));
//	vector<int> a(n);
//	vector<int> tree(tree_size);
//	for (int i = 0; i<n; i++) {
//		scanf("%d", &a[i]);
//	}
//	for (int i = 0; i<k - 1; i++) {
//		update(tree, 1, 0, MAX - 1, a[i], 1);
//	}
//	long long ans = 0;
//	for (int i = k - 1; i<n; i++) {
//		update(tree, 1, 0, MAX - 1, a[i], 1);
//		printf("query : %d\n", kth(tree, 1, 0, MAX-1, (k + 1) / 2));
//		ans += (long long)kth(tree, 1, 0, MAX - 1, (k + 1) / 2);
//		update(tree, 1, 0, MAX - 1, a[i - k + 1], -1);
//	}
//	printf("%lld\n", ans);
//	return 0;
//}