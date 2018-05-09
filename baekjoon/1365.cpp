#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> a;

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		auto it = lower_bound(a.begin(), a.end(), x);
		if (it == a.end()){
			a.push_back(x);
		}
		else{
			*it = x;
		}
	}
	printf("%d\n", n - a.size());
	return 0;
}