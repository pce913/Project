#include<stdio.h>
#include<algorithm>
using namespace std;

bool M[30][30];

int main(){
	int n;
	scanf("%d",&n);
	if (n != 3){
		printf("Woof-meow-tweet-squeek");
		return 0;
	}

	for (int i = 0; i < n; i++){
		int a, b;
		scanf("%d %d",&a,&b);
		if (a>b)
			swap(a, b);
		M[a][b] = true;
	}
	if ((M[2][3] && M[1][3] && M[2][3])){
		printf("Wa-pa-pa-pa-pa-pa-pow!");
	}
	else
		printf("Woof-meow-tweet-squeek");
	return 0;
}