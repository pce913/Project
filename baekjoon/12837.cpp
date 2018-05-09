#include<stdio.h>
#include<vector>
using namespace std;

void update(vector<long long>& tree, int x,long long num){
	for (int i = x; i <= tree.size(); i += i&-i){
		tree[i] += num;
	}
}

long long query(vector<long long>& tree,int x){
	long long ans = 0;
	for (int i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int main(){
	int n,Q;
	scanf("%d %d",&n,&Q);
	vector<long long> tree(n + 1);
	for (int i = 0; i < Q; i++){
		int x, p;
		long long q;
		scanf("%d %d %lld",&x,&p,&q);
		if (x == 1){
			update(tree, p, q);
		}
		else{
			long long ans = query(tree, q) - query(tree, p - 1);
			printf("%lld\n",ans);
		}
	}
	return 0;
}