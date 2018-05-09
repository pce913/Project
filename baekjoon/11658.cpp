#include<stdio.h>
#include<algorithm>
using namespace std;

int tree[4*1030][4*1030];          //2차원 세그먼트 트리 사용
int M[1030][1030];
int n, m;

void update(int tree[],int node,int start,int end,int i,int value){
	if (i > end || i < start){
		return;
	}
	tree[node] += value;
	if (start != end){
		update(tree, 2 * node, start, (start + end) / 2, i, value);
		update(tree, 2 * node + 1, (start + end) / 2+1,end , i, value);
	}
}

void update2d(int node,int start,int end,int x,int y,int value){
	if (x > end || x < start){
		return;
	}
	update(tree[node], 1, 1, n, y, value);
	if (start != end){
		update2d(2 * node, start, (start + end) / 2, x, y, value);
		update2d(2 * node + 1, (start + end) / 2+1,end , x, y, value);
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
	return m1 + m2;
}

int query2d(int node,int start,int end,int xi,int xj,int yi,int yj){   //먼저 x위치를 좁힌 후에
	if (xi > end || xj < start){
		return 0;
	}
	if (start >= xi && end <= xj){
		return query(tree[node], 1, 1, n, yi, yj);   // y 위치까지 좁힌 후 구간 합을 가져온다.
	}
	int m1=query2d(2 * node, start, (start + end) / 2, xi, xj, yi, yj);
	int m2=query2d(2 * node + 1, (start + end) / 2+1,end , xi, xj, yi, yj);
	return m1 + m2;
}

//void init(int tree[], int x ,int node, int start, int end){
//	if (start == end){
//		tree[node] = M[x][start];
//		return;
//	}
//	init(tree, x ,2 * node, start, (start + end) / 2);
//	init(tree, x, 2 * node + 1, (start + end) / 2+1,end );
//	tree[node] = tree[2 * node] + tree[2 * node + 1];
//}
//
//void init2d(int node,int start,int end){
//	if (start == end){
//		init(tree[node], start,1, 1, n);
//		return;
//	}
//	init2d(2 * node, start, (start + end) / 2);
//	init2d(2 * node+1, (start + end) / 2+1, end);
//	for (int x = start; x <= end; x++){
//		init(tree[node], x,1, 1, n);
//	}
//}


int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d", &M[i][j]);
			update2d(1, 1, n, i, j, M[i][j]);
		}
	}
	//init2d(1, 1, n);
	for (int qq = 0; qq < m; qq++){
		int w;
		scanf("%d", &w);
		if (w == 0){    //update
			int x, y, c;
			scanf("%d %d %d", &x, &y, &c);
			int value = c - M[x][y];
			update2d(1, 1, n, x, y, value);
			M[x][y] = c;
		}
		else{   //query
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 > x2)
				swap(x1, x2);
			if (y1 > y2)
				swap(y1, y2);
			printf("%d\n",query2d(1,1,n,x1,x2,y1,y2));
		}
	}
	return 0;
}

//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//int tree[1030][1030];
//int M[1030][1030];
//int n, m;
//void update(int x,int y,int value){
//	for (int i = x; i <= n; i+=i&-i){
//		for (int j = y; j <= n; j+=j&-j){
//			tree[i][j] += value;
//		}
//	}
//}
//
//int query(int x,int y){
//	int ans = 0;
//	for (int i = x; i > 0; i-=i&-i){
//		for (int j = y;j > 0; j -= j&-j){
//			ans += tree[i][j];
//		}
//	}
//	return ans;
//}
//
//int main(){
//	scanf("%d %d",&n,&m);
//	for (int i = 1; i <= n; i++){
//		for (int j = 1; j <= n; j++){
//			scanf("%d",&M[i][j]);
//			update(i, j, M[i][j]);
//		}
//	}
//	for (int qq = 0; qq < m; qq++){
//		int w;
//		scanf("%d",&w);
//		if (w == 0){    //update
//			int x, y, c;
//			scanf("%d %d %d",&x,&y,&c);
//			update(x, y, c - M[x][y]);
//			M[x][y] = c;
//		}
//		else{   //query
//			int x1, y1, x2, y2;
//			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
//			if (x1 > x2)
//				swap(x1, x2);
//			if (y1 > y2)
//				swap(y1, y2);
//			printf("%d\n",query(x2,y2)-query(x2,y1-1)-query(x1-1,y2)+query(x1-1,y1-1));
//		}
//	}
//	return 0;
//}