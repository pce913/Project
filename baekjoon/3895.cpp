#include<stdio.h>

int tree[40005];

void init(int node,int start,int end){
	if (start == end){
		tree[node] = 1;
		return;
	}
	init(2 * node, start, (start + end) / 2);
	init(2 * node + 1, (start + end) / 2+1,end );
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int sum(int node,int start,int end,int i,int j){
	if (i > end || j < start)
		return 0;
	if (start >= i && end <= j)
		return tree[node];
	int a=sum(2 * node, start, (start + end) / 2, i, j);
	int b=sum(2 * node + 1, (start + end) / 2+1,end , i, j);
	return a + b;
}

int query(int node,int start,int end,int k){
	if (start == end){
		return start;
	}
	if (k <= tree[2*node]){   //= 다시보기
		return query(2 * node, start, (start + end) / 2, k);
	}
	else{
		return query(2 * node + 1, (start + end) / 2 + 1, end, k - tree[2*node]);
	}
}

void update(int node, int start, int end, int i, int value){
	if (i > end || i < start)
		return;
	if (start == end){
		tree[node] += value;
		return;
	}
	update(2 * node, start, (start + end) / 2, i, value);
	update(2 * node + 1, (start + end) / 2+1,end , i, value);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void solve(int n,int k,int m){
	init(1, 1, n);
	int last = m;
	update(1, 1, n, last, -1);
	for (int i = n-1; i >= 1; i--){
		int pre_cnt = 0;
		if (last >= 2){
			pre_cnt = sum(1, 1, n, 1, last - 1);
		}
		int idx = (pre_cnt + k - 1) % i + 1;   //1베이스
		int next = query(1, 1, n, idx);
		if (i == 1){
			printf("%d\n",next);
		}
		update(1, 1, n, next, -1);
		last = next;
	}
}

int main(){
	while (true){
		int n, k, m;
		scanf("%d %d %d", &n, &k, &m);
		if (n == 0 && k == 0 && m == 0)
			break;
		solve(n,k,m);
	}

	return 0;
}