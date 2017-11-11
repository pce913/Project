#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;
vector<int> a[10001];
queue<int> q;
int indegree[10001];
int time[10001];
int w[10001];

int main(){
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++){
		int weight,x;
		scanf("%d %d",&weight,&x);
		w[i] = weight;
		for (int j = 0; j < x; j++){
			int v;
			scanf("%d",&v);
			a[v].push_back(i);
			indegree[i]++;
		}
	}
	for (int i = 1; i <= N; i++){
		if (indegree[i] == 0){
			q.push(i);
		}
	}
	int node=0;
	int ans = 0;
	while (!q.empty()){
		node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next_node=a[node][i];
			indegree[next_node]--;
			if (indegree[next_node] == 0){
				q.push(next_node);
			}
			if (time[next_node] < time[node] + w[node]){
				time[next_node] = time[node] + w[node];
			}
			//printf("next_node %d time %d \n",next_node,time[next_node]);
		}
		if (ans < time[node] + w[node])
			ans = time[node] + w[node];
	}
	
	printf("%d",ans);
	return 0;
}