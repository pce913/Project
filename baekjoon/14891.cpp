#include<stdio.h>

int wheel[5][15];
int point[5][5];
void go_circle(int arr[]){  //시계방향 회전 done
	int one = arr[8];
	for (int i = 8; i >= 2; i--){
		arr[i] = arr[i - 1];
	}
	arr[1] = one;
}

void go_counter(int arr[]){  //반시계방향 회전 done
	int eight = arr[1];
	for (int i = 1; i <= 7; i++){
		arr[i] = arr[i + 1];
	}
	arr[8] = eight;
}
//3시 방향 3번, 9시방향 7번
void solve(int x, int d, int before){  //d==1 시계방향 회전, d==0 반시계방향 회전
	bool move_left = false, move_right = false;
	if (x < 4){//오른쪽 확인
		if (x + 1 != before && wheel[x][3] != wheel[x + 1][7]){
			move_right = true;
		}
	}
	if (x > 1){  //왼쪽 확인
		if (x - 1 != before && wheel[x][7] != wheel[x - 1][3]){
			move_left = true;
		}
	}
	d == 1 ? go_circle(wheel[x]) : go_counter(wheel[x]);
	
	if (move_right)
		solve(x + 1, !d, x);
	if (move_left)
		solve(x - 1, !d, x);
}

void init(){
	point[1][1] = 1;
	point[2][1] = 2;
	point[3][1] = 4;
	point[4][1] = 8;
}

int main(){
	init();
	for (int i = 1; i <= 4; i++){
		for (int j = 1; j <= 8; j++){
			scanf("%1d",&wheel[i][j]);
		}
	}
	int k;
	scanf("%d",&k); 
	for (int qq = 0; qq < k; qq++){
		int x, d;
		scanf("%d %d",&x,&d);
		if (d == -1)
			d = 0;
		solve(x, d, -1);
	}
	int ans = 0;
	for (int i = 1; i <= 4; i++){
		ans += point[i][wheel[i][1]];
	}
	printf("%d",ans);
	return 0;
}