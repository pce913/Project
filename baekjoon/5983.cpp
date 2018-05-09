#include<stdio.h>
#include<vector>
#include<cstring>
using namespace std;

vector<int> lang[30001];
vector<int> ans;
int parent[10001];

int Find(int x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

void Union(int x,int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
	}
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);

	int con;
	for (int i = 1; i <= n; i++){
		parent[i] = i;
		int x;
		scanf("%d", &x);
		for (int j = 0; j < x; j++){
			int v;
			scanf("%d", &v);
			lang[v].push_back(i);
			if (i == 1 && j == 0){
				con = v;
			}
		}
	}

	for (int i = 1; i <= m; i++){
		if (lang[i].size() == 0)
			continue;

		int u = lang[i][0];   //해당 언어를 구사하는 소가 아무도 없을 경우 처리해 줘야 함.
		for (int j = 0; j < lang[i].size(); j++){
			int v = lang[i][j];
			Union(u, v);
		}
	}

	for (int i = 1; i <= n; i++){
		if (Find(i) == i && Find(1) != Find(i)){
			ans.push_back(i);
		}
	}

	printf("%d\n",ans.size());
	for (int i = 0; i < ans.size(); i++){
		printf("%d %d\n", con, ans[i]);
	}

	return 0;
}
//#include<stdio.h>
//#include<vector>
//#include<cstring>
//using namespace std;
//
//#define convert(i) i + 10000
//#define revert(i) i - 10000
//
//vector<int> a[40001];
//vector<int> ans;
//bool check[40001];
//
//void dfs(int node){
//	check[node] = true;
//	for (int i = 0; i < a[node].size(); i++){
//		int next = a[node][i];
//		if (!check[next]){
//			dfs(next);
//		}
//	}
//}
//
//int main(){
//	int n, m;
//	scanf("%d %d",&n,&m);
//	for (int i = 1; i <= n; i++){
//		int x;
//		scanf("%d",&x);
//		for (int j = 0; j < x; j++){
//			int v;
//			scanf("%d",&v);
//			a[i].push_back(convert(v));
//			a[convert(v)].push_back(i);
//		}
//	}
//
//	int cnt = 1;
//	int con = revert(a[1][0]);
//	dfs(1);
//	for (int i = 2; i <= n; i++){
//		if (!check[i]){
//			dfs(i);
//			cnt++;
//			ans.push_back(i);
//		}
//	}
//	printf("%d\n",cnt-1);  //connected component 갯수 - 1이 정답이다.
//	for (int i = 0; i < ans.size(); i++){
//		printf("%d %d\n",con , ans[i]);   //어떤 컴포넌트에 있는 언어를 다른 컴포넌트와 연결시키면 된다.
//	}
//	
//	return 0;
//}