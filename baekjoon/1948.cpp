#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;
vector< pair<int, int> > a[10001];
vector< pair<int, int> > r[10001];
queue<int> q;
int indegree[10001];
int rindegree[10001];
int time[10001];
bool isCritical[10001];
                        //배열을 추가해서 임계경로가 아닌애들을 체크해준다.

int main(){                        // 정방향 그래프로 weight 12를 구한후 
	int n, m;                      // 역방향 그래프로 지나야 하는 엣지를 구한다.
	int start, end;
	scanf("%d",&n);
	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		a[x].push_back(make_pair(y,z));
		r[y].push_back(make_pair(x,z));
		indegree[y]++;
		rindegree[x]++;
	}
	
	scanf("%d %d",&start,&end);
	q.push(start);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < a[node].size(); i++){
			int next=a[node][i].first;
			indegree[next]--;
			if (indegree[next] == 0){
				q.push(next);
			}
			if (time[next] < time[node] + a[node][i].second){  
				time[next] = time[node] + a[node][i].second;
			}
		}
		
	}
	printf("%d\n", time[end]);

	int cnt = 0;
	q.push(end);
	isCritical[end] = true;
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < r[node].size(); i++){
			int next = r[node][i].first;
			rindegree[next]--;
			if (rindegree[next] == 0){    //q에는 일단 다 넣어줘야 한다. 그렇지 않으면 예외가 있음.    && time[node] - r[node][i].second == time[next]
				q.push(next);
			}
			
			if (time[node] - r[node][i].second == time[next] && isCritical[node]==true){
				cnt++;
				isCritical[next] = true;
			}
		}
	}
	printf("%d",cnt);
	
	return 0;
}