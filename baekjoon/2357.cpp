#include<stdio.h>
#include<algorithm>
using namespace std;
int a[100001];
pair<int, int> tree[300001];

pair<int, int> query(int node, int start, int end, int i, int j){
	if (i > end || j < start)
		return{ -1, -1 };
	if (i <= start && j >= end)
		return tree[node];

	auto m1 = query(2 * node, start, (start + end) / 2, i, j);
	auto m2 = query(2 * node + 1, (start + end) / 2 + 1, end, i, j);
	if (m1.first == -1 && m1.second == -1)
		return m2;
	else if (m2.first == -1 && m2.second == -1)
		return m1;
	else
		return{ min(m1.first, m2.first), max(m1.second, m2.second) };
}

void init(int node, int start, int end){
	if (start == end)
		tree[node].first = tree[node].second = a[start];
	else{
		init(2 * node, start, (start + end) / 2);
		init(2 * node + 1, (start + end) / 2 + 1, end);
		tree[node].first = min(tree[2 * node].first, tree[2 * node + 1].first);
		tree[node].second = max(tree[2 * node].second, tree[2 * node + 1].second);
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	init(1, 1, n);
	for (int test = 0; test < m; test++){
		int a, b;
		scanf("%d %d", &a, &b);
		auto ans = query(1, 1, n, a, b);
		printf("%d %d\n", ans.first, ans.second);
	}
	return 0;
}