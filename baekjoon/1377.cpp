#include<cstdio>
#include<algorithm>
using namespace std;

pair<int, int> M[500001];
int main(){
	int N;
	int maxi=0;
	int t;
	scanf("%d",&N);
	
	for (int i = 1; i <= N; i++){
		scanf("%d", &M[i].first);
		M[i].second = i;
	}
	sort(M+1, M + N + 1);

	for (int i = 1; i <= N; i++){
		t = M[i].second - i;
		if (maxi < t)
			maxi = t;
	}
	printf("%d",maxi+1);
	return 0;
}