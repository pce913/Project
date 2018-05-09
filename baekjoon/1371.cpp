#include<iostream>
using namespace std;

int counts[256];
char ans[30];
int an = 0;
int main(){
	char c;
	while (cin >> c){
		counts[c]++;
	}

	int max = 0;
	for (int i = 'a'; i <= 'z'; i++){
		if (max < counts[i]){
			max = counts[i];
		}
	}
	for (int i = 'a'; i <= 'z'; i++){
		if (max == counts[i]){
			ans[an++] = i;
		}
	}
	ans[an++] = '\0';
	cout<<ans;
	return 0;
}