#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> a;

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d",&x);
		a.push_back(x);
	}
	sort(a.begin(), a.end());
	int m;
	scanf("%d",&m);
	for (int q = 0; q < m; q++){
		int x;
		scanf("%d",&x);
		if (binary_search(a.begin(), a.end(), x)){
			printf("1\n");
		}
		else{
			printf("0\n");
		}
	}
	return 0;
}