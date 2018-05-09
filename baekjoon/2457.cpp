#include<stdio.h>
#include<algorithm>
using namespace std;
const int MAXR = 1235;
int tree[MAXR];   //날짜 범위.
void update(int x, int value){
	for (int i = x; i <= MAXR; i += i&-i){
		tree[i] = max(tree[i], value);
	}
}

int query(int x){
	int ans = 0;
	for (int i = x; i > 0; i -= i&-i){
		ans = max(ans, tree[i]);
	}
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		int m1, d1, m2, d2;
		scanf("%d %d %d %d", &m1, &d1, &m2, &d2);
		int left = 100 * m1 + d1;
		int right = 100 * m2 + d2;
		update(left, right);
	}
	int sl = 100 * 3 + 1, sr = 100 * 11 + 30;
	int cur = query(sl);
	int ans = 1;
	while (cur <= sr){
		int next = query(cur);   //중간 구간을 구하는 쿼리가 없으므로 펜윅트리를 구간의 최대값처럼 쓸 수 있다.
		if (next == cur)
			break;
		cur = next;
		ans++;
	}
	printf("%d", cur > sr ? ans : 0); //  >= 아님. 문제에서 주어진것은 피는날짜와 '지는날짜 이기 때문에' 11월 30일에 꽃이 져버리면 곤란하다.
	return 0;
}
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//const int MAXR = 1235;
//int tree[4*MAXR];   //날짜 범위.
//
//int query(int node,int start,int end,int i,int j){
//	if (end < i || start > j)
//		return 0;
//	if (start >= i && end <= j)
//		return tree[node];
//	int x = query(2 * node, start, (start + end) / 2, i, j);
//	int y = query(2 * node + 1, (start + end) / 2+1,end , i, j);
//	return max(x, y);
//}
//
//void update(int node, int start, int end, int i, int value){
//	if (i < start || i > end)
//		return;
//	if (start == end){
//		tree[node] = max(tree[node], value);
//		return;
//	}
//	update(2 * node, start, (start + end) / 2, i, value);
//	update(2 * node + 1, (start + end) / 2 + 1, end, i, value);
//	tree[node] = max(tree[2 * node], tree[2 * node + 1]);
//}
//
//int main(){
//	int n;
//	scanf("%d", &n);
//	for (int i = 1; i <= n; i++){
//		int m1, d1, m2, d2;
//		scanf("%d %d %d %d", &m1, &d1, &m2, &d2);
//		int left = 100 * m1 + d1;
//		int right = 100 * m2 + d2;
//		update(1, 1, MAXR, left, right);
//	}
//	int sl = 100 * 3 + 1, sr = 100 * 11 + 30;
//	int cur = query(1, 1, MAXR, 1, sl);
//	int ans = 1;
//	while (cur <= sr){
//		int next = query(1, 1, MAXR, 1, cur);
//		if (next == cur)
//			break;
//		cur = next;
//		ans++;
//	}
//	printf("%d", cur > sr ? ans : 0); //  >= 아님. 문제에서 주어진것은 피는날짜와 '지는날짜 이기 때문에' 11월 30일에 꽃이 져버리면 곤란하다.
//	return 0;
//}