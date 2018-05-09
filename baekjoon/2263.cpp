#include<cstdio>
int in[100001];
int post[100001];
int position[100001];
int n;

void divide(int is,int ie,int ps,int pe){
	if (is > ie || ps > pe)
		return;

	int root = position[post[pe]];
	int left = root - is;
	printf("%d ", post[pe]);
	divide(is, root - 1, ps, ps+left- 1);               //left    //root를 더하면 안됨.
	divide(root+1 , ie, ps+left, pe-1);            //right  여기 다시보기
}
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &in[i]);
		position[in[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &post[i]);
	divide(1,n,1,n);
	return 0;
}