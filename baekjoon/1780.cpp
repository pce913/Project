#include<stdio.h>
#include<vector>
using namespace std;

int ans1, ans2, ans3;

void go(vector< vector<int> >& a,int row, int col, int length){
	bool isSame = true;
	int num=a[row][col];
	for (int i = row; i < row + length; i++){
		for (int j = col; j < col + length; j++){
			if (a[i][j] == num)
				continue;
			else{
				isSame = false;
				break;
			}
		}
		if (!isSame)
			break;
	}

	if (isSame){
		if (num == -1){
			ans1++;
		}
		else if (num == 0){
			ans2++;
		}
		else{
			ans3++;
		}
		return;
	}

	int nlength = length / 3;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			go(a,row+nlength*i, col+nlength*j, nlength);
		}
	}
	return;
}

int main(){
	int n;
	scanf("%d",&n);
	vector< vector<int> > a(n, vector<int>(n));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			scanf("%d",&a[i][j]);
		}
	}
	go(a, 0, 0, n);
	printf("%d\n",ans1);
	printf("%d\n",ans2);
	printf("%d",ans3);
	return 0;
}