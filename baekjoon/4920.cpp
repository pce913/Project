#include<stdio.h>
#include<algorithm>
using namespace std;
const long long INF = 1e18;
long long n;
long long M[105][105];
long long dx[5][4][4] = { { { 0, 0, 0, 0 }, { 0, 1, 2, 3 } },
{ { 0, 0, 1, 1 }, { 0, -1, -1, -2 } },
{ { 0, 0, 0, 1 }, { 0, 0, 1, 2 }, { 0, 1, 1, 1 }, { 0, 0, -1, -2 } },
{ { 0, 0, 0, 1 }, { 0, 1, 2, 1 }, { 0, 0, 0, -1 }, { 0, 0, -1, 1 } },
{ { 0, 0, 1, 1 } } };

long long dy[5][4][4] = { { { 0, 1, 2, 3 }, { 0, 0, 0, 0 } },
{ { 0, 1, 1, 2 }, { 0, 0, 1, 1 } },
{ { 0, 1, 2, 2 }, { 0, 1, 0, 0 }, { 0, 0, 1, 2 }, { 0, 1, 1, 1 } },
{ { 0, 1, 2, 1 }, { 0, 0, 0, 1 }, { 0, 1, 2, 1 }, { 0, 1, 1, 1 } },
{ { 0, 1, 0, 1 } } };

long long sz[5] = { 2, 2, 4, 4, 1 };

long long go(long long cx,long long cy){
	long long ret = -INF;
	for (long long i = 0; i < 5; i++){
		for (long long j = 0; j < sz[i]; j++){
			bool isCan = true;
			long long temp = 0;
			for (long long k = 0; k < 4; k++){
				long long nx = cx + dx[i][j][k];
				long long ny = cy + dy[i][j][k];
				if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
					temp += M[nx][ny];
				}
				else{
					isCan = false;
					break;
				}
			}
			if (isCan){
				ret = max(ret, temp);
			}
		}
	}
	return ret;
}

void solve(long long test){
	long long ans = -INF;
	for (long long i = 1; i <= n; i++){
		for (long long j = 1; j <= n; j++){
			scanf("%lld",&M[i][j]);
		}
	}
	for (long long i = 1; i <= n; i++){
		for (long long j = 1; j <= n; j++){
			long long aa = go(i, j);
			ans = max(ans, aa);
		}
	}
	printf("%lld. %lld\n",test,ans);
}
int main(){
	//freopen("test3.txt","r",stdin);
	//freopen("tetris.in", "r", stdin);
	//freopen("output.txt","w",stdout);
	long long T = 1;
	while (scanf("%lld",&n)){
		if (n == 0)
			break;
		solve(T++);
	}
	return 0;
}