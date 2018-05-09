//#include <cstdio>
//#include <algorithm>
//#include <vector>
//#include <cstring>
//#define MAX_K 100000
//#define INF 1100000000
//using namespace std;
//int t, n, k, l, xseg[12 * MAX_K], yseg[12 * MAX_K], res[MAX_K];
//struct laser {
//	int x, y;
//};
//struct ship {
//	int x1, y1, x2, y2, m;
//};
//laser lsr[MAX_K];
//ship sp[MAX_K];
//vector<int> xpos;
//vector<int> ypos;
//int update(int *seg, int pos, int val, int node, int x, int y) {
//	if (y < pos || pos < x)
//		return seg[node];
//	if (x == y)
//		return seg[node] = val;
//	int mid = (x + y) >> 1;
//	return seg[node] = min(update(seg, pos, val, node * 2, x, mid), update(seg, pos, val, node * 2 + 1, mid + 1, y));
//}
//int query(int *seg, int lo, int hi, int node, int x, int y) {
//	if (y < lo || hi < x)
//		return INF;
//	if (lo <= x&&y <= hi)
//		return seg[node];
//	int mid = (x + y) >> 1;
//	return min(query(seg, lo, hi, node * 2, x, mid), query(seg, lo, hi, node * 2 + 1, mid + 1, y));
//}
//int get_xpos(int val) {
//	return lower_bound(xpos.begin(), xpos.end(), val) - xpos.begin();
//}
//int get_ypos(int val) {
//	return lower_bound(ypos.begin(), ypos.end(), val) - ypos.begin();
//}
//int main() {
//	scanf("%d", &t);
//	while (t--) {
//		memset(xseg, 0, sizeof(xseg));
//		memset(yseg, 0, sizeof(yseg));
//		memset(res, 0, sizeof(res));
//		xpos.clear();
//		ypos.clear();
//		scanf("%d%d%d", &n, &k, &l);
//		for (int i = 0; i < k; i++) {
//			int a, b, c, d, e;
//			scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
//			xpos.push_back(a);
//			xpos.push_back(c);
//			ypos.push_back(b);
//			ypos.push_back(d);
//			sp[i] = { min(a, c), min(b, d), max(a, c), max(b, d), e };
//		}
//		for (int i = 0; i < l; i++) {
//			int a, b;
//			scanf("%d%d", &a, &b);
//			if (b)
//				xpos.push_back(a);
//			else
//				ypos.push_back(a);
//			lsr[i] = { a, b };
//		}
//		sort(xpos.begin(), xpos.end());
//		sort(ypos.begin(), ypos.end());
//		xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
//		ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
//		const int MAX_X = xpos.size();
//		const int MAX_Y = ypos.size();
//		for (int i = 0; i < MAX_X; i++)
//			update(xseg, i, INF, 1, 0, MAX_X - 1);
//		for (int i = 0; i < MAX_Y; i++)
//			update(yseg, i, INF, 1, 0, MAX_Y - 1);
//
//		for (int i = 0; i < MAX_X; i++)
//			printf("%d\n", xseg[i]);
//		
//
//		for (int i = l - 1; i >= 0; i--) {
//			if (lsr[i].y)
//				update(xseg, get_xpos(lsr[i].x), i, 1, 0, MAX_X - 1);
//			else
//				update(yseg, get_ypos(lsr[i].x), i, 1, 0, MAX_Y - 1);
//		}
//		for (int i = 0; i < k; i++) {
//			int idx = min(query(xseg, get_xpos(sp[i].x1), get_xpos(sp[i].x2), 1, 0, MAX_X - 1), query(yseg, get_ypos(sp[i].y1), get_ypos(sp[i].y2), 1, 0, MAX_Y - 1));
//			if (idx == INF)continue;
//			res[idx] = max(res[idx], sp[i].m);
//		}
//		for (int i = 0; i < l; i++) {
//			printf("%d\n", res[i]);
//		}
//	}
//	return 0;
//}

#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#include<cmath>
using namespace std;

const int INF = 1e9;

struct Ship{
	int x1, y1, x2, y2, w;
};

struct Laser{
	int pos, dir;
};

vector<int> make_tree(int num){
	int h = (int)ceil(log2(num));
	int tree_size = (1 << (h + 1));
	vector<int> tree(tree_size);
	return tree;
}

void update(vector<int>& tree,int node,int start,int end,int i,int value){
	if (i<start || i > end){
		return;
	}
	tree[node] = min(tree[node], value);
	if (start != end){
		update(tree, 2 * node, start, (start + end) / 2, i, value);
		update(tree, 2 * node + 1, (start + end) / 2 + 1, end, i, value);
	}
}
int get_pos(vector<int>& v, int val) {
	return (lower_bound(v.begin(), v.end(), val) - v.begin()) + 1;
}



