#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

struct Point{
	int x, y, w;
	bool operator<(const Point& p)const{
		return this->x < p.x;
	}
};

struct Info{
	long long lsum, rsum, total_sum, max_sum;
};

vector<Point> a;
vector<int> ypos;
const int MAXN = 3005;
Info tree[4 * MAXN];
//LSUM->그 구간의 왼쪽 끝에서부터의 연속한 원소의 최대 합
//RSUM->그 구간의 오른쪽 끝에서부터의 연속한 원소의 최대 합
//TOTALSUM->그 구간의 모든 원소의 합
//MAXSUM->그 구간에서 나올 수 있는 최대 연속합

//LSUM = max(왼쪽자식의LSUM, 왼쪽자식의TOTALSUM + 오른쪽 자식의 LSUM)
//RSUM = max(오른쪽자식의RSUM, 오른쪽자식의TOTALSUM + 왼쪽 자식의RSUM)
//TOTALSUM = 왼쪽자식의TOTALSUM + 오른쪽자식의TOTALSUM
//MAXSUM = max(왼쪽자식의RSUM + 오른쪽자식의LSUM, 왼쪽자식의MAXSUM, 오른쪽자식의 MAXSUM, LSUM, RSUM)
void update(int node, int start, int end, int i, int value){
	if (i > end || i < start)
		return;
	if (start == end){
		tree[node].lsum += value;
		tree[node].rsum += value;
		tree[node].total_sum += value;
		tree[node].max_sum += value;
		return;
	}
	update(2 * node, start, (start + end) / 2, i, value);
	update(2 * node + 1, (start + end) / 2 + 1, end, i, value);
	Info& curr = tree[node];
	Info& left = tree[2 * node];
	Info& right = tree[2 * node + 1];
	curr.lsum = max(left.lsum, left.total_sum + right.lsum);
	curr.rsum = max(right.rsum, right.total_sum + left.rsum);
	curr.total_sum = left.total_sum + right.total_sum;
	curr.max_sum = max({ left.rsum + right.lsum, left.max_sum, right.max_sum, curr.lsum, curr.rsum });
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x, y, w;
		scanf("%d %d %d", &x, &y, &w);
		a.push_back({ x, y, w });
		ypos.push_back(y);
	}
	sort(a.begin(), a.end());
	sort(ypos.begin(), ypos.end());
	ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
	for (int i = 0; i < a.size(); i++){
		a[i].y = lower_bound(ypos.begin(), ypos.end(), a[i].y) - ypos.begin() + 1;
	}

	const int MAX_Y = ypos.size();
	long long ans = 0;
	for (int i = 0; i < a.size(); i++){
		memset(tree, 0, sizeof(tree));
		if (i>0 && a[i].x == a[i - 1].x)    //연속된 두 점이 같은 x 좌표라면 밑에서 이미 처리 했을 것이므로
			continue;          //넘어간다.

		for (int j = i; j < a.size(); j++){
			int y = a[j].y;
			int value = a[j].w;
			update(1, 1, MAX_Y, y, value);
			if (j < a.size() - 1 && a[j].x == a[j + 1].x)   //좌표를 볼 때 x좌표가 같은 점들은 반드시 한번에 업데이트 한 후 봐야 한다. 
				continue;

			long long q = tree[1].max_sum;
			ans = max(ans, q);
		}
	}
	printf("%lld", ans);
	return 0;
}