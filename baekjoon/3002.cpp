#include<stdio.h>
const int MAXN = 250005;
int tree[4*MAXN][10];   //tree[node][i]: node가 나타내는 구간에서 i가 몇개 있니?
int a[MAXN], lazy[4 * MAXN];
void init(int node,int start,int end){
	if (start == end){
		tree[node][a[start]] = 1;
	}
	else{
		init(2 * node, start, (start + end) / 2);
		init(2 * node + 1, (start + end) / 2 + 1, end);
		for (int i = 0; i < 10; i++){
			tree[node][i] = tree[2 * node][i] + tree[2 * node + 1][i];
		}
	}
}

void update_lazy(int node,int start,int end){
	if (lazy[node] != 0){
		int temp[10];
		for (int i = 0; i < 10; i++){//여태까지 등장한 갯수를 한칸씩 쉬프트 해주면 된다.
			temp[(i + lazy[node]) % 10] = tree[node][i]; //예를들어 구간에 3이 5번 등장했다면, 
		}                                       //1씩 업데이트 되므로 4가 5번 등장 한다고 할 수 있다.
		for (int i = 0; i < 10; i++){ 
			tree[node][i] = temp[i];
		}
		if (start != end){
			lazy[2 * node] += lazy[node];
			lazy[2 * node + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update_range(int node,int start,int end,int i,int j){
	update_lazy(node, start, end);
	if (start > j || end < i){
		return;
	}
	if (start >= i && end <= j){
		lazy[node] += 1;    //이렇게 업데이트하는것이 코드가 짧아서 참 좋구나.
		update_lazy(node, start, end);
		return;
	}
	update_range(2 * node, start, (start + end) / 2, i, j);
	update_range(2 * node + 1, (start + end) / 2+1,end , i, j);
	for (int i = 0; i<10; i++){
		tree[node][i] = tree[2 * node][i] + tree[2 * node + 1][i];
	}
}

int query(int node,int start,int end,int i,int j){
	update_lazy(node, start, end);
	if (start > j || end < i){
		return 0;
	}
	if (start >= i && end <= j){
		int ans = 0;
		for (int i = 0; i < 10; i++){
			ans += tree[node][i] * i;
		}
		return ans;
	}
	int s1 = query(2 * node, start, (start + end) / 2, i, j);
	int s2 = query(2 * node + 1, (start + end) / 2 + 1, end, i, j);
	return s1 + s2;
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		scanf("%1d",&a[i]);
	}
	init(1, 1, n);
	for (int qq = 0; qq < m; qq++){
		int a, b;
		scanf("%d %d",&a,&b);
		printf("%d\n",query(1,1,n,a,b));
		update_range(1, 1, n, a, b);
	}
	return 0;
}
//#include <cstdio>
//#include <algorithm>
//#define MAX_N 250000
//using namespace std;
////seg[node][i]: node가 나타내는 구간에서 i가 몇개 있니?
//int seg[4 * MAX_N][10], lazy[4 * MAX_N], n, m, x, y, v[10];
//int a[MAX_N];
//void u_lazy(int node, int x, int y) {
//	if (!lazy[node])return;
//	for (int i = 0; i < 10; i++)   //업데이트되는 값이 1이므로 값들을 한칸씩 쉬프트 해준다. 아하. 
//		v[(i + lazy[node]) % 10] = seg[node][i];
//	for (int i = 0; i < 10; i++)
//		seg[node][i] = v[i];
//	if (x != y) {
//		lazy[node * 2] += lazy[node];
//		lazy[node * 2 + 1] += lazy[node];
//	}
//	lazy[node] = 0;
//	return;
//}
//int init(int pos, int val, int node, int x, int y) {
//	if (pos < x || y < pos)
//		return seg[node][val];
//	if (x == y)   //여기서는 결국 x==y==pos가 될 것이다. 일종의 update이다.
//		return seg[node][val] = seg[node][val] + 1;
//	int mid = (x + y) >> 1;
//	return seg[node][val] = init(pos, val, node * 2, x, mid) + init(pos, val, node * 2 + 1, mid + 1, y);
//}
//void update(int lo, int hi, int node, int x, int y) {
//	u_lazy(node, x, y);
//	if (y < lo || hi < x)
//		return;
//	if (lo <= x&&y <= hi) {
//		lazy[node]++;   //update 시키려는 구간을 나타내는 lazy값을 1 증가시킨다. 즉, 구간에 몽땅 1을 증가시켜 줄 것이다.
//		u_lazy(node, x, y);   //lazy를 흡수 시켜야 하므로 update_lazy 호출
//		return;
//	}
//	int mid = (x + y) >> 1;
//	update(lo, hi, node * 2, x, mid);
//	update(lo, hi, node * 2 + 1, mid + 1, y);
//	for (int i = 0; i < 10; i++)
//		seg[node][i] = seg[node * 2][i] + seg[node * 2 + 1][i];
//}
//int query(int lo, int hi, int node, int x, int y) {
//	u_lazy(node, x, y);
//	if (y < lo || hi < x)
//		return 0;
//	if (lo <= x&&y <= hi) {
//		int ret = 0;
//		for (int i = 1; i < 10; i++) {
//			ret += seg[node][i] * i;
//		}
//		return ret;
//	}
//	int mid = (x + y) >> 1;
//	return query(lo, hi, node * 2, x, mid) + query(lo, hi, node * 2 + 1, mid + 1, y);
//}
//int main() {
//	scanf("%d%d", &n, &m);
//	for (int i = 1; i <= n; i++) {
//		int x;
//		scanf("%1d", &x);
//		init(i, x, 1, 1, n);
//	}
//
//	while (m--) {
//		scanf("%d%d", &x, &y);
//		printf("%d\n", query(x, y, 1, 1, n));
//		update(x, y, 1, 1, n);
//	}
//	return 0;
//}
