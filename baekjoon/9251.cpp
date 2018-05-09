#include<iostream>
#include<string>
#include <cstring>
#include<algorithm>
#include <vector>
using namespace std;
//역추적(백트래킹) 하는 문제는 재귀로 풀어야 쉽다!
//여러개의 LCS를 찾는 버젼도 9252번에 제출해두었음.
string s1, s2;
int D[1005][1005];
string ans;
int go(int i,int j){
	if (i == s1.size() || j == s2.size())return 0;
	int& ret = D[i][j];
	if (ret != -1)
		return ret;
	ret = 0;
	if (s1[i] == s2[j]){
		ret = go(i + 1, j + 1) + 1;
	}
	else{
		ret = max(go(i + 1, j), go(i, j + 1));
	}
	return ret;
}

void backtracking(int i,int j){
	if (i == s1.size() || j == s2.size())return;
	if (s1[i] == s2[j]){
		ans.push_back(s1[i]);
		backtracking(i + 1, j + 1);
	}
	else{
		if (D[i + 1][j] > D[i][j + 1]){
			backtracking(i + 1, j);
		}
		else{
			backtracking(i, j + 1);
		}
	}
}

int main(){                      // 최대길이 부분 문자열의 길이.
	cin >> s1 >> s2;
	memset(D, -1, sizeof(D));
	cout << go(0, 0) << "\n";
	backtracking(0, 0);
	cout << ans;
	return 0;
}