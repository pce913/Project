#include<stdio.h>
int n;
char w1[25][25], w2[25][25];
long long dist[25][25], sw1[25][25], sw2[25][25];
int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%s", &w1[i]);
	}
	for (int i = 0; i < n; i++){
		scanf("%s", &w2[i]);
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			dist[i][j] = sw1[i][j] = sw2[i][j] = 1e7;
			if (w1[i][j] != '.'){
				dist[i][j] = (w1[i][j]-'0') * (w2[i][j]-'0');
				sw1[i][j] = (w1[i][j] - '0');
				sw2[i][j] = (w2[i][j] - '0');
			}
		}
		dist[i][i] = 0;
	}
	for (int k = 0; k < n; k++){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (dist[i][j] > (sw1[i][k] + sw1[k][j])*(sw2[i][k] + sw2[k][j])){
					dist[i][j] = (sw1[i][k] + sw1[k][j])*(sw2[i][k] + sw2[k][j]);
					sw1[i][j] = sw1[i][k] + sw1[k][j];
					sw2[i][j] = sw2[i][k] + sw2[k][j];
				}
			}
		}
	}
	long long ans = dist[0][1];
	if (ans == 1e7){
		ans = -1;
	}
	printf("%lld",ans);
	return 0;
}
//#include<stdio.h>
//#include<queue>
//using namespace std;
//
//struct Edge{
//	int to, cost1, cost2;
//	bool operator<(const Edge& e)const{
//		return cost1*cost2 > e.cost1*e.cost2;
//	}
//};
//int n;
//int dist[25];
//char w1[25][25], w2[25][25];
//void dijkstra(int start){
//	priority_queue<Edge> q;
//	dist[start] = 0;
//	q.push({ start, 0, 0 });
//	while (!q.empty()){
//		auto p = q.top();
//		q.pop();
//		int node = p.to;
//		int cost1 = p.cost1;
//		int cost2 = p.cost2;
//		if (cost1*cost2 > dist[node])
//			continue;
//		for (int next = 0; next < n; next++){
//			if (w1[node][next] != '.'){
//				if (dist[next] > (cost1+(w1[node][next]-'0')) * (cost2+(w2[node][next]-'0'))){
//					dist[next] = (cost1 + (w1[node][next] - '0')) * (cost2 + (w2[node][next] - '0'));
//					q.push({ next, (cost1 + (w1[node][next] - '0')) , (cost2 + (w2[node][next] - '0')) });
//				}
//			}
//		}
//	}
//}
//
//int main(){
//	scanf("%d",&n);
//	for (int i = 0; i < n; i++){
//		scanf("%s",&w1[i]);
//		dist[i] = 1e9;
//	}
//	for (int i = 0; i < n; i++){
//		scanf("%s", &w2[i]);
//	}
//	dijkstra(0);
//	int ans = dist[1];
//	if (ans == 1e9)
//		ans = -1;
//	printf("%d",ans);
//	return 0;
//}