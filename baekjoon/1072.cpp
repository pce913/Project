#include<cstdio>
int main(){
	long long x, y,tx,ty;
	int z;
	int temp=0;
	int cnt=1;
	int rcnt = 0;

	while (scanf("%lld %lld",&x,&y)==2){
		tx = x;
		ty = y;
		z = ((double)y / x) * 100;
		temp = z;
		if (z>=99)
			printf("-1\n");
		else{
			while (true){
				x =tx+ cnt;
				y =ty+ cnt;
				
				temp = ((double)y / x) * 100;

				if (z != temp){
					if (cnt <= 1){
						rcnt += 1;
						break;
					}

					cnt = cnt / 2;
					rcnt += cnt;
					x -= cnt;
					y -= cnt;
					tx = x;
					ty = y;
					cnt = 1;
					continue;
				}

				cnt *= 2;
			}
			printf("%d\n", rcnt);
			rcnt = 0;
			cnt = 1;
		}
	}
	return 0;
}