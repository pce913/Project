//#include<stdio.h>
//#include<cstring>
//
//int C, D, dd;
//int d[201][101][101][2][2];   //d[N][x][y][sx][sy] : N일에 X팀이 x번째 연습까지 했고, Y팀이 y번째 연습까지 했을때 최소비용,
//                   //sx,sy가 0인 경우, 해당팀의 첫 휴식, 1인경우 해당 팀이 연속으로 휴식    
////bool check[211][111][111][2][2];   //여기서는 check배열 안쓰는게 낫다.
//int a[101];           //a팀이 방문해야 하는 도시 순서
//int b[101];
//
//int an, bn;
//
//int go(int day,int x,int y,int prevx,int prevy){
//	if (x == an && y == bn){
//		return 0;
//	}
//	if (day >= 200){
//		return 1e9;
//	}
//	//예외처리
//
//	if (d[day][x][y][prevx][prevy]!=-1){
//		return d[day][x][y][prevx][prevy];
//	}
//	int& ans = d[day][x][y][prevx][prevy];
//
//	if (x < an && y < bn){     //두 팀이 모두 연습을 하는 경우
//		int temp = C;         
//		if (a[x] != b[y])   //두 팀이 다른 경기장을 이용할 경우
//			temp += C;
//		if (ans == -1 || ans > temp + go(day + 1, x + 1, y + 1, 0, 0))
//			ans = temp + go(day + 1, x + 1, y + 1, 0, 0);
//	}
//	if (x < an){           //X팀만 연습하는 경우. Y팀은 휴식
//		int temp = C;
//		temp += dd;
//		if (prevy == 0)
//			temp += D;
//		if (ans == -1 || ans > temp + go(day + 1, x + 1, y, 0, 1))
//			ans = temp + go(day + 1, x + 1, y, 0, 1);
//	}
//	if (y < bn){      //Y팀만 연습하는 경우. X팀은 휴식
//		int temp = C;
//		temp += dd;
//		if (prevx == 0){
//			temp += D;
//		}
//		if (ans == -1 || ans > temp + go(day + 1, x, y + 1, 1, 0)){
//			ans = temp + go(day + 1, x, y + 1, 1, 0);
//		}
//	}
//
//	int temp = 0;               // 두 팀 모두 쉬는 경우
//	temp += 2 * dd;
//	if (prevx == 0){
//		temp += D;
//	}
//	if (prevy == 0){
//		temp += D;
//	}
//	if (ans == -1 || ans > temp + go(day + 1, x, y, 1, 1)){
//		ans = temp + go(day + 1, x, y, 1, 1);
//	}
//
//	return ans;
//}
//
//int main(){
//	int T;
//	scanf("%d",&T);
//	for (int test = 0; test < T; test++){
//		scanf("%d %d %d",&C,&D,&dd);
//		an = 0;
//		bn=0;
//		while (true){
//			int temp;
//			scanf("%d",&temp);
//			if (temp == 0)
//				break;
//			a[an] = temp;
//			an++;
//		}
//		while (true){
//			int temp;
//			scanf("%d",&temp);
//			if (temp == 0)
//				break;
//			b[bn] = temp;
//			bn++;
//		}
//		memset(d, -1, sizeof(d));
//		printf("%d\n",go(0,0,0,0,0));
//	}
//	return 0;
//}
#include<stdio.h>
#include<cstring>

int C, D, dd;
int d[101][101][2][2];   //d[x][y][sx][sy] :  X팀이 x번째 연습까지 했고, Y팀이 y번째 연습까지 했을때 최소비용,
//sx,sy가 0인 경우, 해당팀의 첫 휴식, 1인경우 해당 팀이 연속으로 휴식    
//bool check[211][111][111][2][2];   //여기서는 check배열 안쓰는게 낫다.
int a[101];           //a팀이 방문해야 하는 도시 순서
int b[101];

int an, bn;

