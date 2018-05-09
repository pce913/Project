#include<stdio.h>
#include<stack>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<set>
using namespace std;

vector<long long> a[500005], r[500005], Ascc[500005];
long long atm[500005], SccAtm[500005], D[500005], whatGroup[500005];
bool isRest[500005], isRestScc[500005];
bool check[500005];
stack<long long> st;
set<long long> check_st[500005];
long long n, m, s, p, gnum;
void attach_num(long long node){
	check[node] = true;
	for (long long i = 0; i < a[node].size(); i++){
		long long next = a[node][i];
		if (!check[next]){
			attach_num(next);
		}
	}
	st.push(node);
}

void make_scc(long long node, long long gnum){
	check[node] = true;
	whatGroup[node] = gnum;
	for (long long i = 0; i < r[node].size(); i++){
		long long next = r[node][i];
		if (!check[next]){
			make_scc(next, gnum);
		}
	}
}

void check_node(int node){
	check[node] = true;
	for (int i = 0; i < Ascc[node].size(); i++){
		int next = Ascc[node][i];
		if (!check[next]){
			check_node(next);
		}
	}
}

void go(){
	D[whatGroup[s]] = SccAtm[whatGroup[s]];
	for (long long i = whatGroup[s]; i <= gnum; i++){
		if (!check[i])
			continue;
		for (long long next : Ascc[i]){
			D[next] = max(D[next], D[i] + SccAtm[next]);
		}
	}
}

int main(){
	scanf("%lld %lld", &n, &m);
	for (long long i = 0; i < m; i++){
		long long x, y;
		scanf("%lld %lld", &x, &y);
		a[x].push_back(y);
		r[y].push_back(x);
	}
	for (long long i = 1; i <= n; i++){
		scanf("%lld", &atm[i]);
	}
	scanf("%lld %lld", &s, &p);
	for (long long i = 0; i < p; i++){
		long long x;
		scanf("%lld", &x);
		isRest[x] = true;
	}
	////////////
	for (long long i = 1; i <= n; i++){
		if (!check[i]){
			attach_num(i);
		}
	}
	memset(check, false, sizeof(check));
	while (!st.empty()){
		long long node = st.top();
		st.pop();
		if (!check[node]){
			make_scc(node, ++gnum);
		}
	}

	//scc로 다시 그래프를 구성해야 함.
	for (long long i = 1; i <= n; i++){
		SccAtm[whatGroup[i]] += atm[i];
		if (isRest[i])
			isRestScc[whatGroup[i]] = true;
		for (long long next : a[i]){
			if (whatGroup[i] != whatGroup[next]){  //이렇게만 해도 알아서 DAG가 된다.
				if (check_st[whatGroup[i]].count(whatGroup[next]) == 0){
					check_st[whatGroup[i]].insert(whatGroup[next]);
					Ascc[whatGroup[i]].push_back(whatGroup[next]);
				}
			}
		}
	}
	memset(check, false, sizeof(check));
	check_node(whatGroup[s]);

	//코사라쥬를 쓰면 SCC가 위상 정렬 순서대로 묶임을 이용하자.
	go();
	long long ans = 0;
	for (long long i = 1; i <= gnum; i++){
		if (isRestScc[i]){
			ans = max(ans, D[i]);
		}
	}
	printf("%lld", ans);
	return 0;
}