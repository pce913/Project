#define P1

#ifdef P1
#include<stdio.h>
int N, S, M;
bool check[101][1001];
int V[101];
int ans=-1;

bool dfs(int n,int p){         //  n 번 곡, p 현재볼륨
	if (n > N || p<0 || p>M)
		return false;

	if (n == N){
		ans = ans > p ? ans : p;
	}
		
	if (check[n][p])
		return true;

	check[n][p] = true;
	//printf("%d %d\n",n,p);
	dfs(n + 1, p - V[n+1]);
	dfs(n + 1, p + V[n+1]);
	
	return true;
}

int main(){
	scanf("%d %d %d",&N,&S,&M);
	for (int i = 1; i <= N; i++)
		scanf("%d",&V[i]);
	
	dfs(0, S);            //0 S

	printf("%d",ans);                 //마지막곡 연주 못할 시에 -1 출력
	return 0;
}
#endif
#ifdef P2

#include<stdio.h>
int check[101][1001];
int main()
{
	int tc, start, m, p;
	scanf("%d %d %d", &tc, &start, &m);
	check[0][start] = 1;
	for (int i = 0; i < tc; i++)
	{
		scanf("%d", &p);
		for (int j = 0; j <= m; j++)
		{
			if (!check[i][j]) continue;
			if (j - p >= 0) check[i + 1][j - p] = 1;
			if (j + p <= m)check[i + 1][j + p] = 1;
		}
	}
	int k;
	for (k = m; k >= 0; k--)
	if (check[tc][k]) break;
	printf("%d\n", k);
	return 0;
}
#endif