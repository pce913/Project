#include<stdio.h>
#include<algorithm>
using namespace std;

int main(){
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	printf("%d", min({(n+m-k)/3,n/2,m}));
	return 0;
}
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//int main(){
//	int n, m, k;
//	scanf("%d %d %d",&n,&m,&k);
//	int team;
//	if (n / 2 > m){
//		team = m;
//		int nam = n - 2*m;
//		if (nam < k){
//			k -= nam;
//			int g = k / 3;
//			int s = k % 3;
//			team-= g;
//			if (s != 0)
//				team--;
//		}
//	}
//	else if (n/2 <=m){
//		team = n / 2;
//		int nam = m - n / 2;
//		if (n % 2 == 1){
//			nam += 1;
//		}
//		if (nam < k){
//			k -= nam;
//			int g = k / 3;
//			int s = k % 3;
//			team -= g;
//			if (s != 0)
//				team--;
//		}
//	}
//	printf("%d",team);
//	return 0;
//}