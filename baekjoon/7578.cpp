#include<stdio.h>
#include<vector>
#include<map>
using namespace std;

void update(vector<int>& tree,int x,int diff){
	for (int i = x; i < tree.size(); i += i&-i){
		tree[i] += diff;
	}
}

long long sum(vector<int>& tree,int x){
	long long ans = 0;
	for (int i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

long long sum(vector<int>& tree,int left,int right){
	if (left > right)
		return 0;
	return sum(tree, right) - sum(tree, left-1);
}


int main(){
	int n;
	scanf("%d",&n);
	vector<int> a(n);
	vector<int> tree(n + 1);
	for (int i = 0; i < n; i++){
		scanf("%d",&a[i]);
	}
	map<int, int> position;
	for (int i = 1; i <= n; i++){
		int num;
		scanf("%d",&num);
		position[num] = i;
	}
	long long ans = 0;
	for (int i = 0; i < n; i++){
		int p=position[a[i]];
		ans += sum(tree,p+1,n);
		update(tree,p,1);
	}
	printf("%lld",ans);
	return 0;
}