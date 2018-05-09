#include<stdio.h>
int n;
char p[1000005];
int pi[1000005];

void fill_pi(){   //1베이스
	pi[1] = 0;
	int j = 1;
	for (int i = 2; i <= n; i++){
		while (j > 1 && p[i] != p[j]){
			j = pi[j - 1] + 1;
		}
		if (p[i] == p[j]){
			pi[i] = j;
			j += 1;
		}
		else{
			pi[i] = 0;
		}
	}
}

int main(){
	scanf("%d", &n);
	scanf("%s", &p[1]);
	fill_pi();               //pi는 i까지 보았을때 prefix==sufix 인 것중에 최대 길이를 저장하고 있다.
	printf("%d", n - pi[n]);    //전체 광고판 길이에서 pi를 빼준값이 정답이 된다.
	return 0;
}
//#include<stdio.h>
//#include<iostream>
//#include<string>
//#include<vector>
//using namespace std;
//int n;
//string p;
////이 문제를 1베이스로 풀면 이상하게 계속 틀린다. 왜 그런걸까?
//vector<int> preprocessing(string p) {  //0 베이스
//	vector<int> pi(n);
//	pi[0] = 0;
//	int j = 0;
//	for (int i = 1; i<n; i++) {
//		while (j>0 && p[i] != p[j]) {
//			j = pi[j - 1];
//		}
//		if (p[i] == p[j]) {
//			pi[i] = j + 1;
//			j += 1;
//		}
//		else {
//			pi[i] = 0;
//		}
//	}
//	return pi;
//}
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin >> n >> p;
//	//pi는 i까지 보았을때 prefix==sufix 인 것중에 최대 길이를 저장하고 있다.
//	auto pi = preprocessing(p);
//	printf("%d", n - pi[n - 1]);    //전체 광고판 길이에서 pi를 빼준값이 정답이 된다.
//	return 0;
//}