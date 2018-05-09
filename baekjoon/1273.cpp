#include<stdio.h>
#include<algorithm>
using namespace std;
const int MAXH = 3300000;
int sum[MAXH+5];   //높이 300만개로 잡아.
int color[3][300005];
int tree[4 * MAXH];
int mheight;

void init(int node,int start,int end){
	if (start == end){
		tree[node] = 1;
		return;
	}
	init(2 * node, start, (start + end) / 2);
	init(2 * node + 1, (start + end) / 2 + 1, end);
	tree[node] = tree[2*node] + tree[2*node+1];
}

void update(int node,int start,int end,int i,int value){  //value에 0 넣어주자.
	if (i > end || i < start)
		return;
	if (start == end){
		tree[node] = value;
		return;
	}
	update(2 * node, start, (start + end) / 2, i, value);
	update(2 * node + 1, (start + end) / 2 + 1, end, i, value);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int start, int end, int k){  //실제 인덱스 찾는 쿼리. 조세퍼스 문제2 참조.
	if (start == end && k == 1){
		return start;
	}
	else if (start == end && k != 1){   //내가 보고 있는 범위에 답이 없는 경우를 처리해야 한다.
		return -1;
	}
	if (k <= tree[2 * node]){
		return query(2 * node, start, (start + end) / 2, k);
	}
	else{
		return query(2 * node + 1, (start + end) / 2 + 1, end, k - tree[2 * node]);
	}
}

int main(){
	freopen("konzerve.in.1","r",stdin);
	int n, m;
	scanf("%d",&n);
	for (int i = 0; i < 3; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d", &color[i][j]);
		}
	}

	for (int i = 1; i <= n; i++){ //2차원 mark 기법
		sum[1] += 1;
		sum[min(color[0][i] + 1,MAXH )] -= 1;
		sum[min(color[0][i] + 1, MAXH)] += 2;
		sum[min(color[0][i] + color[1][i] + 1, MAXH)] -= 2;
		sum[min(color[0][i] + color[1][i] + 1, MAXH)] += 5;
		sum[min(color[0][i] + color[1][i] + color[2][i] + 1, MAXH)] -= 5;
		mheight = max(mheight, min(color[0][i] + color[1][i] + color[2][i], MAXH));
	}
	for (int i = 1; i <= mheight; i++){
		sum[i] += sum[i - 1];
	}
	scanf("%d", &m);

	init(1, 1, mheight);
	for (int q = 0; q < m; q++){
		int x;
		scanf("%d",&x);
		int idx = query(1, 1, mheight, x);
		if (idx == -1){
			printf("0\n");
		}
		else{
			printf("%d\n", sum[idx]);
			update(1, 1, mheight, idx, 0);
		}
	}
	return 0;
}
