#include<stdio.h>
#include<vector>
using namespace std;

vector<int> ans;
vector<int> list;
int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++){
		list.push_back(i);
	}

	int cur = 0;
	for (int i = 1; i <= n; i++){
		int next = (cur + m - 1) % list.size();     //다음 위치
		ans.push_back(list[next]);  //정답 추가
		list.erase(list.begin()+next);
		cur = next;
	}

	printf("<%d",ans[0]);
	for (int i = 1; i < ans.size(); i++){
		printf(", %d",ans[i]);
	}
	printf(">");
	return 0;
}



//#include<stdio.h>
//#include<vector>
//#include<cmath>
//using namespace std;
//
//void init(vector<int>& tree, int node, int start, int end){
//	if (start == end){
//		tree[node] = 1;
//	}
//	else{
//		init(tree, 2 * node, start, (start + end) / 2);
//		init(tree, 2 * node + 1, (start + end) / 2 + 1, end);
//		tree[node] = tree[2 * node] + tree[2 * node + 1];
//	}
//}
//
//void update(vector<int>& tree, int node, int start, int end, int i, int diff){
//	if (i > end || i < start)
//		return;
//	tree[node] += diff;
//	if (start != end){
//		update(tree, 2 * node, start, (start + end) / 2, i, diff);
//		update(tree, 2 * node + 1, (start + end) / 2 + 1, end, i, diff);
//	}
//}
//
//int sum(vector<int>& tree, int node, int start, int end, int left, int right){
//	if (left > end || right < start){
//		return 0;
//	}
//	if (left <= start && right >= end){
//		return tree[node];
//	}
//	return sum(tree, 2 * node, start, (start + end) / 2, left, right) +
//		sum(tree, 2 * node + 1, (start + end) / 2 + 1, end, left, right);
//}
//
//int query(vector<int>& tree, int node, int start, int end, int k){
//	if (start == end){
//		return start;
//	}
//	if (k <= tree[2 * node]){
//		return query(tree, 2 * node, start, (start + end) / 2, k);
//	}
//	else{
//		return query(tree, 2 * node + 1, (start + end) / 2 + 1, end, k - tree[2 * node]);
//	}
//}
//
//int main(){
//	int n, k;
//	scanf("%d %d", &n, &k);
//	int h = (int)ceil(log2(n));
//	int tree_size = (1 << (h + 1));
//	vector<int> tree(tree_size);
//	vector<int> ans(n + 1);
//	init(tree, 1, 1, n);
//	int last = 0;
//	printf("<");
//	for (int i = n; i >= 1; i--){
//		int pre = 0;              // 현재 위치 앞에 몇개가 있니?
//		if (last != 0){
//			pre = sum(tree, 1, 1, n, 1, last - 1);
//		}
//		int index = (pre + k) % i;      // 조세퍼스 순열이므로 인덱스가 다시 앞으로 갈 경우를 대비해서 %i
//		if (index == 0){
//			index = i;
//		}
//		last = query(tree, 1, 1, n, index);
//		printf("%d", last);
//		if (i != 1){
//			printf(", ");
//		}
//		update(tree, 1, 1, n, last, -1);
//	}
//	printf(">");
//	return 0;
//}