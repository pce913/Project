#include<stdio.h>

int a[100000];
int main(){
	const int INF = 100000000;
	int n, s;
	scanf("%d %d", &n, &s);
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	int left = 0;
	int right = 0;
	int sum = a[0];
	int ans = INF;
	while (right < n){
		if (sum < s){
			right++;
			sum += a[right];
		}
		else if (sum == s){
			if (ans> right - left + 1){
				ans = right - left + 1;
			}
			right++;
			sum += a[right];
		}
		else if (sum > s){
			if (ans > right - left + 1){
				ans = right - left + 1;
			}
			sum -= a[left];
			left++;
		}
	}
	if (ans == INF)
		ans = 0;
	printf("%d", ans);
	return 0;
}