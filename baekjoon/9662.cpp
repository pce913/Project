//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <limits.h>
//#include <stack>
//#include <queue>
//#include <map>
//#include <set>
//#include <algorithm>
//using namespace std;
//typedef int lint;
//typedef long double llf;
//typedef pair<int, int> pi;
//
//int sk[2005], cy[2005];
//int m, n, a[25];
//
//int getsk(int x);
//int getcy(int x);
//
//int getsk(int x){
//	if (~sk[x]) return sk[x];
//	int ret = 0;
//	for (int i = 0; i<n; i++){
//		if (x - a[i] >= 0 && !getcy(x - a[i])){
//			ret = 1;
//		}
//	}
//	return sk[x] = ret;
//}
//
//int getcy(int x){
//	if (~cy[x]) return cy[x];
//	int ret = 0;
//	for (int i = 0; i<n; i++){
//		if (x - a[i] >= 0 && !getsk(x - a[i])){
//			ret = 1;
//		}
//	}
//	return cy[x] = ret;
//}
//
//int main(){
//	scanf("%d %d", &m, &n);
//	for (int i = 0; i<n; i++) scanf("%d", &a[i]);
//	memset(cy, -1, sizeof(cy));
//	memset(sk, -1, sizeof(sk));
//	for (int i = 1; i <= 2000; i++){
//		getsk(i);
//	}
//	int joogy = 0;
//	for (int i = 1; i <= 2000; i++){
//		bool bad = 0;
//		for (int j = i; j + i <= 2000; j++){
//			if (sk[j] != sk[j + i]){
//				bad = 1;
//				break;
//			}
//		}
//		if (bad == 0){
//			joogy = i;
//			break;
//		}
//	}
//	if (m <= joogy){
//		printf("%d", count(sk + 1, sk + m + 1, 0));
//		return 0;
//	}
//	else{
//		int ret = count(sk + 1, sk + joogy, 0);
//		ret += ((m - joogy + 1) / joogy)* count(sk + joogy, sk + 2 * joogy, 0);
//		ret += count(sk + joogy, sk + joogy + (m + 1) % joogy, 0);
//		printf("%d", ret);
//	}
//}

#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> a;
bool D[3005];
int main(){
	int m;
	scanf("%d",&m);
	int k;
	scanf("%d",&k);
	for (int i = 0; i < k; i++){
		int x;
		scanf("%d",&x);
		a.push_back(x);
	}
	D[0] = false;
	for (int i = 1; i <= 2000; i++){
		for (int j = 0; j < a.size(); j++){
			if (i - a[j] >= 0 ){
				if (!D[i - a[j]])
					D[i] = true;
			}
		}
	}
	int clen = 0;
	for (int len = 1; len <= 1000; len++){
		int left = len;       //left를 0, right를 len으로 초기화 하면 런타임 에러 난다. 왜지?
		int right = len + len;
		bool isDiff = false;
		while (right <= 2000){    //슬라이딩 윈도우처럼 끝까지 대어 보아야 답을 찾기 수월하다.
			if (D[left++] != D[right++]){
				isDiff = true;
				break;
			}
		}
		if (!isDiff){
			clen = len;
			break;
		}
	}

	if (m <= clen){
		printf("%d", count(D + 1,D  + m + 1, 0));
		return 0;
	}
	int ans = count(D + 1, D + clen, false);
	ans += ((m - clen + 1) / clen)*count(D + clen, D + 2 * clen, false);    //범위를 D + clen, D + 2 * clen로 해야 틀리지 않는다.
	ans += count(D + clen, D + clen + (m + 1) % clen, false);
	printf("%d",ans);
	return 0;
}