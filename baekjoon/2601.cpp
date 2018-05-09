#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
/*먼저 각각의 직사각형에
대해, 이 직사각형을 덮을 수 있도록 하는 정사각형의 왼쪽 위 꼭지점의 영역을 생각
한다.즉, 이러한 영역의 한 점을 선택하여, 그 점을 왼쪽 위로 하는 정사각형을 놓았
을 때 주어진 직사각형이 덮일 수 있도록 하는 것이다.이러한 영역의 좌표 범위를
잘 고려해 보면, 이 영역도 역시 직사각형으로 나타나게 된다.따라서 이렇게 문제를
바꾸고 나면 직사각형이 가장 많이 겹치는 영역이나 점을 찾는 문제로 바뀌게 된다.*/

struct Line{
	int x, y, ly;
	bool isOpen;
	bool operator<(const Line& l)const{
		if (this->x == l.x){
			return this->isOpen < l.isOpen;    //이것도 반드시 달아줘야 한다. 즉, x좌표가 같을 경우 닫는 괄호부터 본다.
		}
		return this->x < l.x;
	}
};
int MAX_Y = 0;
const int MAXN = 200005;
vector<Line> line;
vector<int> ypos;
int tree[4 * MAXN],lazy[4*MAXN];

void update_lazy(int node,int start,int end){
	if (lazy[node] != 0){
		tree[node] += lazy[node];
	}
	if (start != end){
		lazy[2 * node] += lazy[node];
		lazy[2 * node + 1] += lazy[node];
	}
	lazy[node] = 0;
}

