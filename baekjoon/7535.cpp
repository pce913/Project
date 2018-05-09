#include<cstdio>
int check[4005];
int n;
int TC;
int a[4005][4005], r[4005][4005];
int an[4005], rn[4005];
int stk[4005];
int sn;
int grp[4005];
void init(){
	TC++;
	for (int i = 1; i <= 2*n; i++){
		an[i] = rn[i] = 0;
	}
	sn = 0;
}

int convert(int x){
	return x > n ? x - n : x + n;
}

void add_edge(int x,int y){
	a[convert(x)][an[convert(x)]++] = y;
	a[convert(y)][an[convert(y)]++] = x;
	r[y][rn[y]++] = convert(x);
	r[x][rn[x]++] = convert(y);

	a[x][an[x]++] = convert(y);
	a[y][an[y]++] = convert(x);
	r[convert(y)][rn[convert(y)]++] = x;
	r[convert(x)][rn[convert(x)]++] = y;
}

void dfs_rev(int node,int gnum){
	check[node] = TC;
	grp[node] = gnum;
	for (int i = 0; i < rn[node]; i++){
		int next = r[node][i];
		if (check[next] != TC){
			dfs_rev(next, gnum);
		}
	}
}

void dfs(int node){
	check[node] = TC;
	for (int i = 0; i < an[node]; i++){
		int next = a[node][i];
		if (check[next]!=TC){
			dfs(next);
		}
	}
	stk[sn++] = node;
}

void solve(int test){
	init();
	int q;
	scanf("%d %d",&n,&q);
	for (int i = 0; i < q; i++){
		int x, y;
		scanf("%d %d",&x,&y); //xor 절을 추가하면 된다.
		add_edge(x, y);
	}
	for (int i = 1; i <= 2 * n; i++){
		if (check[i]!=TC){
			dfs(i);
		}
	}

	TC++;
	int GN = 0;
	while (sn){
		int node = stk[--sn];
		if (check[node] != TC){
			dfs_rev(node, ++GN);
		}
	}

	bool isAns = 1;
	for (int i = 1; i <= n; i++){
		if (grp[i] == grp[i + n]){
			isAns = 0;
			break;
		}
	}
	printf("Scenario #%d:\n%s\n\n", test, isAns ? "No suspicious bugs found!" : "Suspicious bugs found!");
}

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 1; test <= T; test++)
		solve(test);
	return 0;
}