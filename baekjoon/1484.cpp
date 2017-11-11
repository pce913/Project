#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

vector<long long> ans;
vector<long long> check;

int main(){
	for (long long i = 1; i <= 100000; i++){
		check.push_back(i*i);
	}
	long long n;
	scanf("%lld", &n);

	long long k = 1;
	while (true){
		long long num = n + k*k;    //c^2
		double what = sqrt(num);
		if (2 * what - 1 > n)    // G= c^2 - b^2 라고 했을때 b는 아무리 커봐야 c-1보다 커질 수 없다.
			break;             //따라서 G= c^2 - (c-1)^2로 식을 놓고 정리하면 2*c-1 > n 일때는 절대 답이 존재하지 않는다.

		if (binary_search(check.begin(), check.end(), num)){
			ans.push_back((long long)sqrt(num));
		}
		k++;
	}



	if (ans.empty()){
		printf("-1");
	}
	else{
		for (int i = 0; i < ans.size(); i++){
			printf("%lld\n", ans[i]);
		}
	}
	return 0;
}