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

//long long
vector<long long> a_par, b_par;
long long sum[1005];
long long ii = 1;
long long n, k, q;
long long get_rank(long long x){
	long long left = 1;
	long long right = ii;
	long long ans = 0;
	while (left <= right){
		long long mid = (left + right) >> 1LL;
		if (x <= sum[mid]){
			ans = mid-1 ;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return ans;
}

long long get_parent(long long x,long long rx){
	long long cidx = x - sum[rx];  //현재 높이에서의 인덱스
	long long ccidx = (cidx - 1) % k + 1;
	long long parent = (x + (k - 2) - ccidx + 1) / k;   //
	return parent;
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k >> q;
	sum[1] = 1;
	long long s = 0;
	long long num = 1;
	if (k == 1){ //1진 트리일때 예외처리 하자.
		for (long long qq = 0; qq < q; qq++){
			long long x, y;
			cin >> x >> y;
			cout << abs(x - y)<<"\n";
		}
		return 0;
	}
	while (s < n){  
		sum[ii] = sum[ii - 1] + num;
		ii++;
		s += num;
		num *= k;
	}
	ii--;
	for (long long qq = 0; qq < q; qq++){
		a_par.clear(), b_par.clear();
		long long x, y;
		cin>> x >> y;
		long long rx = get_rank(x);
		long long ry = get_rank(y);
		a_par.push_back(1), b_par.push_back(1);
		while (x != 1){
			a_par.push_back(x);
			x = get_parent(x, get_rank(x));
		}
		while (y != 1){
			b_par.push_back(y);
			y = get_parent(y, get_rank(y));
		}
		sort(a_par.rbegin(), a_par.rend());
		sort(b_par.begin(), b_par.end());
		long long prank = 0;
		for (long long i = 0; i < a_par.size(); i++){
			if (binary_search(b_par.begin(), b_par.end(), a_par[i])){
				prank = lower_bound(b_par.begin(), b_par.end(), a_par[i]) - b_par.begin();
				break;   //무조건 한번은 걸림
			}
		}
		cout << rx + ry - 2*prank<<"\n";
	}
	return 0;
}