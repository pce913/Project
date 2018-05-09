//#include<stdio.h>
//#include<vector>
//#include<cmath>
//using namespace std;
//
//void update(vector<int>& tree, int node, int start, int end, int i, int value){
//	if (i > end || i < start)
//		return;
//	if (start == end){
//		tree[node] = value;
//	}
//	else {
//		update(tree, 2 * node, start, (start + end) / 2, i, value);
//		update(tree, 2 * node + 1, (start + end) / 2 + 1, end, i, value);
//		tree[node] = tree[2 * node] * tree[2 * node + 1];
//	}
//}
//
//int query(vector<int>& tree,int node,int start,int end,int left,int right){          // 곱을 구하는 트리
//	if (left > end || right < start)
//		return 1;
//	if (left <= start && right >= end){
//		return tree[node];
//	}
//	int m1=query(tree, 2 * node, start, (start + end) / 2, left, right);
//	int m2=query(tree, 2 * node+1, (start + end) / 2+1,end , left, right);
//	return m1*m2;
//}
//
//void init(vector<int>& tree, vector<int>& a, int node, int start, int end){
//	if (start == end)
//		tree[node] = a[start];
//	else{
//		init(tree, a, 2 * node, start, (start + end) / 2);
//		init(tree, a, 2 * node + 1, (start + end) / 2+1, end);
//		tree[node] = tree[2 * node] * tree[2 * node + 1];
//	}
//}
//
//
//int main(){
//	int n, k;
//	while (scanf("%d %d", &n, &k) == 2){
//		vector<int> a(n + 1);
//		int h = ceil(log2(n));
//		int tree_size = (1 << (h + 1));
//		vector<int> tree(tree_size);            
//		for (int i = 1; i <= n; i++){
//			scanf("%d",&a[i]);
//			if (a[i] > 0)
//				a[i] = 1;
//			if (a[i] < 0)
//				a[i] = -1;
//		}
//		init(tree, a, 1, 1, n );
//
//		for (int T = 0; T < k; T++){
//			char x;
//			int b, c;
//			scanf(" %c %d %d", &x, &b, &c);          // scanf 할때 앞에 한칸 띄워줘야 한다.
//			if (x == 'C'){
//				if (c>0)
//					c = 1;
//				if (c < 0)
//					c = -1;
//				update(tree, 1, 1, n, b, c);
//			}
//			else if (x == 'P'){
//				int temp = query(tree,1,1,n,b,c);
//				char ans = '0';
//				if (temp>0){
//					ans = '+';
//				}
//				else if (temp < 0){
//					ans = '-';
//				}
//				printf("%c", ans);
//			}
//		}
//		printf("\n");
//	}
//	return 0;
//}
#include <cstdio>
#include <vector>
using namespace std;
const int inf = 200000;
int sum(vector<int> &tree, int i) {
	int ans = 0;
	while (i > 0) {
		ans += tree[i];
		i -= i&-i;
	}
	return ans;
}
int sum(vector<int> &tree, int start, int end) {
	return sum(tree, end) - sum(tree, start - 1);
}
void update(vector<int> &tree, int i, int diff) {
	while (i < tree.size()) {
		tree[i] += diff;
		i += i&-i;
	}
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		vector<int> a(n + 1);
		vector<int> tree(n + 1);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			if (a[i] < 0) {            // a[i]가 0보다 작을 경우에는 tree[i]를 1로 초기화 해줌 음수의 갯수를 저장
				update(tree, i, 1);
			}
			else if (a[i] == 0) {          //a[i]가 0일경우 tree[i]를 아주 큰 수로 초기화 해줌
				update(tree, i, inf);            
			}                               //a[i]가 양수일 경우에는 tree[i]를 0으로 초기화 해줌.
		}
		while (m--) {
			char cmd;
			scanf(" %c", &cmd);
			if (cmd == 'C') {
				int index, value;
				scanf("%d %d", &index, &value);
				if (a[index] < 0) {
					update(tree, index, -1);
				}
				else if (a[index] == 0) {
					update(tree, index, -inf);
				}
				a[index] = value;
				if (a[index] < 0) {
					update(tree, index, 1);
				}
				else if (a[index] == 0) {
					update(tree, index, inf);
				}
			}
			else if (cmd == 'P') {
				int start, end;
				scanf("%d %d", &start, &end);
				int cnt = sum(tree, start, end);
				if (cnt > n) {
					putchar('0');
				}
				else if (cnt % 2 == 0) {          // 음수가 짝수개이다.
					putchar('+');
				}
				else {                          // 음수가 홀수개 이다.
					putchar('-');
				}
			}
		}
		puts("");
	}
	return 0;
}