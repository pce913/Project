#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

int a[205];
vector<int> v;
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	for (int i = 1; i <= n; i++){
		auto it = lower_bound(v.begin(), v.end(),a[i]);
		if (it == v.end()){
			v.push_back(a[i]);
		}
		else{
			*it = a[i];
		}
	}
	printf("%d",n-v.size());
	return 0;
}