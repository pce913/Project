#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> a;
int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		a.push_back(x);
	}
	sort(a.begin(), a.end());
	for (int i = 0; i < a.size(); i++){
		printf("%d\n", a[i]);
	}
	return 0;
}