#include<stdio.h>
int a[500005], tree[2000005];
int n;
void init(int node,int start,int end){
	if (start == end){
		tree[node] = a[start];
		return;
	}
	init(2 * node, start, (start + end) / 2);
	init(2 * node + 1, (start + end) / 2+1,end );
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node,int start,int end,int i,int value){
	if (i > end || i < start)
		return;
	if (start == end){
		tree[node] += value;
		return;
	}
	update(2 * node, start, (start + end) / 2, i, value);
	update(2 * node + 1, (start + end) / 2+1,end , i, value);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node,int start,int end,int value){
	if (start == end)
		return start;
	if (value <= tree[2 * node]){
		return query(2 * node, start, (start + end) / 2, value);
	}
	else{
		return query(2 * node + 1, (start + end) / 2 + 1, end, value - tree[2 * node]);
	}
}

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	init(1, 1, n);
	int m;
	scanf("%d", &m);
	for (int qq = 0; qq < m; qq++){
		int x;
		scanf("%d", &x);
		if (x == 1){
			int y, v;
			scanf("%d %d", &y, &v);
			update(1, 1, n, y, v);
		}
		else{
			int v;
			scanf("%d", &v);
			printf("%d\n",query(1,1,n,v));
		}
	}
	return 0;
}
//#include<stdio.h>
//int a[500005], tree[500005];
//int n;
//void update(int x,int value){
//	for (int i = x; i <= n; i += i&-i){
//		tree[i] += value;
//	}
//}
//
//int query(int x){
//	int ans = 0;
//	for (int i = x; i > 0; i -= i&-i){
//		ans += tree[i];
//	}
//	return ans;
//}
//
//int main(){
//	scanf("%d",&n);
//	for (int i = 1; i <= n; i++){
//		scanf("%d",&a[i]);
//		update(i, a[i]);
//	}
//	int m;
//	scanf("%d",&m);
//	for (int qq = 0; qq < m; qq++){
//		int x;
//		scanf("%d",&x);
//		if (x == 1){
//			int y, v;
//			scanf("%d %d",&y,&v);
//			update(y, v);
//		}
//		else{
//			int v;
//			scanf("%d",&v);
//			int left = 1;
//			int right = n;
//			int ans = 0;
//			while (left <= right){
//				int mid = (left + right) >> 1;  //ºÎ´ë
//				if (v> query(mid - 1) && v <= query(mid)){
//					ans = mid;
//					break;
//				}
//				else if (v > query(mid)){
//					left = mid + 1;
//				}
//				else{
//					right = mid - 1;
//				}
//			}
//			printf("%d\n",ans);
//		}
//	}
//	return 0;
//}