#include<stdio.h>
#include<queue>
using namespace std;

#define MAX 200001
bool check[MAX];
int dist[MAX];

void bfs(int N,int K){
	queue<int> q;
	q.push(N);
	check[N] = true;
	dist[N] = 0;
	while (!q.empty()){
		if (check[K] == true)
			break;

		int p=q.front();
		q.pop();
		int next[3] = {p+1,p-1,2*p};
		for (int i = 0; i < 3; i++){
			if (next[i] >= 0 && next[i] <= MAX){
				if (check[next[i]] == false){
					q.push(next[i]);
					check[next[i]] = true;
					dist[next[i]] = dist[p] + 1;
				}
			}	
		}
	}
}

int main(){
	int N, K;
	scanf("%d %d",&N,&K);
	bfs(N, K);
	printf("%d",dist[K]);
	return 0;
}