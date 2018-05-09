#include<stdio.h>
#include<stack>
using namespace std;

int main(){
	int n;
	scanf("%d",&n);
	stack<int> s;
	int num = 1;
	for (int i = 1; i <= n; i++){
		int a;
		scanf("%d",&a);
		if (a != num){
			s.push(a);
		}
		else{
			num++;
			while (!s.empty()){
				if (s.top() == num){
					s.pop();
					num++;
				}
				else{
					break;
				}
			}
			
		}
	}
	if (s.empty())
		printf("Nice");
	else
		printf("Sad");
	return 0;
}