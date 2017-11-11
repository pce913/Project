#include<stdio.h>
#include<algorithm>
using namespace std;
int a[100001];
int tree[300001];    // 배열의 최대길이보다 3배 정도로 잡아야 한다.

int query(int node, int start, int end, int i, int j){       // i,j 우리가 구하고 싶은 범위 i~j
	if (i > end || j < start)
		return 1300000000;
	if (i <= start && j >= end)
		return tree[node];

	return min(query(2 * node, start, (start + end) / 2, i, j),
		query(2 * node + 1, (start + end) / 2 + 1, end, i, j));
}

void init(int node, int start, int end){           // 구간의 start값과 end 
	if (start == end)
		tree[node] = a[start];
	else{
		init(2 * node, start, (start + end) / 2);
		init(2 * node + 1, (start + end) / 2 + 1, end);
		tree[node] = min(tree[2 * node], tree[2 * node + 1]);      // 구간의 최소값 미리 구해놓는다.
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	init(1, 1, n);
	for (int test = 0; test < m; test++){
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", query(1, 1, n, a, b));
	}
	return 0;
}
//#include<stdio.h>
//#include<algorithm>
//#include<vector>
//using namespace std;
//
//int query(vector<int>& tree, int node, int start, int end, int left, int right)
//{
//	if (left > end || right < start)
//		return 1300000000;
//	if (left <= start && end <= right)
//		return tree[node];
//
//	return min(query(tree, node * 2, start, (start + end) / 2, left, right),
//		query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right));
//}
//
//void init(vector<int>& arr, vector<int>& tree, int node, int start, int end)
//{
//	if (start == end){
//		tree[node] = arr[start];
//	}
//	else{
//		init(arr, tree, 2 * node, start, (start + end) / 2);
//		init(arr, tree, 2 * node + 1, (start + end) / 2 + 1, end);
//		tree[node] = min(tree[2*node],tree[2*node+1]);
//	}
//}
//int arr[100001];
//
//int main(){
//	int n, m;
//	scanf("%d %d", &n, &m);
//	vector<int> arr(n+1);
//	vector<int> tree(4*n);
//	for (int i = 1; i <= n; i++){
//		scanf("%d", &arr[i]);
//	}
//	init(arr,tree,1, 1, n);
//	for (int test = 0; test < m; test++){
//		int a, b;
//		scanf("%d %d", &a, &b);
//		printf("%d\n", query(tree,1, 1, n, a, b));
//	}
//	return 0;
//}