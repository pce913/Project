#include<stdio.h>

int a[55];
//double D[2505][2505];  //이항계수. 이항계수를 double 형으로 구해놓아야만 맞는다. 안그러면 오버플로우 때문에 틀린다. long long도 안됨.
double nCr(int x, int y)  //double로 해야만 맞는다. 안드러면 오버플로우 때문에 틀린다.   double형으로 하면 1e300 이상의 수도 표현 가능하다.
{                              //double형 이항계수의 공간은 매우 크므로 차라리 그냥 계산하는게 낫다.
	double ans = 1.0;
	for (int i = 0; i < y; i++)
	{
		ans *= (double)(x - i);
		ans /= (double)(i + 1);
	}
	return ans;
}

int main(){
	int n = 0;
	int m, k;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++){
		scanf("%d", &a[i]);
		n += a[i];
	}
	scanf("%d", &k);
	double mother = nCr(n, k);
	double son = 0;
	for (int i = 1; i <= m; i++){
		if (a[i] < k)continue;
		son += nCr(a[i], k);
	}
	printf("%.10lf", son / mother);
	return 0;
}
//#include<stdio.h>
//
////n이 최대 2500까지 나올 수 있으므로 이항계수를 쓸 수가 없다.
///*
//첫 번째로 꺼낸 조약돌이 i번 색일 확률: A[i]/n
//두 번째로 꺼낸 조약돌이 i번 색일 확률: (A[i] - 1)/(n - 1)
//...
//k개의 조약돌이 모두 i번색 일 확률
//sum( (A[i] - j)/(n - j) )
//*/
//
//int a[55];
//int main(){
//	int n = 0;
//	int m, k;
//	scanf("%d", &m);
//	for (int i = 1; i <= m; i++){
//		scanf("%d", &a[i]);
//		n += a[i];
//	}
//	scanf("%d", &k);
//	double ans = 0;
//	for (int i = 1; i <= m; i++){
//		double temp = 1;
//		for (int j = 0; j <= k - 1; j++){
//			temp *= (double)(a[i] - j) / (n - j);
//		}
//		ans += temp;
//	}
//	printf("%.10lf", ans);
//	return 0;
//}