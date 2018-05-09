//#include<stdio.h>
//#include<vector>
//using namespace std;
//#define MAX(x,y) ((x) > (y) ? (x) : (y)) 
//
//int start;
//int ending;
//int maxi=0;
//vector< pair<int,int> > a[100001];
//bool check[100001];
//int limit =1000000000;
//
//void dfs(int node,int forelimit){
//	check[node] = true;
//	if (node == ending){
//		maxi = MAX(maxi,forelimit);
//		check[node] = false;
//		return;
//	}
//	for (int i = 0; i < a[node].size(); i++){
//		int next = a[node][i].first;
//		if (check[next] == false){
//			limit = (forelimit > a[node][i].second) ? a[node][i].second : forelimit;
//			if (maxi < limit)
//				dfs(next, limit);
//		}
//	}
//	check[node] = false;
//}
//
//int main(){
//	freopen("input.txt", "r", stdin);
//	int N, M;
//	scanf("%d %d",&N,&M);
//	
//	for (int i = 1; i <= M; i++){
//		int t1, t2, t3;
//		scanf("%d %d %d",&t1,&t2,&t3);
//		a[t1].push_back(make_pair(t2,t3));
//		a[t2].push_back(make_pair(t1,t3));
//	}
//	scanf("%d %d",&start,&ending);
//	dfs(start,1000000000);
//	printf("%d",maxi);
//	return 0;
//}


#include<stdio.h>
#include<vector>
#include<cstring>
using namespace std;

int start;
int ending;
vector< pair<int, int> > a[100001];
bool check[100001];
int limit;
bool dfs(int node){
	if (check[node])
		return false;

	check[node] = true;
	if (node == ending){
		return true;
	}
	for (auto& p : a[node]){
		int next = p.first;
		if (p.second >= limit){
			if (dfs(next))
				return true;
		}
	}
	return false;
}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= M; i++){
		int t1, t2, t3;
		scanf("%d %d %d", &t1, &t2, &t3);
		a[t1].push_back(make_pair(t2, t3));
		a[t2].push_back(make_pair(t1, t3));
	}
	scanf("%d %d", &start, &ending);

	int l=1, r=1000000000;
	int ans = 0;
	while (l <= r){
		memset(check,false,sizeof(check));
		int m = (l + r) / 2;
		limit = m;
		if (dfs(start)){
			ans = m;
			l = m + 1;
		}
		else
			r = m - 1;
	}
	printf("%d", ans);
	return 0;
}

