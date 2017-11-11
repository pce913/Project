#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace  std;
const int MAXN = 100005;
vector<int> adj[MAXN],children[MAXN];
int low[MAXN], num[MAXN],finish[MAXN];           //finish[node] : node에서 빠져 나올때의 매긴 번호.
bool check[MAXN];
int cnt = 0;

void dfs(int node, int parent){
	check[node] = true;
	num[node] = low[node] = ++cnt;
	for (int next : adj[node]){
		if (next == parent)
			continue;
		if (!check[next]){   //tree edge
			dfs(next, node);
			low[node] = min(low[node], low[next]);
			children[node].push_back(next);
		}
		else{  //back edge
			low[node] = min(low[node], num[next]);
		}
	}
	finish[node] = ++cnt;
}

bool is_descendant(int x,int y){  //x가 y의 후손이니?  ok
	return num[x] >= num[y] && finish[x] <= finish[y];
}

int find_related_child(int x,int y){  //x를 루트로 하는 subtree에서 y는 그 중 어느 child에 붙어 있니?
	int left = 0;
	int right = children[x].size() - 1;
	int mid;
	while (left <= right){
		mid = (left + right) >> 1;
		int c = children[x][mid];
		if (finish[c] < num[y]){         //y가 mid보다 오른쪽 자식에 달려 있는 경우
			left = mid + 1;
		}
		else if (num[c] > finish[y]){  //y가 mid보다 왼쪽 자식에 달려 있는 경우
			right = mid - 1;
		}
		else{
			break;
		}
	}
	return children[x][mid];
}

int main(){
	int n, e;
	scanf("%d %d",&n,&e);
	for (int i = 0; i < e; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1,-1);

	int qq;
	scanf("%d",&qq);
	for (int que = 0; que < qq; que++){
		int what;
		scanf("%d",&what);
		if (what == 1){   //단절선 쿼리
			int a, b, g1, g2;
			scanf("%d %d %d %d",&a,&b,&g1,&g2);
			if (is_descendant(g1, g2))
				swap(g1, g2);
			
			if (low[g2] <= num[g1]){   //위로 올라가는 간선이 있다. 즉, 단절선이 아니다.
				printf("yes\n");
			}
			else if (is_descendant(a,g2) == is_descendant(b, g2)){ //단절선일때. 즉, a랑 b가 같은 조상을 가지고 있거나, a랑 b가 둘다 다른 조상을 가지고 있거나. ok
				printf("yes\n");
			}
			else{
				printf("no\n");
			}
		}
		else if(what == 2){  //단절점 쿼리.
			int a, b, c;
			scanf("%d %d %d",&a,&b,&c);
			if (!is_descendant(a, c) && !is_descendant(b, c)){   //a가 c의 후손도 아니고 b도 c의 후손이 아닌경우. 
				printf("yes\n");
			}
			else if (is_descendant(a, c) && is_descendant(b, c)){  //a,b둘다 c의 후손인 경우
				int a_rel = find_related_child(c, a);
				int b_rel = find_related_child(c, b);
				if (a_rel == b_rel){   //a와 b가 같은 child에 달려 있는 경우.
					printf("yes\n");
				}
				else if (low[a_rel] < num[c] && low[b_rel] < num[c]){   //a가 속한곳의 child와 b가 속한곳의 child가 둘다 c를 넘는 백엣지를 가지고 있니?
					printf("yes\n");
				}
				else{
					printf("no\n");
				}
			}
			else{      //a,b 둘중 하나는 c의 후손이고 다른 하나는 아닌 경우
				if (is_descendant(a, c))    //a가 c의 후손이니?
					swap(a, b);   //b를 일단 밑으로 본다.
				int b_rel = find_related_child(c, b);
				if (low[b_rel] < num[c]){  //b가 속한곳의 child가 c를 넘어서는 엣지를 가지고 있니?
					printf("yes\n");
				}
				else{
					printf("no\n");
				}
			}
		}
	}
	return 0;
}