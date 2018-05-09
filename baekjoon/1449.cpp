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
using namespace std;
int a[1005];
bool cover[4005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int N, L;
	cin >> N >> L;
	for (int i = 1; i <= N; i++){
		cin >> a[i];
	}
	sort(a + 1, a + 1 + N);
	int ans = 0;
	for (int i = 1; i <= N; i++){
		if (!cover[a[i]]){
			ans++;
			for (int j = a[i]; j <= a[i] + L - 1; j++){
				cover[j] = true;
			}
		}
	}
	cout << ans;
	return 0;
}