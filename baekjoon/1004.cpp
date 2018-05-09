#include<stdio.h>

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int x1, x2, y1, y2,cx,cy,r;
		int n;
		int ans = 0;
		
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		scanf("%d",&n);
		for (int i = 0; i < n; i++){
			scanf("%d %d %d", &cx, &cy, &r);
			bool isSameCircle1 = false;
			bool isSameCircle2 = false;
			if ((x1 - cx)*(x1 - cx) + (y1 - cy)*(y1 - cy) < r*r){
				ans++;
				isSameCircle1 = true;
			}
			if ((x2 - cx)*(x2 - cx) + (y2 - cy)*(y2 - cy) < r*r){
				ans++;
				isSameCircle2 = true;
			}
			if (isSameCircle1 && isSameCircle2){
				ans -= 2;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}