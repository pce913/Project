#include<stdio.h>
#include<stack>
#include<algorithm>
using namespace std;

int a[100005];
stack<int> s;

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++){
		while (!s.empty() && a[s.top()] > a[i]){  //while문이 돌때는 top에 위치한 보다 한뒤에 있는 녀석은
			int height = a[s.top()];              //top에 위치한 녀석의 높이보다 항상 높이가 높은게 보장된다.
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
		int height = a[s.top()];
		s.pop();
		int width = n;
		if (!s.empty()){
			int right = n;
			int left = s.top();
			width = right - left;
		}
		ans = max(ans, width*height);
	}
	printf("%d", ans);
	return 0;
}
//#include<stdio.h>
//#include<stack>
//#include<algorithm>
//using namespace std;
//
//int a[100005];
//stack<int> s;
//
//int main(){
//	int n;
//	scanf("%d",&n);
//	for (int i = 1; i <= n; i++){
//		scanf("%d",&a[i]);
//	}
//
//	int ans = 0;
//	for (int i = 1; i <= n; i++){
//		if (!s.empty()){
//			if (a[s.top()] <= a[i]){
//				s.push(i);
//			}
//			else{
//				while (!s.empty() && a[s.top()] > a[i]){
//					int height = a[s.top()];
//					s.pop();
//
//					int width = i;  //
//					if (!s.empty()){
//						int right = i - 1;
//						int left = s.top();
//						width = right - left + 1;
//					}
//					ans = max(ans, width*height);
//				}
//				s.push(i);
//			}
//		}
//		else{
//			s.push(i);
//		}
//	}
//	while (!s.empty()){
//		int height = a[s.top()];
//		s.pop();
//		int width = n;
//		if (!s.empty()){
//			int right = n;
//			int left = s.top();
//			width = right - left + 1;
//		}
//		ans = max(ans, width*height);
//	}
//	printf("%d",ans);
//
//	return 0;
//}

//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//int a[100005];
//int index_tree[400005];   //구간의 최소값을 가지는 인덱스를 저장하는 트리.
//int n;
//void init(int node,int start,int end){
//	if (start == end){
//		index_tree[node] = start;
//		return;
//	}
//	init(2 * node, start, (start + end) / 2);
//	init(2 * node + 1, (start + end) / 2 + 1, end);
//	if (a[index_tree[2*node]] < a[index_tree[2 * node+1]])
//		index_tree[node] = index_tree[2*node];
//	else
//		index_tree[node] = index_tree[2 * node + 1];
//}
//
//int query(int node,int start,int end,int i,int j){
//	if (i > end || j < start)           
//		return 0;                       
//	if (start >= i && end <= j)
//		return index_tree[node];
//	
//	int x = query(2 * node, start, (start + end) / 2, i, j);
//	int y = query(2 * node + 1, (start + end) / 2 + 1, end, i, j);
//	if (x == 0)
//		return y;
//	if (y == 0)
//		return x;
//	return a[x] < a[y] ? x : y;
//}
//
//
//int divide(int left,int right){ //구간의 최소 높이를 가지는 인덱스를 찾는다.
//	if (left > right)    //최소 높이를 찾는 이유는 최소 높이 일때는 직사각형의 양 끝이 어디인지 바로 알 수 있기 때문이다.
//		return 0;      ////그 양끝은 바로 현재 보고 있는 구간 left 와 right가 된다.
//	if (left == right)
//		return a[left];
//
//	int mid = query(1, 1, n, left, right);
//	int left_area = divide(left, mid - 1);
//	int right_area = divide(mid + 1,right);
//	int mid_area = a[mid]*(right - left + 1);
//	return max({ left_area, right_area, mid_area });
//}
//
//int main(){
//	scanf("%d",&n);
//	for (int i = 1; i <= n; i++)
//		scanf("%d",&a[i]);
//	
//	init(1,1,n);
//	printf("%d", divide(1, n));
//	return 0;
//}