#include<stdio.h>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
int n;

struct Mat{
	vector< vector<int> > M;
	int dist;
};
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
bool check[30][30];
int ans;
queue<Mat> q;
bool canGo(int nx,int ny, int i){
	return nx + dx[i] >= 0 && nx + dx[i] <= n - 1 && ny + dy[i] >= 0 && ny + dy[i] <= n - 1;
}

void solve(vector< vector<int> >& T,int i,int j,int r){
	int cx = i;
	int cy = j;
	int nx = i;
	int ny = j;
	while (canGo(nx, ny, r) && T[nx + dx[r]][ny + dy[r]] == 0){
		nx += dx[r];
		ny += dy[r];
	}
	if (canGo(nx, ny, r) && T[nx + dx[r]][ny + dy[r]] == T[cx][cy] && !check[nx + dx[r]][ny + dy[r]]){   //두번째 방문하는 녀석들. 즉, 겹치는 녀석들을
		T[nx + dx[r]][ny + dy[r]] = 2 * T[cx][cy];                                          //check 배열로 관리해 준다.
		T[cx][cy] = 0;
		check[nx + dx[r]][ny + dy[r]] = true;
	}
	else{
		//T[nx][ny] = T[cx][cy];
		//T[cx][cy] = 0;
		swap(T[nx][ny], T[cx][cy]);   //위의 while문에 한번도 안걸릴 경우, T[nx][ny] == T[cx][cy] 이므로 T[cx][cy]=0 하면 틀릴 수 있다.
	}
}

void bfs(vector< vector<int> >& start){
	q.push({ start ,0 });
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		auto M = p.M;
		int dist = p.dist;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				ans = max(ans, M[i][j]);
			}
		}

		if (dist >= 6)
			break;

		for (int r = 0; r < 4; r++){
			memset(check, 0, sizeof(check));
			auto T = M;
			if (r == 0){
				for (int i = n - 1; i >= 0; i--){
					for (int j = 0; j <= n - 1; j++){
						solve(T, i, j, r);
					}
				}
			}
			else if (r == 1){
				for (int i = 0; i <= n - 1; i++){
					for (int j = 0; j <= n - 1; j++){
						solve(T, i, j, r);
					}
				}
			}
			else if (r == 2){
				for (int i = 0; i < n; i++){
					for (int j = 0; j < n; j++){
						solve(T, i, j, r);
					}
				}
			}
			else if (r == 3){
				for (int i = 0; i <= n - 1; i++){
					for (int j = n - 1; j >= 0; j--){
						solve(T, i, j, r);
					}
				}
			}
			
			q.push({ T, dist + 1 });
		}
	}

}

int main(){
	scanf("%d",&n);
	vector< vector<int> > a(n,vector<int>(n));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			scanf("%d",&a[i][j]);
		}
	}
	bfs(a);
	printf("%d",ans);
	return 0;
}

