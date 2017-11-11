#include<stdio.h>
#include<algorithm>
using namespace std;
int a[100005], tree[400005];

void init(int node,int start,int end){
	if (start == end){
		tree[node] = start;
		return;
	}
	init(2 * node, start, (start + end) / 2);
	init(2 * node + 1, (start + end) / 2 + 1,end );
	if (a[tree[2 * node]] <= a[tree[2 * node + 1]]){
		tree[node] = tree[2 * node];
	}
	else{
		tree[node] = tree[2 * node + 1];
	}
}

void update(int node,int start,int end,int i,int value){
	if (i > end || i < start)
		return;
	if (start == end){
		a[start] = value;
		return;
	}
	update(2 * node, start, (start + end) / 2, i, value);
	update(2 * node + 1, (start + end) / 2 + 1,end , i, value);
	if (a[tree[2 * node]] <= a[tree[2 * node + 1]]){
		tree[node] = tree[2 * node];
	}
	else{
		tree[node] = tree[2 * node + 1];
	}
}

int query(int node,int start,int end,int i,int j){
	if (i > end || j < start){
		return -1;
	}
	if (start >= i && end <= j){
		return tree[node];
	}
	int a1 = query(2 * node, start, (start + end) / 2, i, j);
	int a2 = query(2 * node + 1, (start + end) / 2+1,end , i, j);
	if (a1 == -1){
		return a2;
	}
	else if (a2 == -1){
		return a1;
	}
	else{
		return a[a1] <= a[a2] ? a1 : a2;
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	init(1,1,n);
	int m;
	scanf("%d",&m);
	for (int qq = 0; qq < m; qq++){
		int c, w, v;
		scanf("%d %d %d",&c,&w,&v);
		if (c == 1){
			update(1, 1, n, w, v);
		}
		else{
			printf("%d\n", query(1, 1, n, w, v));
		}
	}
	return 0;
}