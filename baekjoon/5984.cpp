#include<stdio.h>
#include<algorithm>
using namespace std;

bool check[255];
int a[255];
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		a[i] = i;
	}

	check[1] = true;
	int cur = 1;
	int next;
	int getup=1;
	while (true){
		next = (cur + getup - 1)%n+1;       //1베이스. 다음에 이동할 자리를 결정한다.
		if (check[a[next]] || next==1){     //이미 한번 이동했던 소를 또 이동시키려고 한다면 답을 찾은 것이다.
			break;
		}
		check[a[next]] = true;
		swap(getup, a[next]);  //일어난 녀석이 다음 자리에 앉고 앉아 있던 녀석은 일어난다.
		cur = next;
	}
	printf("%d",getup);
	return 0;
}