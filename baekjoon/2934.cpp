#include<iostream>
using namespace std;

int tree[100005];
int n;
void update(int x,int value){
	for (int i = x; i <= 100000; i += i&-i){
		tree[i] += value;
	}
}

int query(int x){
	int ans = 0;
	for (int i = x; i>0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++){
		int l, r;
		cin >> l >> r;
		update(l + 1, 1);
		update(r - 1 + 1, -1);
		int a = query(l);
		int b = query(r);
		cout << a + b << "\n";
		if (a > 0){
			update(l, -a);
			update(l + 1, a);
		}
		if (b > 0){
			update(r, -b);
			update(r + 1, b);
		}
	}
	return 0;
}