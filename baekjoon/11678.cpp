#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
const int MAX = 52;

int cnt, SN, dfsn[MAX * 2], sn[MAX * 2];
vector<int> adj[MAX * 2];
bool finished[MAX * 2];
stack<int> S;

inline int oppo(int n){ return n % 2 ? n - 1 : n + 1; }

int dfs(int curr){
	dfsn[curr] = ++cnt;
	S.push(curr);
	int result = dfsn[curr];
	for (int next : adj[curr]){
		if (dfsn[next] == 0) result = min(result, dfs(next));
		else if (!finished[next]) result = min(result, dfsn[next]);
	}
	if (result >= dfsn[curr]){
		sn[curr] = SN++;
		while (1){
			int family = S.top();
			S.pop();
			finished[family] = true;
			if (family == curr) break;
			sn[family] = sn[curr];
		}
	}
	return result;
}

int main(){
	int N;
	scanf("%d", &N);
	// 4i+1: player 1 has i, 4i+3: player 2 has i
	for (int i = 0; i<26; i++){  //어떤 카드를 1번 플레이어가 가지고 있거나, 2번 플레이어가 가지고 있거나, 둘다 가지고 있지 않거나
		int p = i * 4, q = i * 4 + 2;  //~A1, ~A2
		adj[oppo(p)].push_back(q);    //(~A1 V ~A2)    ==    A1 -> ~A2  
		adj[oppo(q)].push_back(p);
	}
	for (int i = 0; i<N; i++){
		char a, b;
		int P, K;
		scanf(" %c%c %d %d", &a, &b, &P, &K);
		int A = (a - 'A') * 2, B = (b - 'A') * 2;
		P--;   //1번 플레이어는 0, 2번 플레이어는 1
		if (K == 0){  //어느 플레이어가 '한개도 가지고 있지 않다'고 말할때
			int p = (A + P) * 2, q = (B + P) * 2;  //~A1 , ~B1
			adj[oppo(p)].push_back(p);  //(~A1 V ~A1)
			adj[oppo(q)].push_back(q);  //(~B1 V ~B1)
		}
		else if (K == 1){  //어느 플레이어가 '한개 가지고 있다'고 말할때 XOR 연산
			int p = (A + P) * 2 + 1, q = (B + P) * 2 + 1; //A1 , B1
			adj[oppo(p)].push_back(q); //(A1 V B1)
			adj[oppo(q)].push_back(p); 
			adj[p].push_back(oppo(q)); //(~A1 V ~B1)
			adj[q].push_back(oppo(p));
		}
		else{   //어느 플레이어가 '둘다 가지고 있다'고 말할때
			int p = (A + P) * 2 + 1, q = (B + P) * 2 + 1;  //A1, B1
			adj[oppo(p)].push_back(p);   //(A1 V A1)
			adj[oppo(q)].push_back(q);   //(B1 V B1)
		}
	}

	int result = 0;
	bool used[26] = { 0 };
	for (int a = 0; a<26; a++){
		used[a] = true;        //black 후보가 될 수 있는 조합을 찾는 것이다. 
		for (int b = a + 1; b<26; b++){
			used[b] = true;
			for (int c = b + 1; c<26; c++){
				used[c] = true;
				for (int i = 0; i<26; i++){
					int p = i * 4, q = i * 4 + 2;   //~A1, ~A2
					if (used[i]){   // black인 카드는 제외시켜 버리고
						adj[oppo(p)].push_back(p);   //(~A1 V ~A1)
						adj[oppo(q)].push_back(q);   //(~A2 V ~A2)
					}
					else{  //black이 아닌 카드는 둘 중에 한명만 가지고 있게 한다. XOR
						adj[oppo(p)].push_back(q);   //(~A1 V ~A2)
						adj[oppo(q)].push_back(p);
						adj[p].push_back(oppo(q));   //(A1 V A2)
						adj[q].push_back(oppo(p));
					}
				}

				for (int i = 0; i<MAX * 2; i++)
					if (dfsn[i] == 0)     //dfs에서 빠져 나오는 순서대로 저장과 동시에 그룹 번호를 매김.
						dfs(i);
				bool possible = true;
				for (int i = 0; i<MAX; i++){
					if (sn[i * 2] == sn[i * 2 + 1]){   //같은 집합이니?
						possible = false;
						break;
					}
				}
				if (possible) result++;   //가능한 조합이라면 정답에 더해준다.

				for (int i = 0; i<26; i++){   //back tracking 처럼 원상복귀 시키는 코드이다.
					int p = i * 4, q = i * 4 + 2;   //~A1, ~A2
					adj[oppo(p)].pop_back();
					adj[oppo(q)].pop_back();
					if (!used[i]){
						adj[p].pop_back();
						adj[q].pop_back();
					}
				}
				cnt = SN = 0;
				fill(dfsn, dfsn + MAX * 2, 0);
				fill(finished, finished + MAX * 2, 0);

				used[c] = false;
			}
			used[b] = false;
		}
		used[a] = false;
	}
	printf("%d\n", result);
}