#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

vector< pair<int, int> > a;
//중앙값을 찾아주면 된다.
int main(){
	int n;
	long long sum = 0, s = 0;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a.push_back({ x, y });
		sum += y;
	}
	sort(a.begin(), a.end());
	for (int i = 0; i < a.size(); i++){
		s += a[i].second;
		if (s >= sum / 2){
			printf("%d",a[i].first);
			break;
		}
	}
	return 0;
}