#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

/*1.D[i][j]: i, j 위치에 왔을때 최대 몇번만에 왔느냐  여기서 세그먼트 트리의 tree로 D를 대체 할 수 있다.
2.각 row와 col마다 segment tree를 만들어 준다.n범위가 작으므로 다 만들 수 있다.
세그먼트 트리에는 DP의 최댓값이 저장되어 있다.
3.처음 시작위치 D[a][b] = 1 로 시작을 한다.나머지 D[i][j] = 0 인 상태일 것이다.
4.먼저 꽃잎을 sort한다.sort하기 위해서는 2차원을 1차원으로 변환해야 할 것이다.좌표 정보를 함께
가지고 있어야함.
5.꽃잎 순서대로 보면서 현재 좌표로 올 수 있는 후보군을 세그먼트 트리에서 가져온다.
6.세그먼트 트리에서 max값을 가져오는것이다.
7.가져온 max값이 0이 아니라면 현재 좌표를 그 max + 1 로 갱신해준다.
8.max값을 가져왔는데 그 값이 0이라고 하면은 갱신해 주지 않는다.
9.max값을 가져와 갱신을 했다면 현재 좌표가 속해있는 row와 col에 대한 트리를 update 시켜준다.
10.주의 할 점이 있는데, 꽃잎의 갯수가 같은 칸들은 update를 한꺼번에 해줘야 한다.
왜냐하면 실시간으로 update 할 경우에는 꽃잎의 갯수가 현재 보고있는 칸과 같은 곳에서
max값을 가져 올 수 있기 때문이다.
1 2 2 3 3 3 4 4 4 4  ...   --> 예를들어 4같은 경우에는 모아 두었다가 한꺼번에 업데이트 해야 한다.*/

struct Flower{
	int x, y, w;
	bool operator<(const Flower& f)const{
		return this->w < f.w;
	}
};

const int MAXN = 1501;
  // D[i][j]: i,j 위치에 왔을때 최대 몇번만에 왔느냐
int sx, sy;
int row_tree[MAXN][4 * MAXN];   //각각의 행에 대해 최대값을 찾는 세그먼트 트리
int col_tree[MAXN][4 * MAXN];   //각각의 열에 대해 최대값을 찾는 세그먼트 트리
vector<Flower> update_list;   //여기서 w: D[i][j] 값.
vector<Flower> flower;  //여기서 w: 각 꽃의 꽃잎의 갯수
int dxr[] = {  1, -1, -1, 1 };  //row 방향
int dyr[] = { -2, -2,  2, 2 };
int dxc[] = { 2, 2, -2, -2 }; // col 방향
int dyc[] = { 1, -1, -1, 1 };
void update(int tree[], int node, int start, int end, int i, int value){
	if (i > end || i < start){
		return;
	}
	tree[node] = max(tree[node], value);
	if (start != end){
		update(tree, 2 * node, start, (start + end) / 2, i, value);
		update(tree, 2 * node + 1, (start + end) / 2 + 1, end, i, value);
	}
}

int query(int tree[], int node, int start, int end, int i, int j){
	if (i > end || j < start){
		return 0;
	}
	if (start >= i && end <= j){
		return tree[node];
	}
	int m1=query(tree, 2 * node, start, (start + end) / 2, i, j);
	int m2=query(tree, 2 * node + 1, (start + end) / 2+1,end , i, j);
	return max(m1, m2);
}

int main(){
	int n;
	int s_petal = 0;
	scanf("%d %d %d", &n, &sx, &sy);
	flower.resize(n*n);   //resize안하고 push_back 하면 메모리 초과 뜸.
	int fm = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			int x;
			scanf("%d", &x);
			if (i == sx && j == sy)
				s_petal = x;
			flower[fm++] = { i, j, x };
		}
	}
	sort(flower.begin(), flower.end());
	
	update_list.push_back({ sx, sy, 1 });
	Flower aa = { 0, 0, s_petal };
	flower.erase(flower.begin(), lower_bound(flower.begin(), flower.end(), aa));   //시작 꽃잎보다 작은 녀석들은 지워주고 시작한다.
	int cur_w;
	if (flower.size()>0)
		 cur_w = flower[0].w;
	for (int i = 0; i < flower.size(); i++){
		int cx = flower[i].x;
		int cy = flower[i].y;
		int cw = flower[i].w;
		if (cw != cur_w){   //꽃잎의 갯수가 같은 녀석들을 한꺼번에 update 해준다.
			for (int k = 0; k < update_list.size(); k++){
				int ux = update_list[k].x;
				int uy = update_list[k].y;
				int uw = update_list[k].w;
				update(row_tree[ux], 1, 1, n, uy, uw);
				update(col_tree[uy], 1, 1, n, ux, uw);
			}
			cur_w = cw;
			update_list.clear();
		}

		int maxi = 0;
		for (int k = 0; k < 4; k++){   // row 방향
			int nx = cx + dxr[k];
			int ny = cy + dyr[k];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				int from, to;
				if (ny < cy){    //왼쪽
					from = 1;
					to = ny;
				}
				else{   // 오른쪽
					from = ny;
					to = n;
				}
				int temp=query(row_tree[nx], 1, 1, n, from, to);
				maxi = max(maxi, temp);
			}
		}
		for (int k = 0; k < 4; k++){  // col 방향
			int nx = cx + dxc[k];
			int ny = cy + dyc[k];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				int from, to;
				if (nx < cx){   //위쪽
					from = 1;
					to = nx;
				}
				else{   // 아래쪽
					from = nx;
					to = n;
				}
				int temp=query(col_tree[ny], 1, 1, n, from, to);
				maxi = max(maxi, temp);
			}
		}

		if (maxi == 0)
			continue;
		update_list.push_back({ cx, cy, maxi+1 });
	}
	if (!update_list.empty()){  //업데이트 할 것들이 남아있다면 마저 해준다.
		for (int k = 0; k < update_list.size(); k++){
			int ux = update_list[k].x;
			int uy = update_list[k].y;
			int uw = update_list[k].w;
			update(row_tree[ux], 1, 1, n, uy, uw);
			update(col_tree[uy], 1, 1, n, ux, uw);
		}
	}

	int ans = 1;
	for (int i = 1; i <= n; i++){
		ans = max( ans,row_tree[i][1]);    //row에서의 최대값만 가져와도 답을 구할 수 있다.
	}
	printf("%d",ans);
	return 0;
}