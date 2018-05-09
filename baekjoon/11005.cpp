#include<stdio.h>
#include<string>
using namespace std;
int main(){
	int N,B;
	scanf("%d %d",&N,&B);
	string ans;
	while (N>0){
		int r = N%B;
		if (r >= 10)
			ans += (char)(r + 55);
		else
			ans += (char)(r + 48);
		N /= B;
		}
	auto it = --ans.end();
	for (;it != ans.begin();it--)
		printf("%c",*it);
	printf("%c", *it);
	return 0;
}