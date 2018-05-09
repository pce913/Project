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

long long a[10005];
long long k, n;
long long go(long long mid){
	long long cnt = 0;
	for (long long i = 1; i <= k; i++){
		cnt += a[i] / mid;
	}
	return cnt;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> k >> n;
	long long left = 1, right=0;
	for (long long i = 1; i <= k; i++){
		cin >> a[i];
		right = max(right, a[i]);
	}
	long long ans = 0;
	while (left <= right){
		long long mid = (left + right) >> 1LL;
		if (go(mid) >= n){
			ans = mid;
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}
	cout << ans;
	return 0;
}