#include<stdio.h>
#include<vector>
using namespace std;

vector<int> a;

int D[45];

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	D[0] = 1;
	D[1] = 1;
	for (int i = 2; i <= n; i++){
		D[i] = D[i - 1] + D[i - 2];
	}

	for (int i = 0; i < m; i++){
		int x;
		scanf("%d",&x);
		a.push_back(x);
	}

	int ans = 1;
	int before = 1;
	for (int i = 0; i < a.size(); i++){
		int cur = a[i];
		int len = cur-before;
		ans *= D[len];
		before = cur+1;
	}
	if (before <= n){
		int len = n - before + 1;
		ans *= D[len];
	}
	printf("%d",ans);
	return 0;
}