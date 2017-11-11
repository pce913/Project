#include<stdio.h>
#include<algorithm>
using namespace std;

int D_max[10];
int D_min[10];
int a_max[10];
int a_min[10];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= 3; i++){
		scanf("%d",&a_max[i]);
		a_min[i] = a_max[i];
		D_max[i] = a_max[i];
		D_min[i] = a_min[i];
	}
	for (int i = 2; i <= n; i++){
		for (int j = 1; j <= 3; j++){
			scanf("%d",&D_max[j]);
			D_min[j] = D_max[j];
		}
		D_max[1] += max(a_max[1], a_max[2]);
		D_max[2] += max({ a_max[1], a_max[2], a_max[3] });
		D_max[3] += max(a_max[2], a_max[3]);
		D_min[1] += min(a_min[1], a_min[2]);
		D_min[2] += min({ a_min[1], a_min[2], a_min[3] });
		D_min[3] += min(a_min[2], a_min[3]);
		for (int j = 1; j <= 3; j++){
			a_max[j] = D_max[j];
			a_min[j] = D_min[j];
		}
	}
	printf("%d %d", max({ D_max[1], D_max[2], D_max[3] }), min({D_min[1],D_min[2],D_min[3]}));
	return 0;
}