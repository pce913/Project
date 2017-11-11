#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

int tree[500005];
vector<int> a;
vector<int> data;
int n;
void update(int x, int value){
	for (int i = x; i <= n; i += i&-i){
		tree[i] += value;
	}
}

int query(int x){    //앞에 몇명이 있느냐를 본다.
	int ans = 0;
	for (int i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		a.push_back(x);
		data.push_back(x);
	}
	sort(a.begin(), a.end());

	for (int i = 0; i < a.size(); i++){
		auto it = lower_bound(a.begin(), a.end(), data[i]);
		int idx = it - a.begin() + 1;
		printf("%d\n", query(data.size()) - query(idx) + 1);
		update(idx, 1);
	}

	return 0;
}