#include<stdio.h>
#include<cstring>

char s[30];
char t[105];
int main(){
	int n;
	scanf("%d %s",&n,s);
	int ans = 0;
	int sl = strlen(s);
	for (int q = 0; q < n; q++){
		scanf("%s",t);
		int tl = strlen(t);
		for (int len = 1; len < tl; len++){  //문자와 문자 사이의 길이
			bool isCan = true;
			for (int i = 0; i + len*(sl - 1) < tl; i++){ //시작위치
				isCan = true;
				for (int j = 0; j < sl; j++){
					if (s[j] != t[i + j*len]){
						isCan = false;
						break;
					}
				}
				if (isCan){
					ans++;
					break;
				}
			}
			if (isCan)
				break;
		}
	}
	printf("%d",ans);
	return 0;
}