void update_range(int node,int start,int end,int i,int j,int value){
	update_lazy(node, start, end);
	if (i > end || j < start){
		return;
	}
	if (start >= i && end <= j){
		tree[node] += value;
		if (start != end){
			lazy[2 * node] += value;
			lazy[2 * node + 1] += value;
		}
		return;
	}
	update_range(2 * node, start, (start + end) / 2, i, j, value);
	update_range(2 * node + 1, (start + end) / 2+1,end , i, j, value);
	tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

int query(){
	update_lazy(1, 1, MAX_Y);
	return tree[1];
}


int main(){
	int mx1, my1, mx2, my2, d, m;
	scanf("%d %d %d %d %d %d", &mx1, &my1, &mx2, &my2, &d, &m);
	for (int i = 0; i < m; i++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		int nx = max(mx1, x2 - d);
		int ny = min(my1, y2 + d);
		if (nx <= x1 && ny >= y1){
			line.push_back({ nx, ny, y1, true });
			line.push_back({ x1 + 1, y1, ny, false });    //여기에 +1안하면 틀리게 된다.
			ypos.push_back(ny);     // nx == x1 이라면 nx부터 보게 하기 위해서 +1을 해준다. 즉, 이럴때는 여는 괄호부터 먼저 보아야 한다.
			ypos.push_back(y1);     // nx == x1 이 되는 경우는 현재 보고 있는 사각형의 크기가 카펫의 크기 d와 같을때이다. 이럴땐 여는 괄호부터 먼저 보아야 답이 제대로 갱신된다. 
		}                          //이런 경우를 제외하고는 닫는 괄호부터 먼저 보아야 하므로 operator 설정을 해주었다.
	}
	sort(line.begin(), line.end());
	sort(ypos.begin(), ypos.end());
	ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
	for (int i = 0; i < line.size(); i++){
		line[i].y = lower_bound(ypos.begin(), ypos.end(), line[i].y) - ypos.begin() + 1;
		line[i].ly = lower_bound(ypos.begin(), ypos.end(), line[i].ly) - ypos.begin() + 1;
	}

	MAX_Y = ypos.size();
	int ans = 0;
	for (int i = 0; i < line.size(); i++){
		int y = line[i].y;
		int ly = line[i].ly;
		bool isOpen = line[i].isOpen;
		if (y>ly)
			swap(y, ly);

		if (isOpen){
			update_range(1, 1, MAX_Y, y, ly, 1);
		}
		else{
			update_range(1, 1, MAX_Y, y, ly, -1);
		}
		ans = max(ans, query());
	}
	printf("%d", ans);
	return 0;
}
//#include<stdio.h>
//#include<vector>
//#include<algorithm>
//using namespace std;
///*먼저 각각의 직사각형에
//대해, 이 직사각형을 덮을 수 있도록 하는 정사각형의 왼쪽 위 꼭지점의 영역을 생각
//한다.즉, 이러한 영역의 한 점을 선택하여, 그 점을 왼쪽 위로 하는 정사각형을 놓았
//을 때 주어진 직사각형이 덮일 수 있도록 하는 것이다.이러한 영역의 좌표 범위를
//잘 고려해 보면, 이 영역도 역시 직사각형으로 나타나게 된다.따라서 이렇게 문제를
//바꾸고 나면 직사각형이 가장 많이 겹치는 영역이나 점을 찾는 문제로 바뀌게 된다.*/
//
//struct Line{
//	int x, y, ly;
//	bool isOpen;
//	bool operator<(const Line& l)const{
//		if (this->x == l.x){
//			return this->isOpen < l.isOpen;    //이것도 반드시 달아줘야 한다. 즉, x좌표가 같을 경우 닫는 괄호부터 본다.
//		}
//		return this->x < l.x;
//	}
//};
//
//const int MAXN = 200005;
//vector<Line> line;
//vector<int> ypos;
//int tree[4 * MAXN],cnt[4*MAXN];
//
//void update(int node, int start, int end, int i, int j, int value){
//	if (i >end || j < start){
//		return;
//	}
//	if (start >= i && end <= j){
//		cnt[node] += value;
//	}
//	else{
//		update(2 * node, start, (start + end) / 2, i, j, value);
//		update(2 * node + 1, (start + end) / 2+1,end , i, j, value);
//	}
//	if (start == end){
//		tree[node] = cnt[node];
//	}
//	else{
//		tree[node] = cnt[node] + max(tree[2 * node], tree[2 * node + 1]);
//	}
//}
//
//int main(){
//	int mx1, my1, mx2, my2, d, m;
//	scanf("%d %d %d %d %d %d",&mx1,&my1,&mx2,&my2,&d,&m);
//	for (int i = 0; i < m; i++){
//		int x1, y1, x2, y2;
//		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
//		int nx = max(mx1, x2 - d);
//		int ny = min(my1, y2 + d);
//		if (nx <= x1 && ny >= y1){
//			line.push_back({ nx, ny, y1, true });
//			line.push_back({ x1 + 1, y1, ny, false });    //여기에 +1안하면 틀리게 된다.
//			ypos.push_back(ny);     // nx == x1 이라면 nx부터 보게 하기 위해서 +1을 해준다. 즉, 이럴때는 여는 괄호부터 먼저 보아야 한다.
//			ypos.push_back(y1);     // nx == x1 이 되는 경우는 현재 보고 있는 사각형의 크기가 카펫의 크기 d와 같을때이다. 이럴땐 여는 괄호부터 먼저 보아야 답이 제대로 갱신된다. 
//		}                          //이런 경우를 제외하고는 닫는 괄호부터 먼저 보아야 하므로 operator 설정을 해주었다.
//	}
//	sort(line.begin(), line.end());
//	sort(ypos.begin(), ypos.end());
//	ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
//	for (int i = 0; i < line.size(); i++){
//		line[i].y = lower_bound(ypos.begin(), ypos.end(), line[i].y) - ypos.begin() + 1;
//		line[i].ly = lower_bound(ypos.begin(), ypos.end(), line[i].ly) - ypos.begin() + 1;
//	}
//	const int MAX_Y = ypos.size();
//	int ans = 0;
//	for (int i = 0; i < line.size(); i++){
//		int y = line[i].y;
//		int ly = line[i].ly;
//		bool isOpen = line[i].isOpen;
//		if (y>ly)
//			swap(y, ly);
//
//		if (isOpen){
//			update(1, 1, MAX_Y, y, ly, 1);
//		}
//		else{
//			update(1, 1, MAX_Y, y, ly, -1);
//		}
//		ans = max(ans, tree[1]);
//	}
//	printf("%d",ans);
//	return 0;
//}