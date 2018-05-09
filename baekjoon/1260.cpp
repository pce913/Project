#include<stdio.h>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

vector<long long> A[1001];
bool check[1001];
void BFS(long long start){
	queue<long long> q;
	memset(check,false,sizeof(check));
	check[start] = true;
	q.push(start);
	printf("%d ", start);
	while (!q.empty()){
		long long node=q.front();
		q.pop();
		for (int i = 0; i < A[node].size(); i++){
			long long next = A[node][i];
			if (check[next] == false){
				printf("%d ", next);
				q.push(next);
				check[next] = true;
			}
			
		}
	}
}

void DFS(long long _node){
	stack< pair<long long,long long> > s;
	s.push(make_pair(_node,0));
	check[_node] = true;
	printf("%d ",_node);
	while (!s.empty()){
		long long node = s.top().first;
		long long  start = s.top().second;
		s.pop();
		for (long long i = start; i < A[node].size(); i++){
			long long next = A[node][i];
			if (check[next] == false){
				printf("%d ", next);
				check[next] = true;
				s.push(make_pair(node, i + 1));
				s.push(make_pair(next,0));
				break;
			}
		}
	}
}

int main(){
	int N, M;  //N 정점의 개수 , M 간선의 개수 , V 탐색을 시작할 정점의 번호
	long long V, t1, t2;
	scanf("%d %d %lld",&N,&M,&V);	
	for (int i=1;i<=M; i++){
		scanf("%lld %lld", &t1, &t2);
		A[t1].push_back(t2);
		A[t2].push_back(t1);
		check[i] = false;
	}
	for (int i = 1; i <= N; i++){
		int size = A[i].size();
		sort(&A[i][0],&(A[i][size-1])+1);
	}
	DFS(V);
	printf("\n");
	BFS(V);
	return 0;
}