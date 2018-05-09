#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

struct Edge{
	int u, v, cost;
	bool operator<(const Edge& e)const{
		return this->cost < e.cost;
	}
};

struct In{
	int p, index;
	bool operator<(const In& i)const{
		return this->p < i.p;
	}
};

vector<In> ax;
vector<In> ay;
vector<In> az;
vector<Edge> e;
int parent[100001];

int Find(int x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

bool Union(int x, int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
		return true;
	}
	return false;
}


int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		ax.push_back({ x, i });
		ay.push_back({ y, i });
		az.push_back({ z, i });
		parent[i] = i;
	}
	sort(ax.begin(), ax.end());
	sort(ay.begin(), ay.end());
	sort(az.begin(), az.end());
	for (int i = 0; i < n - 1; i++){
		e.push_back({ ax[i].index, ax[i + 1].index, ax[i + 1].p - ax[i].p });
		e.push_back({ ay[i].index, ay[i + 1].index, ay[i + 1].p - ay[i].p });
		e.push_back({ az[i].index, az[i + 1].index, az[i + 1].p - az[i].p });
	}
	sort(e.begin(), e.end());

	long long ans = 0;
	for (int i = 0; i < e.size(); i++){
		int x = e[i].u;
		int y = e[i].v;
		int cost = e[i].cost;
		if (Union(x, y)){
			ans += cost;
		}
	}
	printf("%lld", ans);
	return 0;
}