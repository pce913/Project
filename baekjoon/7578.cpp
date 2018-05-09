#include<iostream>
using namespace std;

int a[500005], pos[1000005];
int tree[500005];
int n;
void update(int x,int value){
	for (int i = x; i <= n; i += i&-i)
		tree[i] += value;
}

int query(int x){
	int ans = 0;
	for (int i = x; i > 0; i -= i&-i)
		ans += tree[i];
	return ans;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++){
		int x;
		cin >> x;
		pos[x] = i;
	}

	long long ans = 0;
	for (int i = 1; i <= n; i++){
		ans += i-1 - query(pos[a[i]]);
		update(pos[a[i]], 1);
	}
	cout << ans;
	return 0;
}