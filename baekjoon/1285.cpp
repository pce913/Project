#include<iostream>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<cstring>
using namespace std;

//simulated anealing
//http://koosaga.com/3

int ori[35];
int ori_cnt[35];
int nw[35];
int nw_cnt[35];
int n;

int cnt_sum(int cnt[]){
	int ret = 0;
	for (int i = 0; i < n; i++)
		ret += min(cnt[i], n - cnt[i]);
	return ret;
}

void go(){
	memcpy(nw, ori, sizeof(nw));
	memcpy(nw_cnt, ori_cnt, sizeof(nw_cnt));
	int idx = rand() % n;  //무슨 행을 뒤집을 것인가.
	for (int i = 0; i < n; i++){
		if (nw[idx] & (1 << i))
			nw_cnt[i]--;
		else
			nw_cnt[i]++;
		nw[idx] ^= (1 << i);
	}
}

int main(){
	srand(6969696969);
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			char x;
			cin >> x;
			if (x == 'T'){
				ori[i] |= (1 << j);
				ori_cnt[j]++; //각 열에 T가 몇개있는지
			}
		}
	}
	int E1 = cnt_sum(ori_cnt);
	double K = 1, T = 1;
	for (int i = 0; i < 31415; i++){
		go();
		int E2 = cnt_sum(nw_cnt);
		if (E1 - E2>log(rand() % 10000 / 1e4) * K * T){
			E1 = E2;
			memcpy(ori, nw, sizeof(ori));
			memcpy(ori_cnt, nw_cnt, sizeof(ori_cnt));
		}
		T *= 0.99998;
	}
	cout << E1;
	return 0;
}