#include<stdio.h>

int n, m;
   //왼쪽에서 오른쪽으로 , 위에서 아래쪽으로 차례대로 0 1 2 3 4 .. n*m-1번 칸
                                      // 격자판의 한 칸을 채우는 방법은  ㅁ- 이렇게 놓는 경우랑 ㅁ  이런식으로 2가지 방법만 있다고 생각하면 된다.
																				//               |
int D[14 * 14][1 << 14];             //D[N][S] : N번째 칸을 채울것이고, N번째 칸부터 칸 M개의 상태가 S일때 경우의 수.
bool check[14 * 14][1 << 14];

int go(int num,int mask){
	if (num == n*m && mask == 0){           //마지막 까지 도달했을때 mask가 0이면
		return 1;                            //격자판의 바로 밑부분이 모두 0이라는 뜻이므로 격자판을 잘 채웠다는 뜻이 된다.
	}
	if (num >= n*m){              //마지막까지 도달했을때 mask가 0이 아니라면 격자판을 잘못 채운 것이므로 0 리턴.
		return 0;
	}

	if (check[num][mask]){
		return D[num][mask];
	}
	check[num][mask] = true;

	int& ans = D[num][mask];
	if (mask & 1){                  // 첫번째 칸이 채워져 있을 경우 다음 칸으로 이동
		ans += go(num + 1, (mask >> 1));            //(mask >> 1) : 다음상태
	}
	else{        //첫째 칸이 안채워져 있는 경우 
		ans += go(num + 1, (mask >> 1) | (1 << (m - 1)));      // 첫째칸에 세로로된 블럭 놓기.
		if ((num%m) != (m - 1) && (mask & 2) == 0){       //첫째칸과 둘째칸에 가로로된 블럭 놓기. 앞쪽 조건: 지금 놓으려는 블록이 오른쪽 끝의 블록이 아닌경우.
			ans += go(num + 2, (mask >> 2));
		}
	}
	ans %= 9901;
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	printf("%d",go(0,0));
	return 0;
}