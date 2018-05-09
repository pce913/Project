#include<iostream>
using namespace std;
long double n, l, w, h;

bool go(long double len){
	long long a1=(long long)(l / len);
	long long a2 = (long long)(w / len);
	long long a3 = (long long)(h / len);
	return a1*a2*a3 >= n;
}

int main(){
	cin >> n >> l >> w >> h;
	long double left = 0;
	long double right = 1e15;
	long double ans = 0;
	while (right - left >= 1e-9){
		long double mid = (left + right) / 2;
		if (go(mid)){
			ans = mid;
			left = mid;
		}
		else{
			right = mid;
		}
	}
	printf("%.10Lf",ans);
	return 0;
}