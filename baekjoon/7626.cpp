#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
    // 3392 화성 지도 문제와 함께 보자.
struct Info{
	int x, y, ly;
	bool isOpen;
	bool operator<(const Info& p)const{
		return this->x < p.x;
	}
};
const int MAXN = 400000;
vector<Info> a;
vector<int> ypos;
long long tree[4 * MAXN], cnt[4 * MAXN];

void update(int node, int start, int end, int i, int j, int value){
	if (i>end || j < start)
		return;
	if (i <= start && j >= end){
		cnt[node] += value;
	}
	else{
		update(2 * node, start, (start + end) / 2, i, j, value);
		update(2 * node + 1, (start + end) / 2 + 1, end, i, j, value);
	}

	if (cnt[node]>0){
		tree[node] = ypos[end + 1] - ypos[start];    //기존 좌표 계산 할때는 end - start + 1 이것으로 했지만
	}                                              //좌표 압축일 때는 ypos[end + 1] - ypos[start] 이렇게 한다.
	else{
		if (start == end)
			tree[node] = 0;
		else{
			tree[node] = tree[2 * node] + tree[2 * node + 1];
		}

	}
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		int x1, x2, y1, y2;
		scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
		a.push_back({ x1, y1, y2, true });
		a.push_back({ x2, y2, y1, false });
		ypos.push_back(y1);
		ypos.push_back(y2);
	}
	sort(a.begin(), a.end());
	sort(ypos.begin(), ypos.end());
	ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
	for (int i = 0; i < a.size(); i++){
		a[i].ly = lower_bound(ypos.begin(), ypos.end(), a[i].ly) - ypos.begin();
		a[i].y = lower_bound(ypos.begin(), ypos.end(), a[i].y) - ypos.begin();
	}
	const int MAX_Y = ypos.size();
	int dx = 0;
	int last_x = a[0].x;
	long long ans = 0;
	for (int i = 0; i < a.size(); i++){
		int x = a[i].x;
		int y = a[i].y;
		int ly = a[i].ly;
		bool isOpen = a[i].isOpen;
		if (ly < y){
			swap(ly, y);
		}

		int dx = x - last_x;
		last_x = x;
		ans += dx*tree[1];
		if (isOpen){
			update(1, 0, MAX_Y - 1, y, ly - 1, 1);
		}
		else{
			update(1, 0, MAX_Y - 1, y, ly - 1, -1);
		}
	}
	printf("%lld", ans);
	return 0;
}