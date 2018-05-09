#include<stdio.h>
#include<vector>
#include<cmath>
using namespace std;

const int MAX = 1000000;

void update(vector<int>& tree,int node,int start,int end,int i,int diff){
	if (i<start || i >end){
		return;
	}
	tree[node] += diff;
	if (start != end){
		update(tree, node * 2, start, (start + end) / 2, i, diff);
		update(tree, node * 2 + 1, (start + end) / 2 + 1, end, i, diff);
	}
}

int query(vector<int>& tree, int node, int start, int end, int k){                         // 몇번째 사탕인지(사탕이 무슨 맛인지)
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

int main(){
	int h = (int)ceil(log2(MAX));
	int tree_size = (1 << (h + 1));
	vector<int> tree(tree_size);                    //tree[i] : i 번째 사탕이 몇개가 들어 있는지.

	int n;
	scanf("%d",&n);
	for (int T = 0; T < n; T++){
		int cmd;
		scanf("%d",&cmd);
		if (cmd == 2){
			int box, diff;
			scanf("%d %d",&box,&diff);
			update(tree,1,1,MAX,box,diff);
		}
		else if (cmd == 1){
			int k;
			scanf("%d",&k);
			int box = query(tree,1,1,MAX,k);
			printf("%d\n",box);
			update(tree,1,1,MAX,box,-1);
		}
	}
	return 0;
}