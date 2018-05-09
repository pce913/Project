#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;
int parent[100001];
bool check[100001];
vector<int> A[100001];
void bfs(int x){
	check[x] = true;
	queue<int> q;
	q.push(x);
	while (!q.empty()){
		int node=q.front();
		q.pop();
		for (int i = 0; i < A[node].size(); i++){
			int next = A[node][i];
			if (check[next] == false){
				check[next] = true;
				parent[next] = node;
				q.push(next);
			}
		}
	}
}

int main(){
	int N;
	int a, b;
	scanf("%d", &N);
	for (int i = 0; i < N - 1; i++){
		scanf("%d %d",&a,&b);
		A[a].push_back(b);
		A[b].push_back(a);
	}
	bfs(1);
	for (int i = 2; i <= N; i++)
		printf("%d\n",parent[i]);
	return 0;
}