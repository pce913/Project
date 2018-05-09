#include<stdio.h>
#include<algorithm>
using namespace std;
int a[5000001];                //nth_element를 사용하면 더 빠르게 풀 수 있다.
int main(){
	int n,k;
	scanf("%d %d",&n,&k);
	for (int i = 0; i < n; i++){
		scanf("%d",&a[i]);
	}
	//sort(a, a + n);
	nth_element(a,a+k-1,a+n);
	printf("%d",a[k-1]);
	return 0;
}