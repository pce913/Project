#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int a[1005], b[1005];
vector<int> sumb;
int main(){
	int t;
	scanf("%d",&t);
	int n, m;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++){
		scanf("%d",&b[i]);
	}
	for (int i = 1; i <= m; i++){
		int sum = 0;
		for (int j = i; j <= m; j++){
			sum += b[j];
			sumb.push_back(sum);
		}
	}
	sort(sumb.begin(), sumb.end());

	long long ans = 0;
	for (int i = 1; i <= n; i++){
		int sum = 0;
		for (int j = i; j <= n; j++){
			sum += a[j];
			int goal = t - sum;
			auto p = equal_range(sumb.begin(), sumb.end(), goal);
			ans += (p.second-p.first);
		}
	}
	printf("%lld",ans);
	return 0;
}