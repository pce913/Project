#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> tree;
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d",&x);
		tree.push_back(x);
	}
	sort(tree.begin(), tree.end());
	reverse(tree.begin(), tree.end());
	for (int i = 0; i < tree.size(); i++){
		tree[i] += i + 1;
	}
	int ans = 0;
	for (int i = 0; i < tree.size(); i++){
		ans = max(ans, tree[i] + 1);
	}
	printf("%d",ans);
	return 0;
}