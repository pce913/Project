#include<stdio.h>
#include<vector>
#include<queue>
#include <functional> 
using namespace std;
vector<int> a[32001];
int indegree[32001];
priority_queue<int, vector<int>, greater<int> > q;

int main(){
	int N, M;
	scanf("%d %d",&N,&M);
	for (int i = 1; i <= M; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		indegree[y]++;
	}
	for (int i = 1; i <= N; i++){
		if (indegree[i] == 0){
			q.push(i);
		}
	}
	while (!q.empty()){
		int node = q.top();
		q.pop();
		printf("%d ",node);
		for (int i = 0; i < a[node].size(); i++){
			int next=a[node][i];
			indegree[next]--;
			if (indegree[next] == 0){
				q.push(next);
			}
		}
	}
	return 0;
}