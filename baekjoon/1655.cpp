#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<tuple>
#include<iomanip>
#include<algorithm>
#include<functional>
#include<cmath>
#include<unordered_set>
#include<unordered_map>
using namespace std;
int tree[400005];
int a[100005], temp[100005];
map<int, int> recover;
vector<int> press;
void update(int node, int start, int end, int i, int value){
	if (i > end || i < start)
		return;
	if (start == end){
		tree[node] += value;
		return;
	}
	update(2 * node, start, (start + end) / 2, i, value);
	update(2 * node + 1, (start + end) / 2 + 1, end, i, value);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int start, int end, int k){
	if (start == end){
		return start;
	}
	if (k <= tree[2 * node]){    // go left
		return query(2 * node, start, (start + end) / 2, k);
	}
	else{   //go right   아하
		return query(2 * node + 1, (start + end) / 2 + 1, end, k - tree[2 * node]);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		temp[i] = a[i];
		press.push_back(a[i]);
	}
	sort(press.begin(), press.end());
	press.erase(unique(press.begin(), press.end()), press.end());
	for (int i = 1; i <= n; i++){
		a[i] = lower_bound(press.begin(), press.end(), a[i]) - press.begin() + 1;  //1베이스
		recover[a[i]] = temp[i];  //압축한것 복원.
	}
	for (int i = 1; i <= n; i++){
		update(1, 1, n, a[i], 1);
		if (i % 2 == 1){
			int value = query(1, 1, n, i / 2 + 1);     //1베이스로 리턴한다.
			cout << recover[value] << "\n";
		}
		else{
			int value1 = query(1, 1, n, i / 2);
			int value2 = query(1, 1, n, i / 2 + 1);
			cout << min(recover[value1], recover[value2]) << "\n";
		}
	}
	return 0;
}