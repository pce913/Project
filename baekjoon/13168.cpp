#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<set>
#include<string>
using namespace std;
const long long INF = 1e18;

map<string, int> mm;
vector<string> plan;
long long dist_normal[105][105];
long long dist_ticket[105][105];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,r;
	cin >> n >> r;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i == j)
				continue;
			dist_normal[i][j] = INF;
			dist_ticket[i][j] = INF;
		}
	}

	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		mm[s] = i;
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++){
		string s;
		cin >> s;
		plan.push_back(s);
	}
	int K;
	cin >> K;
	for (int i = 0; i < K; i++){
		string w, s, e;
		long long p;
		cin >> w >> s >> e >> p;
		int u = mm[s];
		int v = mm[e];
		dist_normal[u][v] = min(dist_normal[u][v], p);
		dist_normal[v][u] = min(dist_normal[v][u], p);
		if (w == "Mugunghwa" || w == "ITX-Saemaeul" || w == "ITX-Cheongchun"){
			dist_ticket[u][v] = 0;
			dist_ticket[v][u] = 0;
		}
		else if (w == "S-Train" || w == "V-Train"){
			dist_ticket[u][v] = min(dist_ticket[u][v], p / 2);
			dist_ticket[v][u] = min(dist_ticket[v][u], p / 2);
		}
		else{
			dist_ticket[u][v] = min(dist_ticket[u][v], p);
			dist_ticket[v][u] = min(dist_ticket[v][u], p);
		}
	}
	////////////////////////////////
	for (int k = 0; k < n; k++){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (dist_normal[i][j] > dist_normal[i][k] + dist_normal[k][j]){
					dist_normal[i][j] = dist_normal[i][k] + dist_normal[k][j];
				}
				if (dist_ticket[i][j] > dist_ticket[i][k] + dist_ticket[k][j]){
					dist_ticket[i][j] = dist_ticket[i][k] + dist_ticket[k][j];
				}
			}
		}
	}

	long long normal_cost=0, ticket_cost=0;
	for (int i = 0; i < plan.size()-1; i++){
		string s = plan[i];
		string e = plan[i + 1];
		int u = mm[s];
		int v = mm[e];
		ticket_cost += dist_ticket[u][v];
		normal_cost += dist_normal[u][v];		
	}

	cout << (r+ticket_cost < normal_cost ? "Yes" : "No");
	return 0;
}
