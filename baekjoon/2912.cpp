//#include<stdio.h>
//#include<vector>
//#include<cmath>
//#include<algorithm>
//using namespace std;
//
//struct Info{
//	int candidate, count;
//};
//
//
//int a[300005];
//vector<int> color[300005];
//
//Info init(vector<Info>& tree,int node,int start,int end){
//	if (start == end){
//		tree[node] = { a[start], 1 };
//		return tree[node];
//	}
//	auto L = init(tree, 2 * node, start, (start + end) / 2);
//	auto R = init(tree, 2 * node + 1, (start + end) / 2 + 1, end);
//
//	//Kill the remaining pairs among L.count + R.count numbers that are left.
//	Info S;        
//	if (L.candidate == R.candidate){   
//		S.candidate = L.candidate;
//		S.count = L.count + R.count;
//	}
//	else if (L.count > R.count){
//		S.candidate = L.candidate;
//		S.count = L.count - R.count;
//	}
//	else{
//		S.candidate = R.candidate;
//		S.count = R.count - L.count;
//	}
//	tree[node] = S;
//	return tree[node];
//}
//
//Info query(vector<Info>& tree,int node,int start,int end,int left,int right){
//	if (start > right || end < left){
//		return{ -1, 0 };     //이럴때 count를 0으로 해줘야 한다. 그래야 합칠때 문제가 생기지 않음.
//	}
//	if (start >= left && end <= right){
//		return tree[node];
//	}
//	auto L = query(tree, 2 * node, start, (start + end) / 2, left, right);
//	auto R = query(tree, 2 * node + 1, (start + end) / 2 + 1, end, left, right);
//	Info S;
//	 //Kill 하는 과정. 일단 정답이 될 수 있는 후보를 찾는 과정이다. 이 과정을 통해서는
//	 //말 그대로 후보를 찾을 뿐 실제 답을 찾는 과정이 아니다. 
//	 //후보란 것은 그 구간사이에 가장 갯수가 많은 녀석을 가져오는 것이다.
//	 //여기서 L.count - R.count; 를 하는 부분이 Kill을 하는 과정이다.
//	 // 즉, 현재 L과 R에서 선택한 어느 구간의 가장 많이 등장한 녀석 L.candidate와 R.candidate를
//	 //각각 한 pair씩 없애는 것이다.
//	 //이것은 빼기로 구현 할 수 있으며 최종적으로 count가 음수가 아닌 녀석이 실제 후보가 된다.
//	if (L.candidate == R.candidate){
//		S.candidate = L.candidate;
//		S.count = L.count + R.count;
//	}
//	else if (L.count > R.count){
//		S.candidate = L.candidate;
//		S.count = L.count - R.count;
//	}
//	else{
//		S.candidate = R.candidate;
//		S.count = R.count - L.count;
//	}
//	return S;
//}
//
//int get_count(int x,int left,int right){    //요구하는 구간 사이에 실제로 몇개의 같은 색이 있는지를 본다.
//	return upper_bound(color[x].begin(), color[x].end(), right) 
//		- lower_bound(color[x].begin(),color[x].end(),left);
//}
//
//int main(){
//	int n, c;
//	scanf("%d %d",&n,&c);
//	for (int i = 1; i <= n; i++){
//		scanf("%d",&a[i]);
//		color[a[i]].push_back(i);
//	}
//	int h = ceil(log2(n));
//	int tree_size = (1 << (h + 1));
//	vector<Info> tree(tree_size);
//	init(tree, 1, 1, n);
//
//	int m;
//	scanf("%d",&m);
//	for (int qq = 0; qq < m; qq++){
//		int x, y;
//		scanf("%d %d",&x,&y);
//		auto p = query(tree, 1, 1, n, x, y);
//		if (p.count > 0 && 2 * get_count(p.candidate, x, y) > y - x + 1){    //p.count > 0 : 후보가 되는 녀석이 있니?
//			printf("yes %d\n",p.candidate);
//		}
//		else{
//			printf("no\n");
//		}
//	}
//	return 0;
//}
//
//#include <iostream>
//#include <map>
//#include <cstring>
//#include <set>
//#include <vector>
//using namespace std;
//const int MAXN = 300002;
//const int lim = 2000;
//map<int, int> tree[MAXN];
//int n, c, cnt[10001], q, v, l, r, tot[10001], arr[MAXN];
//vector<int> data[MAXN];
//set<int> st;
//void update(int n, int pos, int add){
//	for (int i = pos; i<MAXN; i += i&-i){
//		tree[i][n] += add;
//	}
//}
//int query(int n, int pos){
//	int sum = 0;
//	for (int i = pos; i>0; i -= i&-i){
//		if (tree[i].find(n) != tree[i].end())
//			sum += tree[i][n];
//	}
//	return sum;
//}
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin >> n >> c;
//	for (int i = 1; i <= n; i++){
//		cin >> arr[i];
//		update(arr[i], i, 1);
//		tot[arr[i]]++;
//	}
//	for (int i = 1; i <= c; i++){
//		data[tot[i]].push_back(i);
//		st.insert(tot[i]);
//	}
//	cin >> q;
//	for (int i = 1; i <= q; i++){
//		cin >> l >> r;
//		int len = r - l + 1;
//		int cap = len / 2 + 1;
//		int color = -1;
//		if (len <= 5000){
//			memset(cnt, 0, sizeof(cnt));
//			for (int j = l; j <= r; j++){
//				cnt[arr[j]]++;
//				if (cnt[arr[j]] >= cap){
//					color = arr[j]; break;
//				}
//			}
//		}
//		else{
//			auto it = st.lower_bound(cap);
//			for (; it != st.end() && color == -1; it++){
//				for (int j = 0; j<data[*it].size(); j++){
//					int clr = data[*it][j];
//					if (query(clr, r) - query(clr, l - 1) >= cap){
//						color = clr; break;
//					}
//				}
//			}
//		}
//		if (color == -1)cout << "no\n";
//		else cout << "yes " << color << "\n";
//	}
//	return 0;
//}