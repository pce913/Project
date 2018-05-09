#include<stdio.h>
#include<vector>
#include<cstring>
using namespace std;

vector<int> v[501];
bool visit[501];
int vertex, edge;
bool isTree;

void dfs(int n,int from)
{
	visit[n] = true;
	for (int i = 0; i < v[n].size(); i++)
	{

		int next = v[n][i];
		if (next == from)
			continue;

		if (!visit[next]){
			dfs(next,n);
		}	
		else{
			isTree = false;
			break;
		}
	}
}

int main()
{
	int n, m;
	int count = 0;
	while (1)
	{
		count++;
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;

		for (int i = 1; i <= 500; i++)
		{
			v[i].clear();
		}
		memset(visit, false, sizeof(visit));

		for (int i = 0; i < m; i++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			v[a].push_back(b);
			v[b].push_back(a);
		}

		int t = 0;
		for (int i = 1; i <= n; i++)
		{
			vertex = 0;
			edge = 0;
			isTree = true;
			if (!visit[i]){
				dfs(i,-1);
				if (isTree)
					t++;
			}
			
		}
		if (t == 0)
			printf("Case %d: No trees.\n", count);
		if (t == 1)
			printf("Case %d: There is one tree.\n", count);
		if (t>1)
			printf("Case %d: A forest of %d trees.\n", count, t);
	}
	return 0;
}
