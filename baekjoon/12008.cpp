#include<stdio.h>
#include<algorithm>
using namespace std;
const int MAXN = 270000;
int D[MAXN][65]; //D[idx][num]: 마지막 idx로 num을 만들 수 있다고 할때 그때의 left 인덱스.
int a[MAXN];

///*2 2 2 2 2 2 2 2
//        ^ 
//	이것이 바로 D[8][4] = 4 를 나타냄.

////나올 수 있는 숫자는 커봐야 65 이하이다.
////어떤 숫자 x를 기준으로 우리가 원하는 숫자 w를 만들기 위해서는 2의 지수승 만큼의 w가 필요하다.
////예를 들어 5(w)를 만들기 위해서는 2(x)가 8개 필요하다. 

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		D[i][a[i]] = i;
	}
	for (int j = 1; j <= 65; j++){
		for (int i = 1; i <= n; i++){
			if (D[i][j] != 0 && D[D[i][j] - 1][j] != 0){
				D[i][j+1] = D[D[i][j] - 1][j];
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= 65; j++){
			if (D[i][j]!=0)
				ans = max(ans, j);
		}
	}
	printf("%d",ans);
	return 0;
}

//#include <iostream>
//#include<algorithm>
//using namespace std;
//const int MAXN = 262145;
//int n;
//long long a[MAXN];
//int dp[MAXN][67];
//int main(){
//	ios::sync_with_stdio(false); cin.tie(0);
//	cin >> n;
//	for (int i = 1; i <= n; i++){
//		cin >> a[i];
//		dp[i][a[i]] = i;
//	}
//	for (int i = 2; i <= 66; i++){
//		for (int j = 1; j <= n; j++){
//			if (!dp[j][i - 1])continue;
//			int idx = dp[j][i - 1] - 1;
//			if (dp[idx][i - 1]){
//				dp[j][i] = dp[idx][i - 1];
//			}
//		}
//	}
//	int ans = 0;
//	for (int i = 1; i <= n; i++){
//		for (int j = 0; j<67; j++){
//			if (dp[i][j]){
//				ans = max(ans, j);
//			}
//		}
//	}
//	cout << ans;
//	return 0;
//}
//#include <cstdio>  
//#include <algorithm>  
//using namespace std;
//int f[262200][65], a[262200];    //f[idx][num]: 마지막 idx로 num을 만들 수 있다고 할때 그때의 right 인덱스.
////나올 수 있는 숫자는 커봐야 65 이하이다.
////어떤 숫자 x를 기준으로 우리가 원하는 숫자 w를 만들기 위해서는 2의 지수승 만큼의 w가 필요하다.
////예를 들어 5(w)를 만들기 위해서는 2(x)가 8개 필요하다. 
//
///*2 2 2 2 2 2 2 2
//        ^ 
//	이것이 바로 f[4][4] = 4 를 나타냄.
// */
//int main()
//{    //디버깅 돌려보자.
//	int n, m;
//	scanf("%d", &n);
//	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), f[i][a[i]] = i, m = max(m, a[i]);
//	//m: 나올 수 있는 숫자의 최댓값
//	for (int j = 1; j <= m; j++){   //j: 나올 수 있는 숫자
//		for (int i = 1; i <= n; i++){  //i: 인덱스
//			if (f[i][j] != 0 && f[f[i][j] + 1][j] != 0){
//				f[i][j + 1] = f[f[i][j] + 1][j];
//				if (j + 1 > m)
//					m = j + 1;   //여기 m값이 달라짐에 따라서 바깥쪽 for문의 m도 영향을 받는다.
//				     //이렇게 안하고
//			}
//		}
//	}
//	printf("%d", m);
//}