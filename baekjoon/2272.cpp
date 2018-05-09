#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> a;
vector<int> b;
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		a.push_back(x);
	}
	b.resize(a.size());     //O(nlog(m)) 코드이다.

	int k = 1;    //이진수 원리이다. m이 6일경우 이진수로 110 이므로 2번 shift한 값과 4번 shift한 값을 보면 된다.   
	while (k <= m){
		if (k&m){  //현재 보고 있는 비트가 켜진 경우.
			copy(a.begin(), a.end(), b.begin());
			for (int j = 0; j < a.size(); j++){
				a[j] = a[j] ^ b[(j + k) % n];
			}
		}
		k *= 2;
	}

	for (int i = 0; i < a.size(); i++){
		printf("%d\n", a[i]);
	}
	return 0;
}