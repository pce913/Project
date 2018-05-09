#include<stdio.h>
#include<cmath>

struct Node{
	int left, right;
};

Node tree[1000005]; 

void post(int x){
	if (tree[x].left != 0){
		post(tree[x].left);
	}
	if (tree[x].right != 0){
		post(tree[x].right);
	}
	printf("%d\n",x);
}

void make_tree(int cur,int x){
	if (x > cur){
		if (tree[cur].right != 0){
			make_tree(tree[cur].right, x);
		}
		else{
			tree[cur].right = x;
			return;
		}
	}
	else{
		if (tree[cur].left != 0){
			make_tree(tree[cur].left, x);
		}
		else{
			tree[cur].left = x;
			return;
		}
	}
}

int main(){
	int root;
	scanf("%d", &root);   //루트를 아는것이 중요하다. 중위 탐색 이므로 첫번째 input이 바로 root가 된다.
	
	int x;
	while (scanf("%d", &x) == 1){
		make_tree(root, x);
	}
	post(root);
	return 0;
}
//#include<stdio.h>
//#include<cmath>
//
//int tree[10000005];   //skewed 한 형태를 고려한 tree 사이즈
//void post(int node){
//	if (tree[node]==0)
//		return;
//
//	post(2 * node);
//	post(2 * node + 1);
//	printf("%d\n",tree[node]);
//}
//
//void make_tree(int node,int what){
//	if (tree[node]==0){
//		tree[node] = what;
//		return;
//	}
//
//	if (tree[node] > what){  //왼쪽으로 가는 경우
//		make_tree(2 * node, what);
//	}
//	else{  //오른쪽으로 가는 경우
//		make_tree(2 * node + 1, what);
//	}
//}
//
//int main(){
//	int root;
//	scanf("%d",&root);   //루트를 아는것이 중요하다. 중위 탐색 이므로 첫번째 input이 바로 root가 된다.
//	tree[1] = root;
//	int x;
//	while (scanf("%d", &x) == 1){
//		make_tree(1, x);
//	}
//	post(1);
//	return 0;
//}