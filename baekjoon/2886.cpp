#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

struct Point{
	int x, y;
};

struct Event{
	int dist, pidx, cidx;
	bool operator<(const Event& e)const{
		return dist < e.dist;
	}
};

char M[105][105];
vector<Point> person, chair;
bool dead[10005], charged[10005];

int distance(int x1, int y1, int x2, int y2){
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%s", &M[i][1]);
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if (M[i][j] == 'X'){
				person.push_back({ i, j });
			}
			else if (M[i][j] == 'L'){
				chair.push_back({ i, j });
			}
		}
	}
	vector<Event> v;
	for (int i = 0; i < person.size(); i++){
		for (int j = 0; j < chair.size(); j++){
			v.push_back({ distance(person[i].x, person[i].y, chair[j].x, chair[j].y), i, j });
		}
	}
	sort(v.begin(), v.end());
	int ans = 0;
	for (int i = 0; i < v.size(); i++){
		if (dead[v[i].pidx] || charged[v[i].cidx])
			continue;
		int explode = 0;
		for (int j = i; j < v.size(); j++){
			if (v[i].dist == v[j].dist && v[i].cidx == v[j].cidx){
				explode++;
				dead[v[j].pidx] = true;
				charged[v[j].cidx] = true;
			}
		}
		if (explode >= 2){
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}