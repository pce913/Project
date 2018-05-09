#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

void update(vector<long long>& tree, long long x, long long num){
	for (long long i = x; i < tree.size(); i += i&-i){
		tree[i] += num;
	}
}

long long sum(vector<long long>& tree,long long x){
	long long ans = 0;
	for (long long i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int main(){
	long long n, q;
	scanf("%lld %lld",&n,&q);
	
	vector<long long> tree(n + 1);
	vector<long long> input(n + 1);
	for (long long i = 1; i <= n; i++){
		long long w;
		scanf("%lld",&w);
		input[i] = w;
		update(tree, i, w);
	}
	for (long long i = 0; i < q; i++){
		long long x, y,a,b;
		scanf("%lld %lld %lld %lld",&x,&y,&a,&b);
		if (x>y)
			swap(x, y);
		printf("%lld\n", sum(tree, y) - sum(tree, x - 1));
		long long temp = b - input[a];
		input[a] = b;
		update(tree, a, temp);
	}

	return 0;
}