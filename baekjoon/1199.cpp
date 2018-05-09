#include<stdio.h>
#include<stack>
using namespace std;

struct Point{
	int x, y;
};

stack<Point> s;
stack<int> ans;

int a[1005][1005];
int n;

bool isEvenEdge(){
	for (int i = 1; i <= n; i++){
		int cnt = 0;
		for (int j = 1; j <= n; j++)
			cnt += a[i][j];

		if (cnt & 1)
			return false;
	}
	return true;
}

void go(){
	while (!s.empty()){    //DFS ºñÀç±Í ±¸Çö.
		auto p = s.top();
		int x = p.x;
		int y = p.y;
		s.pop();
		bool isEnd = true;
		for (int i = y; i <= n; i++){
			if (a[x][i] > 0){
				isEnd = false;
				a[x][i]--;
				a[i][x]--;
				s.push({ x, i+1 });
				s.push({ i, 1 });
				break;
			}
		}
		if (isEnd)
			ans.push(x);
	}
}

int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			scanf("%d",&a[i][j]);
			if (s.empty() && a[i][j] > 0){
				s.push({ i, j });
			}
		}
	}
	if (!isEvenEdge())
		printf("-1");
	else{
		go();
		while (!ans.empty()){
			printf("%d ",ans.top());
			ans.pop();
		}
	}
	return 0;
}