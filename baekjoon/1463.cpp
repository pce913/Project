#include<stdio.h>
#include<algorithm>
using namespace std;

int D[1000001];
int main(){
	int n;
	scanf("%d",&n);
	D[1] = 0;
	D[2] = 1;
	D[3] = 1;

	for (int i = 4; i <= n; i++){
		bool a, b;
		a = b = false;
		if (i % 3 == 0)
			a = true;
		if (i % 2 == 0)
			b = true;

		if (a && b)
			D[i] = min({ D[i / 3], D[i / 2], D[i - 1] })+1;
		else if (a && !b)
			D[i] = min(D[i / 3], D[i - 1])+1;
		else if (!a && b)
			D[i] = min(D[i / 2], D[i - 1]) + 1;
		else
			D[i] = D[i - 1] + 1;
	}
	printf("%d",D[n]);
	return 0;
}