#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> a;

int D[2001][2001];
bool check[2001][2001];

int go(int x, int y){
	if (check[x][y])
		return D[x][y];
	check[x][y] = true;

	int& ans = D[x][y];
	int term = a[y] - a[x];
	int z = a[y] + term;
	auto lower = lower_bound(a.begin() + y + 1, a.end(), z);    //z의 lower_bound를 찾는다.
	//O(logn)
	int index = -1;
	if (lower != a.end() && *lower == z){    //같은 수가 여러개 있는 경우. 또는 다음수가 존재하는 경우
		index = lower - a.begin();    //인덱스 차이.
	}

	if (index == -1){   //다음 수가 없는경우 해당 DP는 2이다. 아하!
		ans = 2;
	}
	else{
		ans = go(y, index) + 1;  //같은 수가 여러개 있는 경우. 또는 다음수가 존재하는 경우 계속 계산해준다.
	}
	return ans;

}


int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		a.push_back(x);
	}
	sort(a.begin(), a.end());

	int ans = 1;    //초기화 1로 해줘야 함.
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			ans = max(ans, go(i, j));
		}
	}
	printf("%d", ans);
	return 0;
}