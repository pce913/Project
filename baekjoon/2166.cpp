//#include<iostream>
//#include<cstring>
//#include<math.h>                  // cmath랑 math.h가 서로 다르다. cmath로 하면 오답 math.h로 하면 정답.
//using namespace std;
//
//long double sum = 0;
//int main(){
//	double x[10002];
//	double y[10002];
//	int n;
//	cin >> n;
//	for (int i = 0; i < n; i++){
//		cin >> x[i] >> y[i];
//	}
//	x[n] = x[0];
//	y[n] = y[0];
//
//	for (int i = 0; i < n; i++){
//		sum += (x[i] * y[i + 1]) / 2 - (x[i + 1] * y[i]) / 2;
//	}
//	//if (sum < 0)
//	//	sum = -sum;            //이거 하면 오답뜬다.
//
//	printf("%.1lf", fabs(sum));
//	return 0;
//}
#include<stdio.h>
#include<vector>
using namespace std;

struct Point{
	double x, y;
};

vector<Point> a;
double ccw(double x1,double y1,double x2,double y2,double x3,double y3){
	return (double)((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1));
}


int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		double x, y;
		scanf("%lf %lf",&x,&y);
		a.push_back({ x, y });
	}
	a.push_back(a[0]);

    long double ans = 0;
	double x1 = a[0].x;
	double y1 = a[0].y;
	for (int i = 0; i < a.size() - 2 ; i++){
		double x2 = a[i + 1].x;
		double y2 = a[i + 1].y;
		double x3 = a[i + 2].x;
		double y3 = a[i + 2].y;
		ans += ccw(x1, y1, x2, y2, x3, y3) / 2.0;
	}
	if (ans < 0)
		ans = -ans;

	printf("%.1Lf",ans);
	return 0;
}