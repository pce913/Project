#include<stdio.h>

//int ccw(int x1,int y1,int x2,int y2,int x3,int y3){
//	int s=(x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
//	int ret;
//	if (s > 0){
//		ret = 1;
//	}
//	else if (s < 0){
//		ret = -1;
//	}
//	else{
//		ret = 0;
//	}
//	return ret;
//}
int ccw(int x1, int y1, int x2, int y2, int x3, int y3){
	int s = (x1*y2+x2*y3+x3*y1)-(x1*y3+x2*y1+x3*y2);
	int ret;
	if (s > 0){
		ret = 1;
	}
	else if (s < 0){
		ret = -1;
	}
	else{
		ret = 0;
	}
	return ret;
}


int main(){
	int x1,y1,x2,y2,x3,y3;
	scanf("%d %d %d %d %d %d",&x1,&y1,&x2,&y2,&x3,&y3);
	printf("%d", ccw(x1, y1, x2, y2, x3, y3));
	return 0;
}