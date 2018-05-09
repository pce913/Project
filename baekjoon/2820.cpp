#include<vector>
#include<iostream>
using namespace std;

const int MAXN = 500001;
vector<int> a[MAXN];
long long money[MAXN];
bool check[MAXN];
int preorder[MAXN];
int postorder[MAXN];
int pre = 0;


void dfs(int node){
	check[node] = true;
	preorder[node]=++pre;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (!check[next]){
			check[next] = true;
			dfs(next);
		}
	}
	postorder[node] = pre;          //트리라는 구조를 1차원적으로 관리하기 위해서 pre와 post를 사용함.
}

void update(vector<int>& tree, int x, int diff){
	for (int i = x; i < tree.size(); i += i&-i){   //마지막 비트를 더해서 천장 노드를 찾는다.
		tree[i] += diff;
	}
}

int query(vector<int>& tree,int x){
	int ans = 0;
	for (int i = x; i>0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	cin >> money[1];

	vector<int> tree(n + 5);   //펜윅트리 트리 사이즈는 몇이지?
	for (int i = 2; i <= n; i++){
		int x;
		cin >> money[i] >> x;
		a[x].push_back(i);
		a[i].push_back(x);
	}

	dfs(1);

	for (int i = 0; i < m; i++){
		char q;
		cin >> q;
		if (q == 'p'){
			int w, x;  //w의 모든 부하의 월급을 x만큼 증가시킨다.
			cin >> w >> x;
			update(tree, preorder[w],x );
			update(tree, postorder[w]+1, -x);     //postorder + 1    mark와 같은 역할이다.  바로 뒷쪽 인덱스에는 -x 해준다.
			// 본래 저장 되어 있던 상사 월급에서 -1 해준다. 왜냐하면 상사는 update 해주면 안되기 때문이다.
			money[w] -= x;     
		}
		else{
			int x;
			cin >> x;                  //쿼리가 중간중간에 들어오므로 1차원 누적합으로는 답을 구하기 어렵고
			cout << money[x] + query(tree, preorder[x])<<"\n";    //대신 펜윅 트리를 사용한다.
		}
	}

	return 0;
}