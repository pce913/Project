#include<stdio.h>
#include<algorithm>
using namespace std;

int n, a[100005],s[100005],ans[100005],tree[400005];
void init(int node,int start,int end){
	if (start == end){
		tree[node] = 1;
		return;
	}
	init(2 * node, start, (start + end) / 2);
	init(2 * node + 1, (start + end) / 2+1,end );
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node,int start,int end,int i,int value){
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

int query(int node,int start,int end,int i){
	if (start == end){
		return start;
	}
	if (i <= tree[2 * node]){
		return query(2 * node, start, (start + end) / 2, i);
	}
	else{
		return query(2 * node + 1, (start + end) / 2 + 1, end, i - tree[2 * node]);
	}
}

int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	for (int i = 1; i <= n; i++){
		scanf("%d",&s[i]);
	}
	sort(a + 1, a + 1 + n);
	init(1, 1, n);
	for (int i = n; i >= 1; i--){
		int idx = query(1, 1, n, s[i] + 1);
		ans[i] = a[idx];
		update(1, 1, n, idx, -1);
	}
	for (int i = 1; i <= n; i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}