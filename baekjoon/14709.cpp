#include<stdio.h>

int main(){
	int the1, the2;
	scanf("%d %d", &the1, &the2);
	if (((the1%30) * 12) == the2){
		printf("O");
	}
	else{
		printf("X");
	}
	return 0;
}