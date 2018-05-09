#include<stdio.h>
const double PI = 3.1415926535897932384626433;

int main(){
	double r;
	scanf("%lf",&r);
	printf("%6lf\n",PI*r*r);
	printf("%6lf\n",2*r*r);
	return 0;
}