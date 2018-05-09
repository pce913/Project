#include<stdio.h>
#include<algorithm>
using namespace std;
int D[1001][31];           // D[i][j] : i 초동안 움직인 횟수가 j 번 일때 최댓값.
int A[1001];
bool check[1001][31];

int go(int sec,int turn){
	if (sec == 0 || turn < 0){
		return 0;
	}
	
	if (check[sec][turn])
		return D[sec][turn];

	check[sec][turn] = true;

	int position = turn % 2 + 1;
	D[sec][turn] = max(go(sec - 1, turn),go(sec-1,turn-1))+( position ==A[sec] ? 1 : 0);
	return D[sec][turn];
}

int main(){
	int t, w;
	scanf("%d %d",&t,&w);
	for (int i = 1; i <= t; i++){
		scanf("%d",&A[i]);
	}
	printf("%d", max(go(t, w),go(t,w-1)));      //출발점을 1로 할 것이냐 2로 할 것이냐. 
	                                           
	return 0;
}