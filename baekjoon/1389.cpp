#include<stdio.h>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

vector<int> a[101];
int relation[101][101];
bool check[101];

int bfs(int start){
	check[start] = true;
	queue<int> q;
	q.push(start);
	int cavin = 0;
	while (!q.empty()){		
		int node=q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next=a[node][i];
			if (!check[next]){
				check[next] = true;
				relation[start][next] = relation[start][node] + 1;
				cavin += relation[start][node] + 1;
				q.push(next);
			}
			else{
				if (relation[start][next] > relation[start][node] + 1){
					cavin = cavin - relation[start][next] +(relation[start][node] + 1);
					relation[start][next] = relation[start][node] + 1;
				}
			}
		}
	}
	return cavin;
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	int distance = 1000000000;
	int ans = 0;
	for (int i = 1; i <= n; i++){
		memset(check, false, sizeof(check));
		int temp=bfs(i);
		if (distance > temp){
			distance = temp;
			ans = i;
		}
			
	}
	printf("%d",ans);
	return 0;
}