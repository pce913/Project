#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int INF = 1e9;
const int MAXC = 4587525;
int max_tree[4 * MAXC], min_tree[4 * MAXC], max_lazy[4 * MAXC], min_lazy[4 * MAXC];

void update_lazy(int tree[], int lazy[], int node, int start, int end){
	if (lazy[node] != 0){
		tree[node] += lazy[node];
	}
	if (start != end){
		lazy[2 * node] += lazy[node];
		lazy[2 * node + 1] += lazy[node];
	}
	lazy[node] = 0;
}

void update(int tree[], int lazy[], bool isMAX, int node, int start, int end, int i, int j, int value){
	update_lazy(tree, lazy, node, start, end);
	if (i > end || j < start){
		return;
	}
	if (start >= i && end <= j){
		tree[node] += value;
		if (start != end){
			lazy[2 * node] += value;
			lazy[2 * node + 1] += value;
		}
		return;
	}
	update(tree, lazy, isMAX, 2 * node, start, (start + end) / 2, i, j, value);
	update(tree, lazy, isMAX, 2 * node + 1, (start + end) / 2 + 1, end, i, j, value);
	if (isMAX)
		tree[node] = max(tree[2 * node], tree[2 * node + 1]);
	else
		tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

int query(int tree[], int lazy[], bool isMAX, int node, int start, int end, int i, int j){
	update_lazy(tree, lazy, node, start, end);
	if (i > end || j < start){
		return isMAX ? 0 : INF;
	}
	if (start >= i && end <= j){
		return tree[node];
	}
	int m1 = query(tree, lazy, isMAX, 2 * node, start, (start + end) / 2, i, j);
	int m2 = query(tree, lazy, isMAX, 2 * node + 1, (start + end) / 2 + 1, end, i, j);
	if (isMAX)
		return max(m1, m2);
	else
		return min(m1, m2);
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int c, n, o;    //c: ³ëµå °¹¼ö, n: ½ºÅÜ ¹üÀ§, o Äõ¸® °¹¼ö
	cin >> c >> n >> o;
	for (int qq = 0; qq < o; qq++){
		string s;
		cin >> s;
		int ans;
		if (s == "state"){
			int x;
			cin >> x;
			ans = query(max_tree, max_lazy, true, 1, 0, c - 1, x, x);
		}
		else if (s == "groupchange"){
			int a, b, s;
			cin >> a >> b >> s;
			if (s > 0){
				int temp = query(max_tree, max_lazy, true, 1, 0, c - 1, a, b);
				if (temp + s > n){
					update(max_tree, max_lazy, true, 1, 0, c - 1, a, b, n - temp);
					update(min_tree, min_lazy, false, 1, 0, c - 1, a, b, n - temp);
					ans = n - temp;
				}
				else{
					update(max_tree, max_lazy, true, 1, 0, c - 1, a, b, s);
					update(min_tree, min_lazy, false, 1, 0, c - 1, a, b, s);
					ans = s;
				}
			}
			else{
				int temp = query(min_tree, min_lazy, false, 1, 0, c - 1, a, b);
				if (temp + s < 0){
					update(max_tree, max_lazy, true, 1, 0, c - 1, a, b, -temp);
					update(min_tree, min_lazy, false, 1, 0, c - 1, a, b, -temp);
					ans = -temp;
				}
				else{
					update(max_tree, max_lazy, true, 1, 0, c - 1, a, b, s);
					update(min_tree, min_lazy, false, 1, 0, c - 1, a, b, s);
					ans = s;
				}
			}
		}
		else{
			int x, v;
			cin >> x >> v;
			int temp = query(max_tree, max_lazy, true, 1, 0, c - 1, x, x);
			if (temp + v > n){
				update(max_tree, max_lazy, true, 1, 0, c - 1, x, x, n - temp);
				update(min_tree, min_lazy, false, 1, 0, c - 1, x, x, n - temp);
				ans = n - temp;
			}
			else if (temp + v < 0){
				update(max_tree, max_lazy, true, 1, 0, c - 1, x, x, -temp);
				update(min_tree, min_lazy, false, 1, 0, c - 1, x, x, -temp);
				ans = -temp;
			}
			else{
				update(max_tree, max_lazy, true, 1, 0, c - 1, x, x, v);
				update(min_tree, min_lazy, false, 1, 0, c - 1, x, x, v);
				ans = v;
			}
		}
		cout << ans << '\n';
	}

	return 0;
}