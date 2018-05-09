#include<stdio.h>
#include<algorithm>
using namespace std;

int lr[100005][2];
bool check[100005];
int cnt = 1;
int depth_max[100005];
int depth_min[100005];
void inorder(int node,int depth){
	if (lr[node][0] == 0 && lr[node][1] == 0){
		depth_max[depth] = max(depth_max[depth], cnt);
		depth_min[depth] = min(depth_min[depth], cnt);
		cnt++;
		return;
	}
	if (lr[node][0]!=0)
		inorder(lr[node][0],depth+1);
	depth_max[depth] = max(depth_max[depth], cnt);
	depth_min[depth] = min(depth_min[depth], cnt);
	cnt++;
	if (lr[node][1]!=0)
		inorder(lr[node][1],depth+1);
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		depth_min[i] = 1e9;
	}
	for (int i = 0; i < n; i++){
		int node, l, r;
		scanf("%d %d %d",&node,&l,&r);
		if (l != -1){
			lr[node][0] = l;
			check[l] = true;
		}
		if (r != -1){
			lr[node][1] = r;
			check[r] = true;
		}
	}
	int root = 0;
	for (int i = 1; i <= n; i++){
		if (!check[i]){
			root = i;
			break;
		}
	}
	inorder(root,1);

	int ans = 0;
	int ad = 0;
	for (int i = 1; i <= n; i++){
		if (ans < depth_max[i]-depth_min[i]+1){
			ans = depth_max[i] - depth_min[i] + 1;
			ad = i;
		}
	}
	printf("%d %d",ad,ans);
	return 0;
}