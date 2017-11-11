#include<algorithm>
#include<iostream>
#include<string>
using namespace std;

bool D[2501][2501];
int DD[2051];
string A;

int main(){
	freopen("input.txt", "r", stdin);
	int i, j;
	cin >> A;
	int N = A.size();

	for (int k = 0; k < N; k++){
		DD[k] = k;
		for (int i = 1; i <= N - k; i++){
			if (A[i-1] == A[i + k-1] && (k<=1 || D[i + 1][i + k - 1] == true))
				D[i][i + k] = true;

			/*if (A[i - 1] != A[i + k - 1])
				continue;
			if (k > 1 && D[i + 1][i + k - 1] != true)
				continue;
			D[i][i + k] = true;*/
		}
	}
	DD[N] = N;
	for (int i = 1; i <= A.size(); i++){
		for (int j = i; j >= 1; j--){
			if (D[j][i] != true){
				continue;
			}
			DD[i] = min(DD[i], DD[j - 1] + 1);
		}
	}
	cout << DD[N];
	return 0;
}
//#include <iostream>
//#include <string>
//
//using namespace std;
//string s;
//int p[2501][2501];
//int d[2501];
//int min(int a, int b){ return a < b ? a : b; }
//int main(){
//	freopen("input.txt", "r", stdin);
//	int i, j;
//	cin >> s;
//
//	for (i = 0; i < s.size(); i++){
//		d[i] = i;
//		for (j = 1; j <= s.size() - i; j++){
//
//			if (s[j - 1] != s[j + i - 1]) continue;
//			if (i>1 && p[j + 1][j + i - 1] != 1) continue;
//			p[j][j + i] = 1;
//		}
//	}
//	d[i] = i;
//
//	for (i = 1; i <= s.size(); i++){
//		for (j = i; j >= 1; j--){
//			if (p[j][i] != 1) continue;
//			d[i] = min(d[i], d[j - 1] + 1);
//		}
//	}
//
//	cout << d[s.size()];
//	return 0;
//}
