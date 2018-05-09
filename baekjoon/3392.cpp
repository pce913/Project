//#include <cstdio>
//#include <algorithm>
//#define MAX_N 10000
//#define MAX_Y 30000
//using namespace std;
//struct m {
//	int x, y1, y2, z;
//};
//bool cmp(m a, m b) {
//	return a.x < b.x;
//}
//int n, seg[4 * MAX_Y], a, b, c, d, cnt[4 * MAX_Y], last, res;
//m arr[2 * MAX_N];
//void update(int lo, int hi, int val, int node, int x, int y) {
//	if (y < lo || hi < x)
//		return;
//	if (lo <= x&&y <= hi)
//		cnt[node] += val;
//	else {
//		int mid = (x + y) >> 1;
//		update(lo, hi, val, node * 2, x, mid);
//		update(lo, hi, val, node * 2 + 1, mid + 1, y);
//	}
//	if (cnt[node])seg[node] = y - x + 1;
//	else {
//		if (x == y)seg[node] = 0;
//		else seg[node] = seg[node * 2] + seg[node * 2 + 1];
//	}
//}
//int main() {
//	scanf("%d", &n);
//	for (int i = 0; i < n; i++) {
//		scanf("%d%d%d%d", &a, &b, &c, &d);
//		arr[i] = { a, b, d - 1, 1 };
//		arr[i + n] = { c, b, d - 1, -1 };
//	}
//	sort(arr, arr + 2 * n, cmp);
//	for (int i = 0; i < 2 * n; i++) {
//		if (i) {
//			int dx = arr[i].x - last;
//			res += dx*seg[1];
//		}
//		update(arr[i].y1, arr[i].y2, arr[i].z, 1, 0, MAX_Y);
//		last = arr[i].x;
//	}
//	printf("%d\n", res);
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX_Y = 30000;  

int tree[5 * MAX_Y];
int cnt[5 * MAX_Y];    //어느 구간을 보았을때 걔네가 전부다 1 이상이니? 를 묻기 위한 변수

struct Point{
	int x, y , ly;
	bool isOpen;
	bool operator<(const Point& p)const{
		return this->x < p.x;
	}
};

vector<Point> line;

void update(int node, int start, int end, int i, int j, int value){
	if (i > end || j < start){
		return;
	}
	if (i <= start && j >= end){
		cnt[node] += value;
	}
	else{
		update(2 * node, start, (start + end) / 2, i, j, value);
		update(2 * node + 1, (start + end) / 2 + 1, end, i, j, value);
	}
	
	if (cnt[node] > 0){     //cnt[node]가 양수라는 것은 node가 담당하는 구간이 모두 양수라는 것이다.
		tree[node] = end - start + 1; 
	}
	else{
		tree[node] = tree[2 * node] + tree[2 * node + 1];
	}
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		line.push_back({ x1, y1, y2,true });
		line.push_back({ x2, y2, y1,false });
	}
	sort(line.begin(), line.end());

	int ans = 0;
	int last_x = line[0].x;
	for (int i = 0; i < line.size(); i++){
		int x = line[i].x;
		int y = line[i].y;
		int ly = line[i].ly;
		bool isOpen = line[i].isOpen;
		if (ly < y){
			swap(ly, y);
		}

		int dx = x - last_x;
		last_x = x;
		ans+=dx* (tree[1]);
		if (isOpen){
			update(1, 0, MAX_Y, y, ly-1, 1);    // 예를 들어 10~20을 표시한다고 했을때 범위가 11이므로 update가 11만큼 된다.
		}                                       //이것을 막기 위해서 -1칸까지만 업데이트 한다.
		else{
			update(1, 0, MAX_Y, y, ly-1, -1);
		}
	}
	printf("%d",ans);
	return 0;
}


