#include<stdio.h>
#include<vector>
using namespace std;

void update(vector<int>& tree,int x,int diff){                     // 펜윅트리 사용
	for (int i = x; i < tree.size(); i += i&-i){
		tree[i] += diff;
	}
}

int sum(vector<int>& tree, int x){
	int ans = 0;
	for (int i = x; i>0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int n, m;
		scanf("%d %d",&n,&m);
		vector<int> tree(n + m + 1);                  // 영화를 올릴 갯수만큼 트리를 더 만들어 준다.
		vector<int> position(n + 1);               // 숫자가 있던 원래의 위치를 저장하는 배열
		for (int i = 1; i <= n; i++){
			update(tree,m+i,1);
			position[i] = m + i;
		}
		for (int i = 0; i < m; i++){
			int x;
			scanf("%d",&x);
			printf("%d ",sum(tree,position[x]-1));
			update(tree,position[x],-1);               // 영화를 빼서 위로 올린다.
			position[x] = m-i;
			update(tree, position[x], 1);           // 맨 꼭대기에 새롭게 올려진 영화에 대해 update 한다.
		}
		printf("\n");
	}
	return 0;
}