int init(vector<int>& tree, int node, int start, int end, int i, int value){
	if (i<start || i > end){
		return tree[node];
	}
	if (start == end){
		return tree[node] = value;
	}
	return tree[node] = min(init(tree, 2 * node, start, (start + end) / 2, i, value), init(tree, 2 * node + 1, (start + end) / 2 + 1, end, i, value));
}

int query(vector<int>& tree, int node, int start, int end, int i, int j){
	if (i > end || j < start){
		return INF;
	}
	if (i <= start && j >= end){
		return tree[node];
	}
	int q1 = query(tree, 2 * node, start, (start + end) / 2, i, j);
	int q2 = query(tree, 2 * node + 1, (start + end) / 2 + 1, end, i, j);
	return min(q1, q2);
}


int main(){
	int T;
	scanf("%d", &T);
	for (int test = 0; test < T; test++){
		vector<int> xpos;  //좌표압축을 하는데 사용됨.
		vector<int> ypos;
		vector<Ship> ship;
		vector<Laser> laser;

		int n, k, l;
		scanf("%d %d %d", &n, &k, &l);
		for (int i = 0; i < k; i++){
			int x1, y1, x2, y2, w;
			scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
			xpos.push_back(x1);
			xpos.push_back(x2);
			ypos.push_back(y1);
			ypos.push_back(y2);
			if (x1 > x2){
				swap(x1, x2);
			}
			if (y1 > y2){
				swap(y1, y2);
			}
			ship.push_back({ x1, y1, x2, y2, w });
		}
		for (int i = 0; i < l; i++){
			int pos, dir;
			scanf("%d %d", &pos, &dir);
			laser.push_back({ pos, dir });
			if (dir == 1){
				xpos.push_back(pos);
			}
			else{
				ypos.push_back(pos);
			}
		}
		sort(xpos.begin(), xpos.end());
		sort(ypos.begin(), ypos.end());
		xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
		ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());

		int xn = xpos.size();
		int yn = ypos.size();
		vector<int> xtree = make_tree(xn);
		vector<int> ytree = make_tree(yn);
		for (int i = 1; i <= xn; i++){
			init(xtree, 1, 1, xn, i, INF);
		}
		for (int i = 1; i <= yn; i++){
			init(ytree, 1, 1, yn, i, INF);
		}

		for (int i = l - 1; i >= 0; i--){
			if (laser[i].dir == 1){
				update(xtree, 1, 1, xn, get_pos(xpos, laser[i].pos), i);
			}
			else{
				update(ytree, 1, 1, yn, get_pos(ypos, laser[i].pos), i);
			}
		}

		vector<int> ans(l);
		for (int i = 0; i < k; i++){
			int x1 = get_pos(xpos, ship[i].x1);
			int y1 = get_pos(ypos, ship[i].y1);
			int x2 = get_pos(xpos, ship[i].x2);
			int y2 = get_pos(ypos, ship[i].y2);
			int w = ship[i].w;
			int xlaser = query(xtree, 1, 1, xn, x1, x2);
			int ylaser = query(ytree, 1, 1, yn, y1, y2);

			int choosen_laser = min(xlaser, ylaser);
			if (choosen_laser == INF)
				continue;
			ans[choosen_laser] = max(ans[choosen_laser], w);
		}
		for (int i = 0; i < l; i++){
			printf("%d\n", ans[i]);
		}

	}
	return 0;
}
//#include <stdio.h>
//#include<algorithm>
//#include<vector>
//#include<map>
//#define pb push_back
//#define mp make_pair
//using namespace std;
//
//typedef pair<int, int> pii;
//const int INF = 1234567890;
//struct Tree{
//	vector<int> tree;
//	int first;
//	Tree(int _size){
//		for (first = 1; first<_size; first <<= 1);
//		tree = vector<int>(_size << 2, INF);
//	}
//
//	void update(int pos, int val)
//	{
//		pos += first;
//		tree[pos] = val;
//		pos >>= 1;
//		while (pos>0){
//			tree[pos] = min(tree[pos << 1], tree[pos << 1 | 1]);
//			pos >>= 1;
//		}
//	}
//
//	int query(int l, int r)
//	{
//		int ret = INF;
//		l += first;
//		r += first;
//		while (l <= r){
//			ret = min(tree[l], min(tree[r], ret));
//			l = (l + 1) >> 1;
//			r = (r - 1) >> 1;
//		}
//		return ret;
//	}
//};
//
//struct Ship{
//	int x1, y1, x2, y2, w;
//};
//int T, N, K, L;
//
//
//int main()
//{
//	int i, j, k;
//	scanf("%d", &T);
//	while (T--){
//		vector<int> xpos;
//		vector<int> ypos;
//		vector<Ship> ship;
//		vector<pii> cannon;
//		vector<int> ans;
//
//		scanf("%d%d%d", &N, &K, &L);
//		for (i = 0; i<K; ++i){
//			int x1, y1, x2, y2, w;
//			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
//			xpos.pb(x1);
//			xpos.pb(x2);
//			ypos.pb(y1);
//			ypos.pb(y2);
//			if (x1>x2)
//				swap(x1, x2);
//			if (y1>y2)
//				swap(y1, y2);
//			ship.pb({ x1, y1, x2, y2, w });
//		}
//
//		for (i = 0; i<L; ++i){
//			int pos, dir;
//			scanf("%d%d", &pos, &dir);
//			if (dir)xpos.pb(pos);
//			else ypos.pb(pos);
//			cannon.pb(mp(pos, dir));
//		}
//
//		sort(xpos.begin(), xpos.end());
//		sort(ypos.begin(), ypos.end());
//		xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());  //이것이 좌표 압축이라고 하는데, 이것만 가지고 압축이 되나? 맵은 안사용해도 되나?   lower_bound까지 하면 좌표압축 된다.
//		ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
//
//		//map<int, int> mx;
//		//map<int, int> my;
//		//for (int i = 0; i < xpos.size(); i++){   //좌표압축  레이져,배의 좌표까지 압축해야 한다.
//		//	mx[xpos[i]] = i + 1;
//		//	my[ypos[i]] = i + 1;
//		//}
//		//for (int i = 0; i < cannon.size(); i++){
//		//	if (cannon[i].second == 1){
//		//		cannon[i].first = mx[cannon[i].first];
//		//	}
//		//	else{
//		//		cannon[i].first = my[cannon[i].first];
//		//	}
//		//}
//		//for (int i = 0; i < ship.size(); i++){
//		//	ship[i].x1 = mx[ship[i].x1];
//		//	ship[i].x2 = mx[ship[i].x2];
//		//	ship[i].y1 = my[ship[i].y1];
//		//	ship[i].y2 = my[ship[i].y2];
//		//}
//
//
//
//		Tree xtr((int)xpos.size());
//		Tree ytr((int)ypos.size());         //구간의 최소값. 노드: 좌표. 노드의 값: 캐논 번호의 최소값.
//		for (i = 0; i<L; ++i){
//			pii cur = cannon[i];   //캐논 pos, dir
//			if (cur.second){  //위쪽 방향 캐논일경우
//				int xidx = lower_bound(xpos.begin(), xpos.end(), cur.first) - xpos.begin();  //캐논 위치보다 왼쪽에 있는 점들의 갯수를 가져옴.  -> 이거 아니다.lower_bound()는 단순히 좌표 압축의 일부분일 뿐이다.
//				xtr.update(xidx, i);     //노드: 좌표. 노드의 값: 캐논 번호의 최소값.
//			}
//			else{
//				int yidx = lower_bound(ypos.begin(), ypos.end(), cur.first) - ypos.begin();
//				ytr.update(yidx, i);
//			}
//		}
//		ans = vector<int>(L, 0);
//		for (i = 0; i<K; ++i){
//			int x1 = lower_bound(xpos.begin(), xpos.end(), ship[i].x1) - xpos.begin();   //현재 보고 있는 배의 x1좌표보다 왼쪽에 있는 점들의 갯수를 가져옴.
//			int y1 = lower_bound(ypos.begin(), ypos.end(), ship[i].y1) - ypos.begin();
//			int x2 = lower_bound(xpos.begin(), xpos.end(), ship[i].x2) - xpos.begin();   //현재 보고 있는 배의 x2좌표보다 왼쪽에 있는 점들의 갯수를 가져옴.
//			int y2 = lower_bound(ypos.begin(), ypos.end(), ship[i].y2) - ypos.begin();
//			int w = ship[i].w;   //배의 무개를 가져옴
//			int xcannon = xtr.query(x1, x2);       //query(l,r)   l ~ r 사이의 구간을 가져오겠다. 각 노드: 좌표. 보고 있는 구간의 x캐논의 최소값을 가져옴.
//			int ycannon = ytr.query(y1, y2);
//			int can = min(xcannon, ycannon);    //지금 보고 있는 배를 부술 수 있는 캐논이 2개 이상일때는 둘중 한개로 부숴야 하는데, 무조건 번호가 작은 놈으로 부수겠다는 의미.
//			if (can == INF)continue;              //코드 분석은 잘 한것같다. 
//			ans[can] = max(ans[can], w);
//		}
//		for (i = 0; i<L; ++i)printf("%d\n",ans[i]);
//	}
//}
