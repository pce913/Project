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

int a[1005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			int x;
			cin >> x;
			a[i] |= x;     //(a[1]&a[2]) | (a[1]&a[3]) ...
		}  //(a[1]&a[2]) 일때를 보자. 이것은 a[1]과 a[2]가 서로 겹치는 비트를 가지고 있는것이다.
	}  //마찬가지로 (a[1]&a[3]) 도 a[1]과 a[3]가 서로 겹치는 비트를 가지고 있는 것이다. 즉, 서로 겹치는 부분을 일부분씩 가지고 있으면 된다.
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	return 0;
}