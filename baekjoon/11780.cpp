//#include<stdio.h>
//#include<stack>
//using namespace std;
//int dist[101][101];
//pair<int,int> v[101][101];
//
//int main(){
//	const int INF = 100000000;
//	int n, m;
//	scanf("%d", &n);
//	scanf("%d", &m);
//	for (int i = 1; i <= n; i++){
//		//v[i][i] = {i,i};
//		for (int j = 1; j <= n; j++){
//			dist[i][j] = INF;
//		}
//	}
//
//	for (int i = 1; i <= m; i++){
//		int x, y, z;
//		scanf("%d %d %d", &x, &y, &z);
//		if (dist[x][y] > z){
//			dist[x][y] = z;
//		}
//	}
//
//	for (int k = 1; k <= n; k++){
//		for (int i = 1; i <= n; i++){
//			for (int j = 1; j <= n; j++){
//				if (dist[i][j] > dist[i][k] + dist[k][j]){
//					dist[i][j] = dist[i][k] + dist[k][j];
//					v[i][j] = { i, k };
//					if (i == 4 && j == 3){
//						printf("i==4 j==3 k : %d\n", k);
//						printf("dist[5][4] : %d\n",dist[5][4]);
//					}
//				}
//			}
//		}
//	}
//	printf("v[5][3] : %d %d\n", v[5][3].first, v[5][3].second);
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= n; j++){
//			if (i == j)
//				dist[i][j] = 0;
//			printf("%d ", dist[i][j]);
//		}
//		printf("\n");
//	}
//
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= n; j++){
//			if (i == j){
//				printf("0\n");
//				continue;
//			}
//			stack<int> s;
//			int from=i;
//			int to = j;
//			do{
//				s.push(to);
//				if (from == 5 && to == 3){
//					printf("asd v[5][3] : %d %d\n", v[from][to].first, v[from][to].second);
//				}
//				from = v[from][to].first;
//				to = v[from][to].second;
//			} while (from != 0 && to != 0);
//			s.push(i);
//
//			printf("%d ",s.size());
//			while (!s.empty()){
//				printf("%d ",s.top());
//				s.pop();
//			}
//			printf("\n");
//		}
//	}
//
//	return 0;
//}
//#include<stdio.h>
//#include<queue>
//using namespace std;
//int dist[101][101];
//pair<int, int> v[101][101];
//
//int main(){
//	const int INF = 100000000;
//	int n, m;
//	scanf("%d", &n);
//	scanf("%d", &m);
//	for (int i = 1; i <= n; i++){
//		//v[i][i] = {i,i};
//		for (int j = 1; j <= n; j++){
//			dist[i][j] = INF;
//		}
//	}
//
//	for (int i = 1; i <= m; i++){
//		int x, y, z;
//		scanf("%d %d %d", &x, &y, &z);
//		if (dist[x][y] > z){
//			dist[x][y] = z;
//		}
//	}
//
//	for (int k = 1; k <= n; k++){
//		for (int i = 1; i <= n; i++){
//			for (int j = 1; j <= n; j++){
//				if (dist[i][j] > dist[i][k] + dist[k][j]){
//					dist[i][j] = dist[i][k] + dist[k][j];
//					v[i][j] = { i, k };
//					if (i == 2 && j == 3){
//						printf("i==2 j==3 k : %d\n", k);
//						printf("dist[2][3] : %d\n", dist[2][3]);
//					}
//				}
//			}
//		}
//	}
//	printf("dist[2][3], dist[2][4], dist[4][3] %d %d %d\n",dist[2][3], dist[2][4], dist[4][3]);
//	printf("v[5][3] : %d %d\n", v[5][3].first, v[5][3].second);
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= n; j++){
//			if (i == j)
//				dist[i][j] = 0;
//			printf("%d ", dist[i][j]);
//		}
//		printf("\n");
//	}
//
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= n; j++){
//			if (i == j){
//				printf("0\n");
//				continue;
//			}
//			queue<int> q;
//			int from = i;
//			int to = j;
//			//q.push(from);
//
//			/*do{
//				if (from == 5 && to == 3){
//					printf("asd v[5][3] : %d %d\n", v[from][to].first, v[from][to].second);
//				}
//				from = v[from][to].first;
//				to = v[from][to].second;
//			} while (from != 0 && to != 0);*/
//
//			//while (from != 0 && to != 0){
//			//	//from = v[from][to].first;
//			//	from = v[from][to].second;
//			//	q.push(from);
//			//}
//			do{
//				q.push(from);
//				from = v[from][to].second;
//			}while (from != 0 && to != 0);
//			q.push(j);
//
//			printf("%d ", q.size());
//			while (!q.empty()){
//				printf("%d ", q.front());
//				q.pop();
//			}
//			printf("\n");
//		}
//	}
//
//	return 0;
//}
#include<stdio.h>
#include<queue>
using namespace std;
int dist[101][101];
int v[101][101];

int main(){
	const int INF = 100000000;
	int n, m;
	scanf("%d", &n);
	scanf("%d", &m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			dist[i][j] = INF;
			v[i][j] = -1;
		}
	}

	for (int i = 1; i <= m; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		if (dist[x][y] > z){
			dist[x][y] = z;
		}
		v[x][y] = y;
	}

	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (dist[i][j] > dist[i][k] + dist[k][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
					v[i][j]= v[i][k];
				}
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (i == j){
				dist[i][j] = 0;
				v[i][j] = -1;
			}
			printf("%d ", dist[i][j]);
		}
		printf("\n");
	}

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (i == j){
				printf("0\n");
				continue;
			}
			queue<int> q;
			int from = i;
			int to = j;
			q.push(from);

			while (v[from][to] != -1){
				from = v[from][to];
				q.push(from);
			}
			printf("%d ", q.size());
			while (!q.empty()){
				printf("%d ", q.front());
				q.pop();
			}
			printf("\n");
		}
	}
	return 0;
}