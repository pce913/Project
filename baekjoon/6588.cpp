#include <stdio.h>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN = 1000005;
bool check[MAXN+1]; 

vector<int> prime;
int main() {
	memset(check, true, sizeof(check));
	for (int i = 2; i*i <= 1000000; i++) {
		if (check[i]) {
			prime.push_back(i);
			for (int j = i*i; j <= 1000000; j += i) {
				check[j] = false;
			}
		}
	}
	while (true) {
		int n;
		scanf("%d",&n);
		if (n == 0) {
			break;
		}
		for (int i = 0; i < prime.size(); i++) {
			if (check[n - prime[i]]) {
				printf("%d = %d + %d\n",n,prime[i],n - prime[i]);
				break;
			}
		}
	}
	return 0;
}