//#include<stdio.h>
//long long n;
//long long M[6][6];
//void mult(){
//	for (long long i = 1; i <= n; i++){
//		for (long long j = 1; j <= n; j++){
//			for (long long k = 1; k <= n; k++){
//				M[i][j] += M[i][k] * M[k][j];
//			}
//		}
//	}
//}
//
//long long* calc(long long b){
//	if (b == 0){
//		return 1;
//	}
//	else if (b == 1){
//		return M;
//	}
//	else if (b % 2 == 0){
//		calc(b / 2);
//	}
//}
//
//long long main(){
//
//	long long b;
//	scanf("%lld %lld",&n,&b);
//	for (long long i = 1; i <= n; i++){
//		for (long long j = 2; j <= n; j++){
//			scanf("%d",&M[i][j]);
//		}
//	}
//	calc(M);
//
//	return 0;
//}
#include<stdio.h>
#include<vector>
using namespace std;

vector< vector<long long> > matrix_multiplication(const vector< vector<long long> >& a,const vector< vector<long long> >& b){
	long long n = a[0].size();
	vector< vector<long long> > c(n, vector<long long>(n));
	for (long long i = 0; i < n; i++){
		for (long long j = 0; j < n; j++){
			for (long long k = 0; k < n; k++){
				c[i][j] += (a[i][k] * b[k][j])%1000;
			}
			c[i][j] %= 1000;
		}
	}
	return c;
}

//vector< vector<long long> > calc(const vector< vector<long long> >& a,const vector< vector<long long> >& I, long long b){
//	if (b == 0)
//		return I;
//	else if (b == 1)
//		return a;
//	else if (b % 2 == 0){
//		auto temp = calc(a, I,b / 2);
//		return matrix_multiplication(temp, temp);
//	}
//	else{
//		return matrix_multiplication(a,calc(a,I,b-1));
//	}
//}


int main(){
	long long n;
	long long b;
	scanf("%lld %lld",&n,&b);
	vector< vector<long long> > a(n,vector<long long>(n));
	vector< vector<long long> > I(n, vector<long long>(n));

	vector< vector<long long> > ans(n, vector<long long>(n));
	for (long long i = 0; i < n; i++){
		for (long long j = 0; j < n; j++){
			scanf("%lld", &a[i][j]);
		}
		//I[i][i] = 1;
		ans[i][i] = 1;
	}
	
	//auto ans = calc(a,I,b);
	while (b > 0){
		if (b % 2 == 1){
			ans = matrix_multiplication(ans, a);
		}
		a = matrix_multiplication(a,a);
		b /= 2;
	}
	for (long long i = 0; i < ans.size(); i++){
		for (long long j = 0; j < ans[i].size(); j++){
			printf("%lld ",ans[i][j]%1000);
		}
		printf("\n");
	}
	return 0;
}