int go(int x, int y, int prevx, int prevy){
	if (x == an && y == bn){
		return 0;
	}
	
	//예외처리

	if (d[x][y][prevx][prevy] != -1){
		return d[x][y][prevx][prevy];
	}
	int& ans = d[x][y][prevx][prevy];

	if (x < an && y < bn){     //두 팀이 모두 연습을 하는 경우
		int temp = C;
		if (a[x] != b[y])   //두 팀이 다른 경기장을 이용할 경우
			temp += C;
		if (ans == -1 || ans > temp + go( x + 1, y + 1, 0, 0))
			ans = temp + go( x + 1, y + 1, 0, 0);
	}
	if (x < an){           //X팀만 연습하는 경우. Y팀은 휴식
		int temp = C;
		temp += dd;
		if (prevy == 0)
			temp += D;
		if (ans == -1 || ans > temp + go(x + 1, y, 0, 1))
			ans = temp + go(x + 1, y, 0, 1);
	}
	if (y < bn){      //Y팀만 연습하는 경우. X팀은 휴식
		int temp = C;
		temp += dd;
		if (prevx == 0){
			temp += D;
		}
		if (ans == -1 || ans > temp + go( x, y + 1, 1, 0)){
			ans = temp + go(x, y + 1, 1, 0);
		}
	}

	int temp = 0;               // 두 팀 모두 쉬는 경우
	temp += 2 * dd;
	if (prevx == 0){
		temp += D;
	}
	if (prevy == 0){
		temp += D;
	}
	if (ans == -1 || ans > temp + go(x, y, 1, 1)){
		ans = temp + go( x, y, 1, 1);
	}

	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	for (int test = 0; test < T; test++){
		scanf("%d %d %d", &C, &D, &dd);
		an = 0;
		bn = 0;
		while (true){
			int temp;
			scanf("%d", &temp);
			if (temp == 0)
				break;
			a[an] = temp;
			an++;
		}
		while (true){
			int temp;
			scanf("%d", &temp);
			if (temp == 0)
				break;
			b[bn] = temp;
			bn++;
		}
		memset(d, -1, sizeof(d));
		printf("%d\n", go(0, 0, 0, 0));
	}
	return 0;
}
//#include<stdio.h>
//#include<algorithm>
//using namespace std;
//
//int C, D, dd;
//int d[101][101][4];             //0: 둘다 뛰는경우, 1: X만 뛰는 경우, 2:Y만 뛰는 경우 ,3: 둘다 쉬는 경우
//
//bool check[101][101][4];   
//int a[101];           //a팀이 방문해야 하는 도시 순서
//int b[101];
//
//int an, bn;
//
//int go(int x, int y, int what,int prevx,int prevy){
//	if (x == an && y == bn){
//		return 0;
//	}
//	if (x > an || y > bn){
//		return 1e9;
//	}
//
//	//예외처리
//
//	if (check[x][y][what]){
//		return d[x][y][what];
//	}
//	check[x][y][what] = true;
//	int& ans = d[x][y][what];
//
//
//	int nx, ny,temp;
//	if (what == 0){
//		temp = C;
//		if (a[x] != b[y])   //두 팀이 다른 경기장을 이용할 경우
//			temp += C;
//
//		nx = 0;
//		ny = 0;
//	}
//	else if (what == 1){
//		temp = C;
//		temp += dd;
//		if (prevy == 0)
//			temp += D;
//		
//		nx = 0;
//		ny = 1;
//	}
//	else if (what == 2){
//		temp = C;
//		temp += dd;
//		if (prevx == 0){
//			temp += D;
//		}
//		nx = 1;
//		ny = 0;
//	}
//	else if (what == 3){
//		temp = 0;               // 두 팀 모두 쉬는 경우
//		temp += 2 * dd;
//		if (prevx == 0){
//			temp += D;
//		}
//		if (prevy == 0){
//			temp += D;
//		}
//		nx = 1;
//		ny = 1;
//	}
//
//	for (int i = 0; i<4; i++){
//		/*int dx = -(~nx);
//		int dy = -(~ny);*/
//		
//		int dx = nx == 1 ? 0 : 1;
//		int dy = ny == 1 ? 0 : 1;
//		if (ans > temp + go(x+dx, y + dy, i, nx, ny))
//			ans = temp + go(x + dx, y + dy, i, nx, ny);
//	}
//
//	return ans;
//}
//
//int main(){
//	int T;
//	scanf("%d", &T);
//	for (int test = 0; test < T; test++){
//		scanf("%d %d %d", &C, &D, &dd);
//		an = 0;
//		bn = 0;
//		while (true){
//			int temp;
//			scanf("%d", &temp);
//			if (temp == 0)
//				break;
//			a[an] = temp;
//			an++;
//		}
//		while (true){
//			int temp;
//			scanf("%d", &temp);
//			if (temp == 0)
//				break;
//			b[bn] = temp;
//			bn++;
//		}
//		//memset(d, -1, sizeof(d));
//
//		for (int i = 0; i < an; i++){
//			for (int j = 0; j < bn; j++){
//				for (int k = 0; k < 4; k++){
//					d[i][j][k] = 1e9;
//				}
//			}
//			
//		}
//
//		int ans1 = go(0, 0, 0, 0, 0);
//		int ans2 = go(0, 0, 1, 0, 0);
//		int ans3 = go(0, 0, 2, 0, 0);
//		int ans4 = go(0, 0, 3, 0, 0);  //이 경우는 어차피 답 아님
//		printf("%d\n", min({ans1,ans2,ans3,ans4}));
//	}
//	return 0;
//}