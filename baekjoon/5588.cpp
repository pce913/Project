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

map<pair<int,int>, int> M;
int ix[2005], iy[2005];
int dx[2005], dy[2005];
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int m;
	cin >> m;
	int mx, my;
	cin >> mx >> my;
	for (int i = 1; i < m; i++){
		int x, y;
		cin >> x >> y;
		dx[i] = x - mx, dy[i] = y - my;
	}

	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		M[{x, y}] = 1;
		ix[i] = x, iy[i] = y;
	}

	int ax = -1, ay = -1;
	for (int i = 0; i < n; i++){
		bool isOk = true;
		for (int j = 0; j < m; j++){
			int x = ix[i] + dx[j], y = iy[i] + dy[j];
			if (M.count({x,y})==0){
				isOk = false;
				break;
			}
		}
		if (isOk){
			ax = ix[i] - mx, ay = iy[i] - my;
			break;
		}
	}
	cout << ax << ' ' << ay;
	return 0;
}