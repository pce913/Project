#include<stdio.h>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int INF = 1e9;
int a[1000005],next_pos[1000005];   //next[i]: i번째에 있는 값이 다음 어느 위치에 등장하는지 저장.
unordered_map<int, int> prv;    //prev[i]: 숫자 i가 이전에 등장한 위치.
vector<int> tree[4000005];

void init(int node,int start,int end){
	if (start == end){
		tree[node].push_back(next_pos[start]);
		return;
	}
	init(2 * node, start, (start + end) / 2);
	init(2 * node + 1, (start + end) / 2+1,end );
	tree[node].resize(end - start + 1);   //stl merge를 써서 정렬된 상태를 유지 시킨다.
	merge(tree[2 * node].begin(), tree[2 * node].end(), tree[2 * node + 1].begin(), tree[2 * node + 1].end(),tree[node].begin());
}

int query(int node,int start,int end,int i,int j){
	if (i > end || j < start)
		return 0;
	if (start >= i && end <= j){   //j보다 큰 next_pos값이 몇개가 있는지를 리턴한다. 이렇게 하면 구간에 몇 종류의 숫자가 있는지를 알 수 있다.
		return (int)tree[node].size() - (upper_bound(tree[node].begin(), tree[node].end(), j) - tree[node].begin());
	}
	int s1 = query(2 * node, start, (start + end) / 2, i, j);
	int s2 = query(2 * node + 1, (start + end) / 2 + 1, end, i, j);
	return s1 + s2;
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		next_pos[i] = INF;
	}
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		if (prv[a[i]] != 0){
			next_pos[prv[a[i]]] = i;
		}
		prv[a[i]] = i;
	}
	init(1, 1, n);
	int q;
	scanf("%d",&q);
	for (int qq = 0; qq < q; qq++){
		int x, y;
		scanf("%d %d",&x,&y);
		printf("%d\n", query(1, 1, n, x, y));
	}
	return 0;
}