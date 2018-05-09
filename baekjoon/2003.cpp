#include<stdio.h>

int a[10000];
int main(){
	int n, s;
	scanf("%d %d", &n, &s);
	for (int i = 0; i < n; i++){
		scanf("%d",&a[i]);
	}
	int left = 0;
	int right = 0;
	int sum = a[0];
	int ans = 0;
	while (right < n){ 
		if (sum < s){
			right++;
			sum += a[right];
		}
		else if (sum == s){
			ans++;
			right++;
			sum += a[right];
		}
		else if (sum > s){
			sum -= a[left];
			left++;
		}
	}
	printf("%d",ans);
	return 0;
}