#include<stdio.h>
int n, L;
int parent[300005];
bool check[300005];   //서랍이 비어있는지 차있는지 체크.

/*
http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220791837179
	술 병을 넣은 쪽을 항상 자식쪽으로 만든 후에 Union 시킨다.
	그렇게 되면 각 집합의 루트노드만 확인해주면 된다.
*/

int Find(int x){
	return x == parent[x] ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y){    //y: 술병을 넣은쪽
	parent[y] = x;
	printf("LADICA\n");
}

void init(){
	for (int i = 1; i <= L; i++){
		parent[i] = i;
	}
}

int main(){
	scanf("%d %d", &n, &L);
	init();
	for (int qq = 1; qq <= n; qq++){
		int a, b;
		scanf("%d %d", &a, &b);
		if (!check[a]){  //규칙 1 적용
			check[a] = true;
			Union(Find(b), Find(a));
		}
		else if (!check[b]){   //규칙 2 적용
			check[b] = true;
			Union(Find(a), Find(b));
		}
		else{
			a = Find(a), b = Find(b);
			if (!check[a]){    //규칙 3 적용
				check[a] = true;
				Union(b, a);
			}
			else if (!check[b]){  //규칙 4 적용
				check[b] = true;
				Union(a, b);
			}
			else{
				printf("SMECE\n");
			}
		}
	}
	return 0;
}