//#include<stdio.h>
//#include<queue>
//#include<algorithm>
//#include<vector>
//using namespace std;
//struct Point{
//	int x, y;    //이전에 어느방향에서 왔는지에 대한 정보가 있어야 한다.
//};
//int dx[] = { 1, 0, -1, 0 };//아래 왼쪽 위 오른쪽
//int dy[] = { 0, -1, 0, 1 };
//
//int rdx[] = { -1, 0, 1, 0 };
//int rdy[] = { 0, 1, 0, -1 };
//
//int n;
//int a[30][30];
//int check[30][30];   //어떤 칸에 어떤 숫자가 들어가있는가.
//int cnt[30][30];   //어떤 칸에 몇개가 겹치는가
//
//int M[10][5][30][30];
//queue<Point> q;
//vector<Point> v;
//
//void bfs(){
//	int cdist = 0;
//	while (!q.empty()){   //true여도 상관 없을것 같다.
//		if (cdist >= 6)
//			break;
//
//		v.clear();
//
//		while (!q.empty()){   //여기 수정해야 할듯.  이전에 어느 방향에서 왔는지에 대한 정보가 필요하다.
//			v.push_back(q.front());
//			q.pop();
//		}
// 		for (int i = 0; i < 4; i++){  //아래 왼쪽 위 오른쪽
//			memset(check, 0, sizeof(check));
//			memset(cnt, 0, sizeof(cnt));
//			for (auto p : v){
//				int cx = p.x;
//				int cy = p.y;
// 				int nx = cx;
//				int ny = cy;
//				//int cdist = p.dist;
//
//			
//				while (nx + dx[i] >= 1 && nx + dx[i] <= n && ny + dy[i] >= 1 && ny + dy[i] <= n && (M[cdist][i][nx + dx[i]][ny + dy[i]] == 0 || M[cdist][i][nx + dx[i]][ny + dy[i]] == M[cdist][i][cx][cy])){
//					nx += dx[i];
//					ny += dy[i];
//				}
// 				check[nx][ny] = M[cdist][i][cx][cy];
//				cnt[nx][ny]++;
//			}
//			//분배하는과정 넣어야함.
//			
// 			for (int k = 1; k <= n; k++){ 
//				if (i == 0){    //위로 올라가며 분배
//					int j = n;
//					int w = n;
//					while (j >= 1){
//						if (cnt[w][k] == 1){
//							M[cdist+1][i][j][k] = check[w][k];
//							q.push({ j, k });
//							j--;
//							w -= cnt[w][k];
//						}
//						else if (cnt[w][k] == 2){
//							M[cdist+1][i][j][k] = 2 * check[w][k];
//							q.push({ j, k });
//							j--;
//							w -= cnt[w][k];
//						}
//						else if(cnt[w][k]>=3){
//							M[cdist+1][i][j][k] = 2 * check[w][k];
//							q.push({ j, k });
//							int num = check[w][k];
//							int recur_cnt = cnt[w][k]-2;
//							j--;
//							w -= cnt[w][k];
//							while (recur_cnt--){
//								M[cdist+1][i][j][k] = num;
//								q.push({ j, k });
//								j--;
//							}
//						}
//						else{
//							j--;
//						}
//					}
//				}
//				else if (i == 1){ // 오른쪽으로 가면서 분배
//					int j = 1;
//					int w = 1;
//					while (j <= n){
//						if (cnt[k][w] == 1){
//							M[cdist + 1][i][k][j] = check[k][w];
//							q.push({ k, j });
//							j++;
//							w += cnt[k][w];
//						}
//						else if (cnt[k][w] == 2){
//							M[cdist+1][i][k][j] = 2 * check[k][w];
//							q.push({ k, j });
//							j++;
//							w += cnt[k][w];
//						}
//						else if (cnt[k][w]>=3){
//							M[cdist + 1][i][k][j] = 2 * check[k][w];
//							q.push({ k, j });
//							int num = check[k][w];
//							int recur_cnt = cnt[k][w]-2;
//							j++;
//							w += cnt[k][w];
//							while (recur_cnt--){
//								M[cdist + 1][i][k][j] = num;
//								q.push({ k, j });
//								j++;
//							}
//						}
//						else{
//							j++;
//						}
//					}
//				}
//				else if (i == 2){   //아래로 내려가며 분배
//					int j = 1;
//					int w = 1;
//					while (j <= n){
//						if (cnt[w][k] == 1){
//							M[cdist + 1][i][j][k] = check[w][k];
//							q.push({ j, k });
//							j++;
//							w += cnt[w][k];
//						}
//						else if (cnt[w][k] == 2){
//							M[cdist + 1][i][j][k] = 2*check[w][k];
//							q.push({ j, k });
//							j++;
//							w += cnt[w][k];
//						}
//						else if (cnt[w][k] >= 3){
//							M[cdist + 1][i][j][k] = 2 * check[w][k];
//							q.push({ j, k });
//							int num = check[w][k];
//							int recur_cnt = cnt[w][k] - 2;
//							j++;
//							w += cnt[w][k];
//							while (recur_cnt--){
//								M[cdist + 1][i][j][k] = num;
//								q.push({ j, k });
//								j++;
//							}
//						}
//						else{
//							j++;
//						}
//					}
//				}
//				else if (i == 3){  //왼쪽으로 가면서 분배
//					int j = n;
//					int w = n;
//					while (j >= 1){
//						if (cnt[k][w] == 1){
//							M[cdist + 1][i][k][j] = check[k][w];
//							q.push({ k, j });
//							j--;
//							w -= cnt[k][w];
//						}
//						else if (cnt[k][w] == 2){
//							M[cdist + 1][i][k][j] = 2 * check[k][w];
//							q.push({ k, j });
//							j--;
//							w -= cnt[k][w];
//						}
//						else if (cnt[k][w] >= 3){
//							M[cdist + 1][i][k][j] = 2 * check[k][w];
//							q.push({ k, j });
//							int num = check[k][w];
//							int recur_cnt = cnt[k][w]-2;
//							j--;
//							w -= cnt[k][w];
//							while (recur_cnt--){
//								M[cdist + 1][i][k][j] = num;
//								q.push({ k, j });
//								j--;
//							}
//						}
//						else{
//							j--;
//						}
//					}
//				}
//
//			}
//			//
//		}
//
//
//		cdist++;
//	}
//	
//}
//
//
//int main(){
//	scanf("%d",&n);
//	for (int i = 1; i <= n; i++){
//		for (int j= 1; j <= n; j++){
//			scanf("%d",&a[i][j]);
//			if (a[i][j] != 0){
//				q.push({ i, j});
//			}
//		}
//	}
//	for (int k = 0; k < 4; k++){
//		for (int i = 1; i <= n; i++){
//			for (int j = 1; j <= n; j++){
//				M[0][k][i][j] = a[i][j];
//			}
//		}
//	}
//	bfs();
//
//	int ans = 0;
//	for (int k = 0; k < 4; k++){
//		for (int i = 1; i <= n; i++){
//			for (int j = 1; j <= n; j++){
//				ans = max(ans, M[5][k][i][j]);
//				printf("%d ", M[2][k][i][j]);
//			}
//			printf("\n");
//		}
//		printf("\n");
//	}
//	printf("%d",ans);
//	return 0;
//}