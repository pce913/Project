#include<stdio.h>
#include<vector>
using namespace std;

int a[2005];
vector<int> dans[15];
int k;

void inorder(int index, int before ,int depth){
	if (index <= 0 || index > (1<<k) || depth > k)
		return;

	int lidx, ridx;
	if (before > index){
		lidx = index - (before - index + 1) / 2;
		ridx =  index + (before - index + 1) / 2;
	}
	else{
		lidx = index - (index - before + 1) / 2;
		ridx = index + (index - before + 1) / 2;
	}

	inorder(lidx, index ,depth + 1);
	dans[depth].push_back(a[index]);
	inorder(ridx , index ,depth + 1);
}

int main(){
	scanf("%d",&k);
	int len = (1 << k)-1;
	for (int i = 1; i <= len; i++){
		scanf("%d",&a[i]);
	}
	int ridx = (len + 1) / 2;
	int root = a[ridx];
	inorder(ridx, len ,1);
	for (int i = 1; i <= k; i++){
		for (int j = 0; j < dans[i].size(); j++){
			printf("%d ",dans[i][j]);
		}
		printf("\n");
	}
	return 0;
}