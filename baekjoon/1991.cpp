#include<stdio.h>

char tree[30][2];   //0:¿ÞÂÊ ,1:¿À¸¥ÂÊ

void preorder(int node){
	printf("%c",node);
	char left = tree[node - 'A'][0];
	char right = tree[node - 'A'][1];
	if (left != '.')
		preorder(left);
	if (right != '.'){
		preorder(right);
	}
}

void inorder(int node){
	char left = tree[node - 'A'][0];
	char right = tree[node - 'A'][1];
	if (left != '.')
		inorder(left);
	printf("%c",node);
	if (right != '.'){
		inorder(right);
	}
}

void postorder(char node){
	char left = tree[node - 'A'][0];
	char right = tree[node - 'A'][1];
	if (left != '.')
		postorder(left);
	if (right != '.'){
		postorder(right);
	}
	printf("%c", node);
}

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		char x, y, z;
		scanf(" %c %c %c",&x,&y,&z);
		tree[x - 'A'][0] = y;
		tree[x - 'A'][1] = z;
	}
	preorder('A');
	printf("\n");
	inorder('A');
	printf("\n");
	postorder('A');
	return 0;
}