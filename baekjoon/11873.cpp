#include<stdio.h>
#include<algorithm>
#include<stack>
using namespace std;

int M[1005][1005];
int n, m;
stack<int> s;
int go(int aa[]){
	int ans = 0;
	for (int i = 1; i <= m; i++){
		while (!s.empty() && aa[s.top()] > aa[i]){
			int height = aa[s.top()];
			s.pop();
			int width = i - 1;  //
			if (!s.empty()){
				int right = i - 1;
				int left = s.top();
				width = right - left;
			}
			ans = max(ans, width*height);
		}
		s.push(i);
	}
	while (!s.empty()){
		int height = aa[s.top()];
		s.pop();
		int width = m;
		if (!s.empty()){
			int right = m;
			int left = s.top();
			width = right - left;
		}
		ans = max(ans, width*height);
	}
	return ans;
}

void solve(){
	int ans = 0;
	for (int q = n; q >= 1; q--){
		ans = max(ans, go(M[q]));
	}
	printf("%d\n", ans);
}

int main(){
	while (true){
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				scanf("%d", &M[i][j]);
				if (M[i][j] == 1)
					M[i][j] = M[i - 1][j] + 1;
			}
		}
		solve();
	}
	return 0;
}
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
/////*i행의 각 열마다 위로 연속된 1의 개수를 위 문제에서 히스토그램 높이라 생각하고 최대직사각형 
////넓이를 구한다.
////모든 행에서 이러한 방법을 적용했을 때 최대 직사각형 넓이를 찾는다.*/
//
//int tree[4005];  //구간의 최소 높이가 되는 인덱스를 저장
//int M[1005][1005];
//int a[1005][1005];
//int n, m;
//
//void accumulate(){
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= m; j++){
//			if (M[i][j] == 1)
//				a[i][j] = a[i - 1][j] + M[i][j];
//			else
//				a[i][j] = M[i][j];
//		}
//	}
//}
//
//void init(int aa[], int node, int start, int end){
//	if (start == end){
//		tree[node] = start;
//		return;
//	}
//	init(aa, 2 * node, start, (start + end) / 2);
//	init(aa, 2 * node + 1, (start + end) / 2 + 1, end);
//	if (aa[tree[2 * node]] < aa[tree[2 * node + 1]])
//		tree[node] = tree[2 * node];
//	else
//		tree[node] = tree[2 * node + 1];
//}
//
//int query(int aa[], int node, int start, int end, int i, int j){
//	if (i > end || j <start)
//		return -1;
//	if (start >= i && end <= j)
//		return tree[node];
//	int idx1 = query(aa, 2 * node, start, (start + end) / 2, i, j);
//	int idx2 = query(aa, 2 * node + 1, (start + end) / 2 + 1, end, i, j);
//	if (idx1 == -1)
//		return idx2;
//	else if (idx2 == -1)
//		return idx1;
//	else
//		return aa[idx1]<aa[idx2] ? idx1 : idx2;
//}
//
//
//int go(int aa[], int left, int right){
//	if (left > right)
//		return 0;
//
//	int mid = query(aa, 1, 1, m, left, right);
//	int left_area = go(aa, left, mid - 1);
//	int right_area = go(aa, mid + 1, right);
//	int mid_area = aa[mid] * (right - left + 1);
//	return max({ left_area, right_area, mid_area });
//}
//
//void solve(){
//	accumulate();
//	int ans = 0;
//	for (int q = n; q >= 1; q--){
//		init(a[q], 1, 1, m);
//		ans = max(ans, go(a[q], 1, m));
//	}
//	printf("%d\n", ans);
//}
//
//int main(){
//	while (true){
//		scanf("%d %d", &n, &m);
//		if (n == 0 && m == 0)
//			break;
//		for (int i = 1; i <= n; i++){
//			for (int j = 1; j <= m; j++){
//				scanf("%d", &M[i][j]);
//			}
//		}
//		solve();
//	}
//	return 0;
//}