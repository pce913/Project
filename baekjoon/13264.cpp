#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
//radix sort를 이용하면 suffix array는 빠르게 구할 수 있지만, lcp를 구할때 불편하지 않나?
struct suffix {
	int index;
	int rank[2];
}; 
//t글자를 기준으로 정렬되어 있다면, t*2글자를 기준으로도 정렬할 수 있다.
void radix_sort(int len, vector<int> &sa, vector<int> &group) {
	int n = sa.size();   //n: suffix array중 가장 긴 문자열의 길이.
	vector<suffix> a(n);
	for (int i = 0; i<n; i++) {
		a[i].index = sa[i];  //index: 몇번 접미사 인지를 저장
		a[i].rank[0] = group[sa[i]];  //rank[0]: 해당 접미사가 몇번 그룹인지를 저장.
		if (sa[i] + len < n) {
			a[i].rank[1] = group[sa[i] + len];  //rank[1]: 해당 접미사+len가 몇번 그룹인지를 저장.
		}
		else {
			a[i].rank[1] = -1;  //대신 크기가 n을 넘어가면 -1을 저장해준다. 실제로 크기가 n과 같은 경우는 있지만 n을 넘어가지는 않는다. 
		}
	}
	vector<suffix> temp(n);
	for (int p = 1; p >= 0; p--) { //2번 반복
		vector<int> cnt(n + 1, 0);
		vector<int> sum(n + 2, 0);
		for (int i = 0; i < n; i++) {
			cnt[a[i].rank[p] + 1] += 1;  //먼저, '해당 접미사+len 의 그룹번호' + 1 의 개수를 세어준다.
		}
		for (int i = 1; i < n + 1; i++) {   //누적합을 구해준다. 그룹은 최대 n개 생길 수 있다.
			sum[i] = sum[i - 1] + cnt[i - 1]; //sum[i]에는 i - 1 번째까지의 누적합이 구해져 있다. i번째가 아니다.
		} 
		for (int i = 0; i<n; i++) {
			temp[sum[a[i].rank[p] + 1]++] = a[i];
		}
		for (int i = 0; i<n; i++) {
			a[i] = temp[i];
		}
	}
	//이 위쪽 까지 실행되면 sa가 그룹별로 묶여있다.

	for (int i = 0; i<n; i++) {
		sa[i] = a[i].index;
	}  
	group[a[0].index] = 0;   //소팅 후 그룹 재결성
	for (int i = 1; i<n; i++) {    
		if (a[i].rank[0] == a[i - 1].rank[0] && a[i].rank[1] == a[i - 1].rank[1]) {
			group[a[i].index] = group[a[i - 1].index];
		}
		else {
			group[a[i].index] = group[a[i - 1].index] + 1;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	int n = s.length();
	vector<int> sa(n);
	vector<int> group(n);
	for (int i = 0; i<n; i++) {
		sa[i] = i;
	}
	for (int i = 0; i<n; i++) {
		group[i] = s[i] - 'a';
	}
	for (int len = 1; len / 2 < n; len *= 2) {   //같은 그룹이니? 를 확인하는 작업을 logn번 해줘야 한다.  1글자로 정렬, 2글자로 정렬, 4글자로 정렬...
		radix_sort(len, sa, group);  //stl sort를 radix sort로 대체한 것이다.
	}
	for (int i = 0; i<n; i++) {
		cout << sa[i] << '\n';
	}
	return 0;
}
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<string>
//using namespace std;
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	string s;
//	cin >> s;
//	int n = s.size();
//	vector<int> sa(n);   //sa: suffix array     이건 push.back()하지 않고 미리 공간을 만들어 놓는게 직관적이다.
//	vector<int> group(n + 1);
//	for (int i = 0; i < n; i++){
//		sa[i] = i;
//	}
//	for (int i = 0; i < n; i++){
//		group[i] = s[i];
//	}
//	group[n] = -1;    //마지막 접미사 배열 비교 할때 필요함. 백준 강의 노트와 13013번 문제 참고.
//	for (int len = 1; len / 2 < n; len *= 2){   //logn번 돈다.
//		auto cmp = [&](const int& u,const int& v){   //[&]: 람다 함수 밖에 있는 모든 변수들을 레퍼런스 형태로 가져오겠다.
//			if (group[u] == group[v]){   //먼저 두 그룹번호를 비교하고 두 그룹번호가 같다면
//				return group[u + len] < group[v + len];  //len만큼 떨어진 부분을 비교한다. 아하.
//			}
//			else{
//				return group[u] < group[v];
//			}
//		};
//		sort(sa.begin(), sa.end(), cmp);
//
//		/////이전과 현재 인덱스가 그룹번호가 같은지 다른지를 비교하여 새로 그룹번호를 배겨줌.
//		vector<int> group2(n + 1);   
//		group2[sa[0]] = 0;   //정렬된 suffix array의 맨앞에 있는 접미사 배열은 당연히 0번 그룹이 된다.
//		group2[n] = -1;
//		for (int i = 1; i < n; i++){
//			if (cmp(sa[i - 1], sa[i])){   //sa[i-1]이 sa[i]보다 그룹순서로 앞선다면, 즉, 사전순으로 앞에 있다면
//				group2[sa[i]] = group2[sa[i - 1]] + 1;    //새로 정렬된 기준으로 다시 그룹번호를 매겨준다.
//			}
//			else{  //sa[i-1]와 sa[i]가 같은 그룹순서인 경우이다.   sa[i-1]가 sa[i]보다 그룹순서가 앞설수는 없다.
//				group2[sa[i]] = group2[sa[i - 1]];
//			}
//		}
//		group = group2;
//	}
//	for (int i = 0; i < n; i++){
//		cout << sa[i] << "\n";
//	}
//	return 0;
//}