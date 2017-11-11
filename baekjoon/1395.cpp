#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;

void update_lazy(vector<int>& tree, vector<int>& lazy, int node, int start, int end){
	if (lazy[node] != 0){                 // lazy에 값이 들어있다면 update후 첫번째 방문이 아니란 뜻이므로 이때 lazy를 update 시켜준다.
		if (lazy[node] % 2 == 1){       // lazy값이 홀수일 경우에만 업데이트. 스위치 반전이라는 개념이므로 짝수일때는 업데이트 하지 않는다.
			tree[node] = (end - start + 1) - tree[node];       // 0 또는 합으로 만든다.
		}
	}
	if (start != end){        //leaf 노드가 아니면 lazy를 물려준다. 기존에 lazy값이 있을 수 있으므로 += 으로 처리
		lazy[2 * node] += lazy[node];
		lazy[2 * node + 1] += lazy[node];
	}
	lazy[node] = 0;         //lazy값을 이용해서 현재 node를 update 시켜줬으므로 lazy값을 0으로 바꿔준다.
}

void update_range(vector<int>& tree, vector<int>& lazy, int node, int start, int end, int left, int right, long long diff){
	update_lazy(tree, lazy, node, start, end);                   //lazy를 먼저 update 시켜준다.
	if (left > end || right < start)
		return;
	if (left <= start && right >= end){                //범위내로 완전히 포함되면
		if (diff % 2 == 1){                              // 차이가 홀수일때
			tree[node] = (end - start + 1) - tree[node];     //노드를 update해준다.  0 또는 합으로 만든다.
		}
		if (start != end){                       //현재 노드가 말단 노드가 아니라면
			lazy[2 * node] += diff;              //자식에게 lazy값을 물려준다.
			lazy[2 * node + 1] += diff;
		}
		return;
	}
	update_range(tree, lazy, 2 * node, start, (start + end) / 2, left, right, diff);
	update_range(tree, lazy, 2 * node + 1, (start + end) / 2 + 1, end, left, right, diff);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int sum(vector<int>& tree, vector<int>& lazy, int node, int start, int end, int left, int right){
	update_lazy(tree, lazy, node, start, end);
	if (left > end || right < start){
		return 0;
	}
	if (left <= start && right >= end){
		return tree[node];
	}
	return sum(tree, lazy, node * 2, start, (start + end) / 2, left, right) + sum(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int> A(n);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<int> tree(tree_size);
	vector<int> lazy(tree_size);

	for (int test = 0; test < m; test++){
		int t1;
		scanf("%d", &t1);
		if (t1 == 0){
			int start, end;
			scanf("%d %d", &start, &end);
			update_range(tree, lazy, 1, 0, n - 1, start - 1, end - 1, 1);
		}
		else if (t1 == 1){
			int start, end;
			scanf("%d %d", &start, &end);
			printf("%d\n", sum(tree, lazy, 1, 0, n - 1, start - 1, end - 1));
		}
	}
	return 0;
}