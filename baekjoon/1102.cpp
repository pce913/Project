//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//	int argc = 3;
//	char* argv[] = {"split","-ab","test"};
//	for (int i = 1; i < argc; i++){
//		printf("argv[%d]: %s\n",i,argv[i]);
//		int j = 0;
//		if (argv[i][j] == '-'){
//			printf("option: ");
//			j += 1;
//			while (argv[i][j] != '\0'){
//				printf("%c ",argv[i][j]);
//				j++;
//			}
//			printf("\n");
//		}
//	}
//	return 0;
//}
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//const int INF = 1000000000;
//int n;
//int D[1 << 16];
//bool check[1 << 16];
//int S[16][16];
//char W[17];
//int p;
//
//int pop_count(int bit){
//	int cnt = 0;
//	while (bit){
//		bit -= (bit&-bit);
//		cnt++;
//	}
//	return cnt;
//}
//
//int go(int mask){
//	if (pop_count(mask) == p){
//		check[mask] = true;
//		return 0;
//	}
//
//	if (check[mask]){
//		return D[mask];
//	}
//
//	check[mask] = true;
//	int& ans = D[mask];
//	ans = INF;
//	for (int k = 0; k < n; k++){
//		if (mask&(1 << k)){        //켜있는애들
//			for (int j = 0; j < n; j++){
//				if (S[k][j] == 0)
//					continue;
//				if ((mask&(1 << j))==0){          // 꺼져있는애들
//					ans = min(ans, go(mask | (1 << j)) + S[k][j]);
//				}
//			}
//		}
//	}
//	
//	return ans;
//}
//
//
//int main(){
//	scanf("%d",&n);
//	for (int i = 0; i < n; i++){
//		for (int j = 0;j<n;j++)
//			scanf("%d",&S[i][j]);
//	}
//	scanf("%s", &W);
//
//	int start = 0;
//	for (int i = n-1; i >= 0; i--){          // 시작 위치를 결정.
//		start = start * 2;
//		if (W[i] == 'Y'){
//			start += 1;
//		}
//	}
//	scanf("%d",&p);
//	int ans=go(start);
//	//int ans = -1;
//	//for (int bit = 0; bit<(1 << n); bit++) {             // 켜진 비트수 확인.
//	//	if (!check[bit])
//	//		continue;
//	//	int cnt = pop_count(bit);
//	//	if (cnt >= p) {          // 문제에서 적어도 p이라고 했으나 '적어도' 이므로 p보다 많이 발전소를 복구해도 된다.
//	//		if (ans==-1 || ans > D[bit]) {
//	//			ans = D[bit];
//	//		}
//	//	}
//	//}
//	if (ans != INF){
//		printf("%d",ans);
//	}
//	else{
//		printf("-1");
//	}
//	//printf("%d",ans);
//	return 0;
//}

//#include <cstdio>
//#include<algorithm>
//using namespace std;
//
//int a[16][16];
//char str[17];
//int d[1 << 16];
//bool check[1 << 16];
//int popcount(int bit){
//	int r=0;
//	while (bit){
//		bit -= (bit&-bit);
//		r++;
//	}
//	return r;
//}
//int main() {
//	int n;
//	scanf("%d", &n);
//	for (int i = 0; i<n; i++) {
//		for (int j = 0; j<n; j++) {
//			scanf("%d", &a[i][j]);
//		}
//	}
//	scanf("%s", str);
//	int start = 0;
//	for (int i = n - 1; i >= 0; i--) {
//		start = start * 2;
//		if (str[i] == 'Y') {
//			start += 1;
//		}
//	}
//	int p;
//	scanf("%d", &p);
//
//	check[start] = true;
//	int ans = 1e9;
//	for (int i = 0; i<(1 << n); i++) {
//		if (!check[i])
//			continue;
//		if (popcount(i) >= p){
//			ans = min(ans, d[i]);
//		}
//		for (int j = 0; j<n; j++) {
//			if (i&(1 << j)) { // j가 켜져 있음
//				for (int k = 0; k<n; k++) {
//					if ((i&(1 << k)) == 0) { // k가 꺼져있음
//						if (check[i | (1 << k)]==false || d[i | (1 << k)] > d[i] + a[j][k]) {        // 켜져있는 애들중에서 꺼진애를 복구.
//							d[i | (1 << k)] = d[i] + a[j][k];
//							check[i | (1 << k)] = true;
//						}
//					}
//				}
//			}
//		}
//		
//	}
//	if (ans >= 1e9)
//		printf("-1");
//	else 
//		printf("%d", ans);
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<string>
using namespace std;
class Robofactory{
public:
	int reveal(vector <int> query, vector <string> answer){
		vector<int> ans_arr(answer.size());
		int even_num = 0;
		for (int i = 0; i < answer.size(); i++){
			if (answer[i] == "Odd"){
				ans_arr[i] = 1;
			}
			else{
				ans_arr[i] = 0;
				even_num++;
			}
		}
		
		for (int i = 0; i < query.size(); i++){           //1번 케이스
			if (query[i]%2  != ans_arr[i]){
				return i;
			}
		}

		if (even_num >= 2){        //even 갯수 2개 이상일때
			return -1;
		}
		else if (even_num == 1){     // even갯수 1개일때
			if (ans_arr.back()!= 0){       //맨뒤가 even이 아니면 -1
				return -1;
			}
			else{            //맨뒤가 even이면 
				return 0;
			}
		}
		
		return 0;

	}
};

