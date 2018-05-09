#include <stdio.h>
#include<vector>
using namespace std;
vector<char> ans;
int main(){
	int n;
	scanf("%d", &n);
	if (n == 0){
		printf("0");
		return 0;
	}

	while (n != 0){
		if (n%-2 == 0){   //n의 부호가 어찌됐든 나누어 떨어진다면
			n /= -2;
			ans.push_back('0');
		}
		else{  //나누어 떨어지지 않을때는 나머지가 -1이 나오지 않도록 조심해야 한다.   7 % -2 = 1   , -7 % 2 = -1 , -7 % -2 = -1. 즉, 앞쪽의 부호를 따라간다.
			if (n > 0){
				n /= -2;
			}
			else{
				n = (n - 1) / -2;
			}
			ans.push_back('1');
		}
	}
	for (auto it = ans.rbegin(); it != ans.rend(); it++){
		printf("%c",*it);
	}
	return 0;
}