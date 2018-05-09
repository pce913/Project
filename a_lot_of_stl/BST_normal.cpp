#include<stdio.h>
#include<vector>
using namespace std;
//바이너리서치 트리를 사용하는 경우. 어떤 원소가 존재하니? 를 묻는 쿼리가 자주 들어오는 경우.
//밑에 내가 짠 버젼은 아직 완성된 버젼이 아니다. 꼼꼼히 다시보자.
//http://blog.eairship.kr/248 참고하기.
struct Tree{
	int val;
	int left, right;
	Tree(){
		val = left = right = -1;
	}
};
Tree tree[10005];
vector<int> pull;
int BN;
int root;  //루트노드를 지웠을때 처리해주기.
int make_node(){
	tree[pull[BN]] = Tree();
	return pull[BN++];
}

void insert(int cur,int x){
	if (x < tree[cur].val){
		if (tree[cur].left != -1)insert(tree[cur].left, x);
		else{
			tree[cur].left = make_node();
			tree[tree[cur].left].val = x;
		}
	}
	else if (x > tree[cur].val){
		if (tree[cur].right != -1)insert(tree[cur].right, x);
		else{
			tree[cur].right = make_node();
			tree[tree[cur].right].val = x;
		}
	}
}

int find_min_node(int cur){
	if (tree[cur].val == -1)return -1;
	if (tree[cur].left != -1)return find_min_node(tree[cur].left);
	else return cur;
}

int erase(int cur,int x){
	if (x < tree[cur].val)tree[cur].left = erase(tree[cur].left, x);
	else if (x > tree[cur].val)tree[cur].right = erase(tree[cur].right, x);
	else{
		if (tree[cur].left != -1 && tree[cur].right != -1){
			int temp = find_min_node(tree[cur].right);
			tree[cur].val = tree[temp].val;
			tree[cur].right = erase(tree[cur].right, tree[temp].val);
		}
		else{
			int temp = cur;
			if (tree[cur].left == -1)cur = tree[cur].right;
			else if (tree[cur].right == -1)cur = tree[cur].left;
			pull.push_back(temp);
		}
	}
	return cur;
}


int main(){
	for (int i = 0; i <= 10000; i++)
		pull.push_back(i);   //삭제될때마다 push_back 할 것이다.

	return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct Node
//{
//	Node* Left;
//	Node* Right;
//	int Data;
//} Node;
//
//Node* createNode(int data)
//{
//	Node* newNode = (Node*)malloc(sizeof(Node));
//	newNode->Left = NULL;
//	newNode->Right = NULL;
//	newNode->Data = data;
//
//	return newNode;
//}
//
//Node* searchNode(Node* Tree, int findData)
//{
//	if (Tree == NULL) return NULL;
//	if (Tree->Data == findData)
//		return Tree;
//	else if (Tree->Data > findData)
//		searchNode(Tree->Left, findData);
//	else
//		searchNode(Tree->Right, findData);
//}
//
//void insertNode(Node* Tree, Node* newNode)
//{
//	if (newNode->Data > Tree->Data)
//	{
//		if (Tree->Right != NULL) insertNode(Tree->Right, newNode);
//		else Tree->Right = newNode;
//	}
//	else if (newNode->Data < Tree->Data)
//	{
//		if (Tree->Left != NULL) insertNode(Tree->Left, newNode);
//		else Tree->Left = newNode;
//	}
//}
//
//Node* findMinNode(Node* Tree)
//{
//	if (Tree == NULL) return NULL;
//	if (Tree->Left != NULL) return findMinNode(Tree->Left);
//	else return Tree;
//}
//
//Node* removeNode(Node* Tree, int data)
//{
//	Node* tempNode;
//
//	if (Tree == NULL) printf("해당하는 노드를 찾을 수 없습니다.\n");
//	else if (Tree->Data > data) Tree->Left = removeNode(Tree->Left, data);
//	else if (Tree->Data < data) Tree->Right = removeNode(Tree->Right, data);
//	else
//	{
//		if (Tree->Left != NULL && Tree->Right != NULL)
//		{
//			tempNode = findMinNode(Tree->Right);
//			Tree->Data = tempNode->Data;
//
//			Tree->Right = removeNode(Tree->Right, tempNode->Data);
//		}
//		else
//		{
//			tempNode = Tree;
//			if (Tree->Left == NULL) Tree = Tree->Right;
//			else if (Tree->Right == NULL) Tree = Tree->Left;
//			free(tempNode);
//		}
//	}
//
//	return Tree;
//}
//
//void printTree(Node* Tree)
//{
//	if (Tree == NULL) return;
//	printTree(Tree->Left);
//	printf("%d ", Tree->Data);
//	printTree(Tree->Right);
//}
//
//int main()
//{
//	Node* Tree = createNode(10);
//	Node* findNode;
//	int input;
//
//	insertNode(Tree, createNode(5));
//	insertNode(Tree, createNode(1));
//	insertNode(Tree, createNode(6));
//	insertNode(Tree, createNode(17));
//	insertNode(Tree, createNode(14));
//	insertNode(Tree, createNode(21));
//
//	while (1)
//	{
//		scanf("%d", &input);
//		findNode = searchNode(Tree, input);
//
//		if (findNode != NULL)
//		{
//			printf("해당 노드를 찾았습니다! 노드를 제거합니다. 노드의 위치는 %#x 입니다.\n", findNode);
//			removeNode(Tree, input);
//			printf("현재 트리 출력: ");
//			printTree(Tree); printf("\n");
//		}
//		else printf("노드를 찾을 수 없었습니다.\n");
//
//	}
//	return 0;
//}