#include<stdio.h>
#include<queue>
#include<cstring>
using namespace std;
bool prime[10001];
bool check[10001];
int dist[10001];
int ci[4] = { 1000, 100, 10, 1 };
int per[4];
void calcPrime(){
	memset(prime,true,sizeof(bool)*10001);
	for (int i = 2; i <= 10000; i++){
		if (prime[i] == true){
			for (int j = i * i; j <= 10000; j += i)
				prime[j] = false;
		}
	}
}

int change(int p,int _i,int _j){
	int c = ci[_i] * _j + p - per[_i]*ci[_i];
	if (ci[_i] == 1000 && _j == 0 || prime[c] == false){
		c = -1;
	}
	return c;
}

void bfs(int fpass,int tpass){
	queue<int> q;
	q.push(fpass);
	memset(check, false, sizeof(bool)* 10001);
	memset(dist, 0, sizeof(int)* 10001);
	check[fpass] = true;
	dist[fpass] = 0;

	while (!q.empty()){
		if (check[tpass] == true)
			break;

		int p = q.front();
		q.pop();

		int temp = p;
		for (int i = 3; i >=0; i--){
			per[i] = temp % 10;
			temp /= 10;
		}

		for (int i = 0; i < 4; i++){
			for (int j = 0; j <= 9; j++){
				int next = change(p,i,j);
				if (next != -1){
					if (check[next] == false){
						q.push(next);
						check[next] = true;
						dist[next] = dist[p] + 1;
					}
				}
			}
		}
	}
}

int main(){
	int T;
	scanf("%d",&T);
	calcPrime();
	for (int test = 0; test < T; test++){
		int fpass,tpass;
		scanf("%d %d",&fpass,&tpass);
		bfs(fpass,tpass);
		printf("%d\n",dist[tpass]);
	}
	return 0;
}