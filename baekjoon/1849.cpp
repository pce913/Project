#include<stdio.h>
#include<vector>
#include<cmath>
using namespace std;

void update(vector<int>& tree,int node,int start,int end,int i,int diff){
	if (i > end || i < start){
		return;
	}
	tree[node] += diff;
	if (start != end){
		update(tree, 2 * node, start, (start + end) / 2, i, diff);
		update(tree, 2 * node + 1, (start + end) / 2+1,end , i, diff);
	}
}

int query(vector<int>& tree,int node,int start,int end,int k){		//몇번째가 어떤 값인지를 구하는 트리
	if (start == end){
		return start;
	}
	else{
		if (k <= tree[2 * node]){
			return query(tree,2*node,start,(start+end)/2,k);
		}
		else{
			return query(tree, 2 * node+1, (start + end) / 2+1, end, k-tree[2*node]);
		}
	}
}

void init(vector<int>& tree,int node,int start,int end){
	if (start == end){
		tree[node] = 1;
	}
	else{
		init(tree, 2 * node, start, (start + end) / 2);
		init(tree, 2 * node + 1, (start + end) / 2+1, end);
		tree[node] = tree[2 * node] + tree[2 * node + 1];
	}
}

int main(){
	int n;
	scanf("%d",&n);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<int> tree(tree_size);

	init(tree, 1, 1, n);
	vector<int> ans(n + 1);
	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		int k = x + 1;
		int position=query(tree, 1, 1, n, k);
		ans[position]=i;
		update(tree, 1, 1, n, position, -1);
	}
	for (int i = 1; i <= n; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}