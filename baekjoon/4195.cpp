#include<iostream>
#include<cstring>
#include<map>
#include<string>
using namespace std;

int parent[200005];
int relation[200005];
map<string, int> mp;

int Find(int x){
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}

int Union(int x, int y){
	x = Find(x);
	y = Find(y);
	if (x != y){
		parent[y] = x;
		relation[x] += relation[y];
	}
	return relation[x];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 0; test < T; test++){
		mp.clear();
		int f;
		cin >> f;
		for (int i = 1;i<=2*f; i++){
			parent[i] = i;
			relation[i] = 1;
		}

		int num = 1;
		for (int i = 0; i < f; i++){
			string a, b;
			cin >> a >> b;
			if (mp.count(a) == 0){
				mp[a] = num;
				num++;
			}
			if (mp.count(b) == 0){
				mp[b] = num;
				num++;
			}
			int ans = Union(mp[a], mp[b]);
			cout << ans << "\n";
		}

	}
	return 0;
}