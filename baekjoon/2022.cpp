#include<stdio.h>
#include<cmath>
#define MIN(a,b) ((a) < (b) ? (a) : (b))
using namespace std;

int main(){
	double x, y, c;
	while (scanf("%lf %lf %lf", &x, &y, &c) == 3){
		double l = 0;
		double r = MIN(x, y);
		double m;
		while (abs(r - l)> 1e-6){
			m = (l + r) / 2.0;
			double h1 = sqrt(x*x - m*m);
			double h2 = sqrt(y*y - m*m);
			double h = (h1*h2) / (h1 + h2);
			if (h > c)
				l = m;
			else
				r = m;	
		}
		printf("%.3lf\n", m);
	}
	return 0;
}