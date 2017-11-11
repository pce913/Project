#include<stdio.h>
#include<vector>
using namespace std;                       // 구간합을 이용하므로 펜윅트리 사용

void update(vector<int>& tree,int x,int diff){
	for (int i = x;i<tree.size(); i += i&-i){                //i&-i 마지막 비트를 구한다.
		tree[i] += diff;
	}
}

int sum(vector<int>& tree,int x){
	int ans = 0;
	for (int i = x; i>0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int sum(vector<int>& tree,int left,int right){
	return sum(tree,right)-sum(tree,left-1);
}

int main(){
	int n;
	scanf("%d",&n);
	vector<int> a(n + 1);
	vector<int> tree(n + 1);
	vector<int> position(n + 1);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		position[a[i]] = i;
		update(tree, i, 1); 
	}
	int left = 1;
	int right = n;
	for (int i = 1; i <= n; i++){
		if (i&1){
			update(tree,position[left],-1);
			printf("%d\n",sum(tree,1,position[left]-1));
			left++;
		}
		else{
			update(tree, position[right], -1);
			printf("%d\n", sum(tree, position[right]+1, n));
			right--;
		}
	}
	return 0;
}