#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
//모든 부분 문자열은 suffix의 prefix 이다.
//1.suffix array 구해
//2.각각의 suffix에 대해 prefix의 개수 구해.

int lcp(string& s, int i, int j){    //lcp O(N) 버젼. O(logn) 버젼은 11479번: 서로 다른 부분문자열의 개수2 에 있다. 
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]){
		i++, j++, k++;
	}
	return k;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	vector<int> sa(n);
	vector<int> group(n + 1);
	for (int i = 0; i < n; i++){
		sa[i] = i;
	}
	for (int i = 0; i < n; i++){
		group[i] = s[i];
	}
	group[n] = -1;
	for (int len = 1; len / 2 < n; len *= 2){  //suffix array 구하기
		auto cmp = [&](const int& u, const int& v){
			if (group[u] == group[v]){
				return group[u + len] < group[v + len];
			}
			else{
				return group[u] < group[v];
			}
		};
		sort(sa.begin(), sa.end(), cmp);

		vector<int> group2(n + 1);
		group2[sa[0]] = 0;
		group2[n] = -1;
		for (int i = 1; i < n; i++){
			if (cmp(sa[i - 1], sa[i])){
				group2[sa[i]] = group2[sa[i - 1]] + 1;
			}
			else{
				group2[sa[i]] = group2[sa[i - 1]];
			}
		}
		group = group2;
	}
	long long ans = 0;
	for (int i = 0; i < n; i++){
		int cp = 0;
		if (i>0){
			cp = lcp(s, sa[i - 1], sa[i]);    //lcp는 suffix array 에서 각각의 접미사 배열 사이의 관계를 보는것이다.
		}    //길이가 n인 문자열의 prefix의 갯수는 n이다.
		ans += (s.size() - sa[i]) - cp;   //s.size()-sa[i] : i번째 suffix 의 길이. 길이가 n인 문자열의 prefix의 개수는 n이다.
	}                                      //여기서 겹치는 부분인 lcp를 빼줘야 한다.
	cout << ans;
	return 0;
}
//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<vector>
//using namespace std;
////모든 부분 문자열은 suffix의 prefix 이다.
////1.suffix array 구해
////2.각각의 suffix에 대해 prefix의 개수 구해.
//
//int lcp(string& s,int i,int j){    //lcp O(N) 버젼. O(logn) 버젼은 11479번: 서로 다른 부분문자열의 개수2 에 있다. 
//	int k = 0;
//	while (i < s.size() && j < s.size() && s[i] == s[j]){
//		i++, j++, k++;
//	}
//	return k;
//}
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	string s;
//	cin >> s;
//	int n = s.size();
//	vector<int> sa(n);
//	vector<vector<int> > group(20, vector<int>(n + 1));  //20으로 잡는 이유는 밑에 len의 로그값이 아무리 커도 20은 넘지 않기 때문이다. 즉, len은 아무리 커도 2^20은 넘지 않는다.
//	for (int i = 0; i < n; i++){
//		sa[i] = i;
//	}
//	for (int i = 0; i < n; i++){
//		group[0][i] = s[i];
//
//	}
//	group[0][n] = -1;
//	for (int k = 0, len = 1; len / 2 < n; k += 1, len *= 2){  //suffix array 구하기
//		auto cmp = [&](const int& u, const int& v){
//			if (group[k][u] == group[k][v]){
//				return group[k][u + len] < group[k][v + len];
//			}
//			else{
//				return group[k][u] < group[k][v];
//			}
//		};
//		sort(sa.begin(), sa.end(), cmp);
//
//		group[k + 1][sa[0]] = 0;
//		group[k + 1][n] = -1;
//		for (int i = 1; i < n; i++){
//			if (cmp(sa[i - 1], sa[i])){
//				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]] + 1;
//			}
//			else{
//				group[k + 1][sa[i]] = group[k + 1][sa[i - 1]];
//			}
//		}
//	}
//	long long ans = 0;
//	for (int i = 0; i < n; i++){
//		int cp = 0;
//		if (i>0){
//			cp = lcp(s, sa[i - 1], sa[i]);    //lcp는 suffix array 에서 각각의 접미사 배열 사이의 관계를 보는것이다.
//		}    //길이가 n인 문자열의 prefix의 갯수는 n이다.
//		ans += (s.size() - sa[i]) - cp;   //s.size()-sa[i] : i번째 suffix 의 길이. 길이가 n인 문자열의 prefix의 개수는 n이다.
//	}                                      //여기서 겹치는 부분인 lcp를 빼줘야 한다.
//	cout << ans;
//	return 0;
//}