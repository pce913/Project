#include<iostream>
using namespace std;
//bool 변수를 2개 써야 한다.

int a[105][105];
int an[105];
int r[105][105];
int rn[105];
int ant[105], rnt[105];
int check[105];
int stk[105];
int sn;
int GN;
int grp[105];
int cvt(int p, char c){  //알파벳에 대한 노드를 반환
	return 52*p + c - 'A' + 1;
}

int NOT(int node){
	return node + 26;
}

void add_edge(int u,int v){
	a[u][an[u]++] = v;
	r[v][rn[v]++] = u;
}

void dfs_rev(int node,int gnum){
	check[node] = GN;
	grp[node] = gnum;
	for (int i = 0; i < rn[node]; i++){
		int next = r[node][i];
		if (check[next] != GN){
			dfs_rev(next, gnum);
		}
	}
}

void dfs(int node){
	check[node] = GN;
	for (int i = 0; i < an[node]; i++){
		int next = a[node][i];
		if (check[next] != GN)
			dfs(next);
	}
	stk[sn++] = node;
}

int go(){
	++GN;
	for (int i = 1; i <= 4 * 26; i++){
		if (check[i] != GN){
			dfs(i);
		}
	}
	++GN;
	int gnum = 0;
	while (sn){
		int node = stk[--sn];
		if (check[node] != GN){
			dfs_rev(node, ++gnum);
		}
	}
	for (int i = 1; i <= 26; i++){
		if (grp[i] == grp[i + 26])
			return false;
		if (grp[i + 26 * 2 ] == grp[i + 26 * 2 + 26])
			return false;
	}
	return true;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		char x, y;
		int p, r;
		cin >> x >> y >> p >> r;
		p -= 1;
		if (r == 0){
			add_edge(cvt(p, x), NOT(cvt(p, x)));
			add_edge(cvt(p, y), NOT(cvt(p, y)));
		}
		else if (r == 1){  //xor
			add_edge(NOT(cvt(p, x)), cvt(p, y));
			add_edge(NOT(cvt(p, y)), cvt(p, x));
			add_edge(cvt(p, x), NOT(cvt(p, y)));
			add_edge(cvt(p, y), NOT(cvt(p, x)));
		}
		else{  //
			add_edge(NOT(cvt(p, x)), cvt(p, x));
			add_edge(NOT(cvt(p, y)), cvt(p, y));
			add_edge(cvt(p ^ 1, x), NOT(cvt(p ^ 1, x)));
			add_edge(cvt(p ^ 1, y), NOT(cvt(p ^ 1, y)));
		}
	}
	for (int i = 1; i <= 4*26; i++){
		ant[i] = an[i];
		rnt[i] = rn[i];
	}

	int ans = 0;
	for (char x = 'A'; x <= 'Z'; x++){
		for (char y = x + 1; y <= 'Z'; y++){
			for (char z = y + 1; z <= 'Z'; z++){
				for (int i = 1; i <= 4 * 26; i++){
					an[i] = ant[i], rn[i] = rnt[i];
				}
				for (char i = 'A'; i <= 'Z'; i++){
					if (i == x || i == y || i == z){
						add_edge(cvt(0, i), NOT(cvt(0, i)));
						add_edge(cvt(1, i), NOT(cvt(1, i)));
					}
					else{
						add_edge(NOT(cvt(0, i)), cvt(1, i));
						add_edge(NOT(cvt(1, i)), cvt(0, i));
						add_edge(cvt(0, i), NOT(cvt(1, i)));
						add_edge(cvt(1, i), NOT(cvt(0, i)));
					}
				}
				ans+=go();
			}
		}
	}
	cout << ans;
	return 0;
}
//
//#include <stdio.h>
//#include <vector>
//#define ll long long
//using namespace std;
//int N;
//int visit[105];
//struct Invest{
//	int c1, c2;
//	int player;
//	int rep;
//}inv[50];
//void add_edge(int u, int v, vector<int> edge[105]){
//	if (u < 0) u = 52 - u;
//	if (v < 0) v = 52 - v;
//	edge[u].push_back(v);
//}
//void dfs(int ix, int stamp, vector<int> edge[105]){
//	//printf("!%d\n",ix);
//	if (visit[ix] == stamp) return;
//	visit[ix] = stamp;
//	for (int i = 0; i < edge[ix].size(); i++)
//		dfs(edge[ix][i], stamp, edge);
//	edge[0].push_back(ix);
//}
//bool check(vector<int> &v){
//	if (v.size() == 0) return true;
//	int cnt[53] = { 0 };
//	int x;
//	for (int i = 0; i < v.size(); i++){
//		x = v[i];
//		if (x > 52) x -= 52;
//		cnt[x]++;
//		if (cnt[x] > 1) return false;
//	}
//	return true;
//}
//bool sat(int s1, int s2, int s3, int &stamp){
//	int i, j;
//	int u, v;
//	vector<int> edge[105];
//	vector<int> back[105];
//	for (i = 0; i < N; i++){
//		u = 26 * (inv[i].player - 1) + inv[i].c1;
//		v = 26 * (inv[i].player - 1) + inv[i].c2;
//		if (inv[i].rep == 1){
//			add_edge(-u, v, edge);
//			add_edge(-v, u, edge);
//			add_edge(v, -u, back);
//			add_edge(u, -v, back);
//			add_edge(-u, v, back);
//			add_edge(-v, u, back);
//			add_edge(v, -u, edge);
//			add_edge(u, -v, edge);
//		}
//		else if (inv[i].rep == 2){
//			add_edge(-u, u, edge);
//			add_edge(-v, v, edge);
//			add_edge(u, -u, back);
//			add_edge(v, -v, back);
//			u = 26 * ((inv[i].player ^ 3) - 1) + inv[i].c1;
//			v = 26 * ((inv[i].player ^ 3) - 1) + inv[i].c2;
//			add_edge(-u, u, back);
//			add_edge(-v, v, back);
//			add_edge(u, -u, edge);
//			add_edge(v, -v, edge);
//		}
//		else{
//			add_edge(-u, u, back);
//			add_edge(-v, v, back);
//			add_edge(u, -u, edge);
//			add_edge(v, -v, edge);
//		}
//	}
//	for (i = 1; i <= 26; i++){
//		if (i == s1 || i == s2 || i == s3){   //s1,s2,s3는 아무도 가지고 있지 않다.
//			add_edge(i, -i, edge);
//			add_edge(i + 26, -i - 26, edge);
//			add_edge(-i, i, back);
//			add_edge(-i - 26, i + 26, back);
//		}
//		else{   //1번플레이어와 2번 플레이어 둘중에 한명은 가지고 있다.
//			add_edge(-i, i + 26, edge);
//			add_edge(-i - 26, i, edge);
//			add_edge(i + 26, -i, back);
//			add_edge(i, -i - 26, back);
//			add_edge(-i, i + 26, back);
//			add_edge(-i - 26, i, back);
//			add_edge(i + 26, -i, edge);
//			add_edge(i, -i - 26, edge);
//		}
//	}
//	for (i = 1; i <105; i++) dfs(i, stamp, edge);
//	stamp++;
//	for (i = edge[0].size() - 1; i >= 0; i--){
//		//printf("%d ",edge[0][i]);
//		dfs(edge[0][i], stamp, back);
//		if (!check(back[0])) return false;
//		back[0].clear();
//	}
//
//
//	return true;
//
//}
//int main(){
//	int i, j, k;
//	int ans = 0;
//	char c1, c2;
//	int player, reply;
//	int stamp = 0;
//
//	for (scanf("%d", &N), i = 0; i < N; i++){
//		scanf(" %c%c%d%d", &c1, &c2, &player, &reply);
//		inv[i] = { c1 - 'A' + 1, c2 - 'A' + 1, player, reply };
//	}
//	for (i = 1; i <= 26; i++){
//		for (j = i + 1; j <= 26; j++){
//			for (k = j + 1; k <= 26; k++){
//				if (sat(i, j, k, ++stamp))
//					ans++;
//				//return 0;
//			}
//		}
//	}
//	printf("%d", ans);
//	return 0;
//}
//#include <cstdio>
//#include <cstring>
//#include <vector>
//#include <stack>
//#include <algorithm>
//using namespace std;
//const int MAX = 52;
//
//int cnt, SN, dfsn[MAX * 2], sn[MAX * 2];
//vector<int> adj[MAX * 2];
//bool finished[MAX * 2];
//stack<int> S;
//
//inline int oppo(int n){ return n % 2 ? n - 1 : n + 1; }
//
//int dfs(int curr){
//	dfsn[curr] = ++cnt;
//	S.push(curr);
//	int result = dfsn[curr];
//	for (int next : adj[curr]){
//		if (dfsn[next] == 0) result = min(result, dfs(next));
//		else if (!finished[next]) result = min(result, dfsn[next]);
//	}
//	if (result >= dfsn[curr]){
//		sn[curr] = SN++;
//		while (1){
//			int family = S.top();
//			S.pop();
//			finished[family] = true;
//			if (family == curr) break;
//			sn[family] = sn[curr];
//		}
//	}
//	return result;
//}
//
//int main(){
//	int N;
//	scanf("%d", &N);
//	// 4i+1: player 1 has i, 4i+3: player 2 has i
//	for (int i = 0; i<26; i++){  //어떤 카드를 1번 플레이어가 가지고 있거나, 2번 플레이어가 가지고 있거나, 둘다 가지고 있지 않거나
//		int p = i * 4, q = i * 4 + 2;  //~A1, ~A2
//		adj[oppo(p)].push_back(q);    //(~A1 V ~A2)    ==    A1 -> ~A2  
//		adj[oppo(q)].push_back(p);
//	}
//	for (int i = 0; i<N; i++){
//		char a, b;
//		int P, K;
//		scanf(" %c%c %d %d", &a, &b, &P, &K);
//		int A = (a - 'A') * 2, B = (b - 'A') * 2;
//		P--;   //1번 플레이어는 0, 2번 플레이어는 1
//		if (K == 0){  //어느 플레이어가 '한개도 가지고 있지 않다'고 말할때
//			int p = (A + P) * 2, q = (B + P) * 2;  //~A1 , ~B1
//			adj[oppo(p)].push_back(p);  //(~A1 V ~A1)
//			adj[oppo(q)].push_back(q);  //(~B1 V ~B1)
//		}
//		else if (K == 1){  //어느 플레이어가 '한개 가지고 있다'고 말할때 XOR 연산
//			int p = (A + P) * 2 + 1, q = (B + P) * 2 + 1; //A1 , B1
//			adj[oppo(p)].push_back(q); //(A1 V B1)
//			adj[oppo(q)].push_back(p); 
//			adj[p].push_back(oppo(q)); //(~A1 V ~B1)
//			adj[q].push_back(oppo(p));
//		}
//		else{   //어느 플레이어가 '둘다 가지고 있다'고 말할때
//			int p = (A + P) * 2 + 1, q = (B + P) * 2 + 1;  //A1, B1
//			adj[oppo(p)].push_back(p);   //(A1 V A1)
//			adj[oppo(q)].push_back(q);   //(B1 V B1)
//		}
//	}
//
//	int result = 0;
//	bool used[26] = { 0 };
//	for (int a = 0; a<26; a++){
//		used[a] = true;        //black 후보가 될 수 있는 조합을 찾는 것이다. 
//		for (int b = a + 1; b<26; b++){
//			used[b] = true;
//			for (int c = b + 1; c<26; c++){
//				used[c] = true;
//				for (int i = 0; i<26; i++){
//					int p = i * 4, q = i * 4 + 2;   //~A1, ~A2
//					if (used[i]){   // black인 카드는 제외시켜 버리고
//						adj[oppo(p)].push_back(p);   //(~A1 V ~A1)
//						adj[oppo(q)].push_back(q);   //(~A2 V ~A2)
//					}
//					else{  //black이 아닌 카드는 둘 중에 한명만 가지고 있게 한다. XOR
//						adj[oppo(p)].push_back(q);   //(~A1 V ~A2)
//						adj[oppo(q)].push_back(p);
//						adj[p].push_back(oppo(q));   //(A1 V A2)
//						adj[q].push_back(oppo(p));
//					}
//				}
//
//				for (int i = 0; i<MAX * 2; i++)
//					if (dfsn[i] == 0)     //dfs에서 빠져 나오는 순서대로 저장과 동시에 그룹 번호를 매김.
//						dfs(i);
//				bool possible = true;
//				for (int i = 0; i<MAX; i++){
//					if (sn[i * 2] == sn[i * 2 + 1]){   //같은 집합이니?
//						possible = false;
//						break;
//					}
//				}
//				if (possible) result++;   //가능한 조합이라면 정답에 더해준다.
//
//				for (int i = 0; i<26; i++){   //back tracking 처럼 원상복귀 시키는 코드이다.
//					int p = i * 4, q = i * 4 + 2;   //~A1, ~A2
//					adj[oppo(p)].pop_back();
//					adj[oppo(q)].pop_back();
//					if (!used[i]){
//						adj[p].pop_back();
//						adj[q].pop_back();
//					}
//				}
//				cnt = SN = 0;
//				fill(dfsn, dfsn + MAX * 2, 0);
//				fill(finished, finished + MAX * 2, 0);
//
//				used[c] = false;
//			}
//			used[b] = false;
//		}
//		used[a] = false;
//	}
//	printf("%d\n", result);
//}