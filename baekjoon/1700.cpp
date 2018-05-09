#include<stdio.h>

const int INF = 1e9;
int a[105], nexts[105], loc[105], plug[105];
int main(){
	int n, k;
	scanf("%d %d",&n,&k);
	for (int i = 1; i <= k; i++){
		scanf("%d",&a[i]);
		nexts[i] = INF;
	}
	for (int i = k; i >= 1; i--){
		if (loc[a[i]])
			nexts[i] = loc[a[i]];
		loc[a[i]] = i;
	}

	int ans = 0;
	for (int i = 1; i <= k; i++){
		bool isPut = false;
		for (int j = 1; j <= n; j++){
			if (a[plug[j]] == a[i] || !plug[j]){   //이미 꽂혀있는경우 처리, 플러그가 비어있는경우 처리
				plug[j] = i;  //인덱스
				isPut = true;
				break;
			}
		}
		if (isPut)continue;

		int maxi = 0, mplug_idx = 0;
		for (int j = 1; j <= n; j++){
			if (maxi < nexts[plug[j]]){
				maxi = nexts[plug[j]];
				mplug_idx = j;
			}
		}
		plug[mplug_idx] = i;
		ans++;
	}
	printf("%d",ans);
	return 0;
}