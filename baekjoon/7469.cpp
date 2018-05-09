#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int a[100005];
vector<int> tree[400005];

void init(int node, int start, int end){
	if (start == end){
		tree[node].push_back(a[start]);
		return;
	}
	init(2 * node, start, (start + end) / 2);
	init(2 * node + 1, (start + end) / 2 + 1, end);
	tree[node].resize(end - start + 1);
	merge(tree[2 * node].begin(), tree[2 * node].end(), tree[2 * node + 1].begin(), tree[2 * node + 1].end(), tree[node].begin());
}

int query(int node, int start, int end, int i, int j, int value){    //쿼리당 O(logn+logn)
	if (i > end || j < start){
		return 0;
	}
	if (start >= i && end <= j){ //현재 보는 범위에서 value보다 작은 값이 몇개 있는지 리턴
		return upper_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin();
	}
	int s1 = query(2 * node, start, (start + end) / 2, i, j, value);
	int s2 = query(2 * node + 1, (start + end) / 2 + 1, end, i, j, value);
	return s1 + s2;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	init(1, 1, n);
	for (int qq = 0; qq < m; qq++){
		int i, j, k;
		scanf("%d %d %d", &i, &j, &k);
		int left = -1e9;
		int right = 1e9;
		int ans;
		while (left <= right){
			int mid = (left + right) >> 1;
			if (k <= query(1, 1, n, i, j, mid)){
				ans = mid;
				right = mid - 1;
			}
			else{
				left = mid + 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}