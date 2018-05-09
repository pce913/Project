#include<stdio.h>
#include<algorithm>
using namespace std;
const int MOD = 1000;
const int MAXN = 20005;

int parent[MAXN], dist[MAXN];

int Find(int x){
	if (x == parent[x])
		return x;
	int temp = Find(parent[x]);
	dist[x] += dist[parent[x]];
	parent[x] = temp;
	return temp;
}

void solve(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		parent[i] = i;
		dist[i] = 0;
	}
	while (true){
		char qq;
		scanf(" %c",&qq);
		if (qq == 'E'){  //쿼리
			int x;
			scanf("%d",&x);
			Find(x);
			printf("%d\n",dist[x]);
		}
		else if (qq == 'I'){
			int a, b;
			scanf("%d %d",&a,&b);
			parent[a] = b;   //일단은 Find하지 말고 말단에 달아버린다.
			dist[a] = abs(a - b) % 1000;
		}
		else
			break;
	}
}

int main(){
	int T;
	scanf("%d", &T);
	for (int test = 0; test < T; test++){
		solve();
	}
	return 0;
}