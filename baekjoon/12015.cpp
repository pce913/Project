#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

#define MAX 1000000

void update(vector<int>& tree, int node, int start, int end, int i, int value){
	if (i > end || i < start){
		return;
	}
	tree[node] = max(tree[node], value);
	if (start != end){
		update(tree, 2 * node, start, (start + end) / 2, i, value);
		update(tree, 2 * node + 1, (start + end) / 2 + 1, end, i, value);
	}
}

int query(vector<int>& tree, int node, int start, int end, int left, int right){     // 최대값을 찾는 쿼리
	if (left > end || right < start){
		return 0;
	}
	if (left <= start && right >= end){
		return tree[node];
	}
	return max(query(tree, 2 * node, start, (start + end) / 2, left, right), query(tree, 2 * node + 1, (start + end) / 2 + 1, end, left, right));
}

int main(){                                       //구간의 최대값으로 푼다.
	int n;                                       // init 함수는 필요가 없다
	scanf("%d", &n);
	int h = (int)ceil(log2(MAX));
	int tree_size = (1 << (h + 1));
	vector<int> tree(tree_size + 1);             //tree[i] : 수 i를 마지막으로 하는 가장 긴 증가하는 부분 수열의 길이  -> 이말은 약간 모호하다.
	int ans = 0;                                 // 구간의 최대를 구하기 위한 트리라고 생각하는게 더 좋다.
	for (int i = 0; i < n; i++){
		int num;
		scanf("%d", &num);
		int temp = query(tree, 1, 1, MAX, 1, num - 1);  //num보다 작은 녀석들 중에 최대 길이를 가져온 후
		ans = max(ans, temp + 1);   //num까지의 길이를 합해본다.
		update(tree, 1, 1, MAX, num, temp + 1);
	}
	printf("%d", ans);
	return 0;
}
//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//int main(){
//	int n;
//	scanf("%d", &n);
//	vector<int> A(n);
//	vector<int> D;
//	for (int i = 0; i<n; i++){
//		scanf("%d", &A[i]);
//	}
//
//	for (int i = 0; i < n; i++){
//		auto it = lower_bound(D.begin(), D.end(), A[i]);
//		if (it == D.end()){
//			D.push_back(A[i]);
//		}
//		else{
//			*it = A[i];
//		}
//	}
//	printf("%d", D.size());
//	return 0;
//}