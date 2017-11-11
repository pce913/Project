//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//const int MINF = -100000000;
//int n;
//int A[50];
//int D[50][250001];          // D[i][j] : i 번째 조각까지 사용했을때 높이차가 j 일때의 높이
//bool check[50][250001];
//int go(int k,int diff){
//	if (diff > 250000){
//		return MINF;
//	}
//	if (k == n){
//		if (diff == 0){
//			return 0;
//		}
//		else{
//			return MINF;
//		}
//	}
//	if (check[k][diff])
//		return D[k][diff];
//
//	check[k][diff] = true;
//	int& ans = D[k][diff];
//	ans = go(k + 1, diff);
//	ans = max(ans, go(k + 1, diff + A[k]));      // 높은 탑 위에 올려놓았을때
//	if (A[k] > diff){                //낮은 탑 위에 올려 놓았을때
//		ans = max(ans, go(k + 1, A[k] - diff) + diff);
//	}
//	else{
//		ans = max(ans, go(k + 1, diff - A[k]) + A[k]);
//	}
//	return ans;                                             //ans에는 결국 높이가 같은 애들만
//}
//
//int main(){
//	scanf("%d",&n);
//	for (int i = 0; i < n; i++){
//		scanf("%d",&A[i]);
//	}
//	int ans = go(0,0);
//	if (ans == 0)
//		printf("-1");
//	else
//		printf("%d", ans);
//	return 0;
//}
#include<stdio.h>
#include<algorithm>
using namespace std;

const int MINF = -100000000;
int A[50];
int D[50][250001];          // D[i][j] : i 번째 조각까지 사용했을때 높이차가 j 일때 높이가 같은 부분의 높이.
bool check[50][250001];
int go(int k, int diff){
	if (diff > 250000){
		return MINF;
	}
	if (k < 0){
		if (diff == 0){
			return 0;
		}
		else{
			return MINF;
		}
	}
	if (check[k][diff])
		return D[k][diff];

	check[k][diff] = true;
	int& ans = D[k][diff];
	ans = go(k - 1, diff);
	ans = max(ans, go(k - 1, diff + A[k]));      // 높은 탑 위에 올려놓았을때
	if (A[k] > diff){                               // 낮은 탑 위에 올려놓았을때
		ans = max(ans, go(k - 1, A[k] - diff) + diff);
	}
	else{
		ans = max(ans, go(k - 1, diff - A[k]) + A[k]);
	}
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &A[i]);
	}
	int ans = go(n-1, 0);
	if (ans == 0)
		printf("-1");
	else
		printf("%d",ans);
	return 0;
}