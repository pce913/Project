#include<stdio.h>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
int dist[100001];
vector< pair<int,int> > A[100001];
void bfs(int x){
	dist[x] = -1;
	queue<int> q;
	q.push(x);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < A[node].size(); i++){
			int next = A[node][i].first;
			if (dist[next]==0){
				dist[next] = dist[node] + A[node][i].second;
				q.push(next);
			}
		}
	}
}

int main(){
	int N;
	scanf("%d", &N);

	for (int i = 1; i <= N; i++){
		int a, b,c;
		scanf("%d", &a);
		while (true){
			scanf("%d", &b);
			if (b == -1)
				break;
			scanf("%d", &c);
			A[a].push_back(make_pair(b, c));
		}
	}
	bfs(1);
	int far=1;
	int max = dist[1];
	for (int i = 2; i <= N; i++){
		if (max < dist[i]){
			max = dist[i];
			far = i;
		}
	}
	memset(dist,0,sizeof(dist));
	bfs(far);

	max = dist[1];
	for (int i = 2; i <= N; i++){
		if (max < dist[i])
			max = dist[i];
	}
	printf("%d",max+1);
	return 0;
}