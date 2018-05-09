#include<stdio.h>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

   //동시에 여러 건물을 지을 수 있음.
vector<int> a[502];
int timee[502];
int stimee[502];
int indegree[502];

int ans[502];
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		int t;
		int x;
		scanf("%d", &t);
		timee[i] = t;
		while (true){
			int x;
			scanf("%d", &x);
			if (x == -1)break;
			a[x].push_back(i);
			indegree[i]++;
		}
	}

	queue<int> q;
	for (int i = 1; i <= n; i++){
		if (indegree[i] == 0){
			q.push(i);
			ans[i] += timee[i];
		}
	}
	for (int i = 1; i <= n; i++)stimee[i] = timee[i];

	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next = a[node][i];
			indegree[next]--;
			stimee[next] = max(stimee[next], stimee[node] + timee[next]);
			if (indegree[next] == 0){
				q.push(next);			
				ans[next] += stimee[next];
			}
		}
	}

	for (int i = 1;i<=n;i++)
		printf("%d\n",ans[i]);

	return 0;
}