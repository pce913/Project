//#include<stdio.h>
//#include<stack>
//#define MAX(a,b) ((a) > (b) ? (a): (b));
//using namespace std;
//
//long long M[100000];
//int main(){
//	while (true){
//		int n;
//		scanf("%d", &n);
//		if (n == 0)
//			break;
//		for (int i = 0; i < n; i++){
//			scanf("%lld",&M[i]);
//		}
//		stack<long long> s;
//		long long ans = 0;
//		for (int i = 0; i < n; i++){
//			while (!s.empty() && M[s.top()]>M[i]){
//				int height = M[s.top()];
//				s.pop();
//				long long width = i;
//				if (!s.empty()){
//					width = i - s.top()-1 ;   
//				}
//				ans = MAX(ans, width*height);
//			}
//			s.push(i);
//		}
//		while (!s.empty()){
//			long long height = M[s.top()];
//			s.pop();
//			long long width = n;
//			if (!s.empty()){
//				width = n - s.top()-1;
//			}
//			ans = MAX(ans,width*height);
//		}
//		printf("%lld\n",ans);
//	}
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<cmath>
using namespace std;                           // 세그먼트 트리 사용
                                               // 세그먼트 트리에 구간에서 가장 높이가 낮은 막대를 저장해 놓는다.
void init(vector<int>& a,vector<int>& tree,int node,int start,int end){
	if (start == end){
		tree[node] = start;       //index를 저장
	}
	else{
		init(a,tree,2*node,start,(start+end)/2);
		init(a,tree,2*node+1,(start+end)/2+1,end);
		if (a[tree[2 * node]] <= a[tree[2 * node + 1]]){
			tree[node] = tree[2 * node];
		}
		else{
			tree[node] = tree[2 * node + 1];
		}
	}
}

int query(vector<int>& a,vector<int>& tree,int node,int start,int end,int i,int j){
	if (i > end || j < start){
		return -1;
	}
	if (i <= start && j >= end){
		return tree[node];
	}
	int m1 = query(a,tree,2*node,start,(start+end)/2,i,j);
	int m2 = query(a, tree, 2 * node + 1, (start + end) / 2+1, end, i, j);
	if (m1 == -1){
		return m2;
	}
	else if (m2 == -1){
		return m1;
	}
	else{
		if (a[m1] <= a[m2]){                  // <= 작거나 같다 이다.
			return m1;
		}
		else{
			return m2;
		}
	}
}

long long largest(vector<int>& a, vector<int>& tree, int i, int j){     // 분할 정복   우리가 원하는 범위 i~j
	int n = a.size();
	int m = query(a,tree,1,0,n-1,i,j);                
	long long area=(long long)(j-i+1)*(long long)a[m];     // 가장 높이가 낮은 막대로 만들 수 있는 넓이.
	if (i <= m - 1){
		long long temp = largest(a,tree,i,m-1);
		if (area < temp){
			area = temp;
		}
	}
	if (m + 1 <= j){
		long long temp = largest(a,tree,m+1,j);
		if (area < temp){
			area = temp;
		}
	}
	return area;
}

int main(){
	while (true){
		int n;
		scanf("%d",&n);
		if (n == 0)
			break;
		vector<int> a(n);
		int h = (int)ceil(log2(n));
		int tree_size = (1<<(h+1));
		for (int i = 0; i < n; i++){
			scanf("%d",&a[i]);
		}
		vector<int> tree(tree_size);
		init(a,tree,1,0,n-1);
		printf("%lld\n",largest(a,tree,0,n-1));
	}
	return 0;
}
//#include <iostream>
//#include <cmath>
//#include <vector>
//#include <algorithm>
//using namespace std;
//void init(vector<int> &a, vector<int> &tree, int node, int start, int end) {
//	if (start == end) {
//		tree[node] = start;
//	}
//	else {
//		init(a, tree, node * 2, start, (start + end) / 2);
//		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
//		if (a[tree[node * 2]] <= a[tree[node * 2 + 1]]) {
//			tree[node] = tree[node * 2];
//		}
//		else {
//			tree[node] = tree[node * 2 + 1];
//		}
//	}
//}
//int query(vector<int> &a, vector<int> &tree, int node, int start, int end, int i, int j) {
//	if (i > end || j < start) {
//		return -1;
//	}
//	if (i <= start && end <= j) {
//		return tree[node];
//	}
//	int m1 = query(a, tree, 2 * node, start, (start + end) / 2, i, j);
//	int m2 = query(a, tree, 2 * node + 1, (start + end) / 2 + 1, end, i, j);
//	if (m1 == -1) {
//		return m2;
//	}
//	else if (m2 == -1) {
//		return m1;
//	}
//	else {
//		if (a[m1] <= a[m2]) {
//			return m1;
//		}
//		else {
//			return m2;
//		}
//	}
//}
//long long largest(vector<int> &a, vector<int> &tree, int start, int end) {
//	int n = a.size();
//	int m = query(a, tree, 1, 0, n - 1, start, end);
//	long long area = (long long)(end - start + 1)*(long long)a[m];
//	if (start <= m - 1) {
//		long long temp = largest(a, tree, start, m - 1);
//		if (area < temp) {
//			area = temp;
//		}
//	}
//	if (m + 1 <= end) {
//		long long temp = largest(a, tree, m + 1, end);
//		if (area < temp) {
//			area = temp;
//		}
//	}
//	return area;
//}
//int main() {
//	while (true) {
//		int n;
//		cin >> n;
//		if (n == 0) break;
//		vector<int> a(n);
//		for (int i = 0; i<n; i++) {
//			cin >> a[i];
//		}
//		int h = (int)(ceil(log2(n)) + 1e-9);
//		int tree_size = (1 << (h + 1));
//		vector<int> tree(tree_size);
//		init(a, tree, 1, 0, n - 1);
//		cout << largest(a, tree, 0, n - 1) << '\n';
//	}
//	return 0;
//}