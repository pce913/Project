#include<stdio.h>
#include<queue>
using namespace std;

/*
임의의 두 점을 잇고,
다른 두 점을 이으면 두개의 선분이 완성되고,
두 선분의 벡터의 내적이 0이면 직교
그리고 그때, 두 선분의 길이가 같으면 정사각형이다.
*/

struct Vector{
	int x1, y1,x2,y2;
	long long size;
	bool operator<(const Vector& v)const{
		return this->size < v.size;
	}
};

const int MAXN = 100000;
int x[4];
int y[4];

long long distance(int x1,int y1,int x2,int y2){
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

int main(){
	int T;          //마름모 꼴도 고려해야 한다.
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		priority_queue<Vector> q;
		for (int i = 0; i < 4; i++){
			scanf("%d %d",&x[i],&y[i]);
		}
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (i == j)
					continue;
				q.push({ x[j], y[j], x[i], y[i], distance(x[j], y[j], x[i], y[i]) });
			}
		}
		if (q.size() <= 1){
			printf("0\n");
			continue;
		}
		auto v1 = q.top();
		q.pop();
		auto v2 = q.top();

		int v1dirx = v1.x1 - v1.x2;
		int v1diry = v1.y1 - v1.y2;
		int v2dirx = v2.x1 - v2.x2;
		int v2diry = v2.y1 - v2.y2;
		if (v1.size == v2.size){
			if (v1dirx*v2dirx + v1diry*v2diry == 0){
				printf("1\n");
				continue;
			}
		}
		printf("0\n");
	}
	return 0;
}