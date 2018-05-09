#include<iostream>
#include<algorithm>
using namespace std;

int n;
int ans;
int va[25];
int pw2[15];
const int MD = 10;
int is_change(int Tar[][25], int Src[][25], int dir){   //블록이 움직이지 않았다면, 움직이지 않은 방향 그대로 리턴. 움직였다면 -1 리턴.
	bool isChange = false;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (Tar[i][j] != Src[i][j]){
				isChange = true;
				break;
			}
		}
	}
	return isChange ? -1 : dir;
}

void pushing(int& vn, bool& isEven, int x){
	if (isEven && va[vn - 1] == x){
		va[vn - 1] *= 2;
		isEven = false;
	}
	else{
		va[vn++] = x;
		isEven = true;
	}
}

void filling(int vn, int i, int j, int k, int M[][25]){
	if (k < vn)
		M[i][j] = va[k];
	else
		M[i][j] = 0;
}

int goDown(int M[][25]){
	int maxi = 0;
	for (int i = 1; i <= n; i++){
		bool isEven = 0;
		int vn = 0;
		for (int j = n; j >= 1; j--){
			if (M[j][i] != 0){
				pushing(vn, isEven, M[j][i]);
			}
		}
		int k = 0;
		for (int j = n; j >= 1; j--){
			filling(vn, j, i, k++, M);
			maxi = max(maxi, M[j][i]);
		}
	}
	return maxi;
}

int goLeft(int M[][25]){
	int maxi = 0;
	for (int i = 1; i <= n; i++){
		bool isEven = 0;
		int vn = 0;
		for (int j = 1; j <= n; j++){
			if (M[i][j] != 0){
				pushing(vn, isEven, M[i][j]);
			}
		}
		int k = 0;
		for (int j = 1; j <= n; j++){
			filling(vn, i, j, k++, M);
			maxi = max(maxi, M[i][j]);
		}
	}
	return maxi;
}

int goUp(int M[][25]){
	int maxi = 0;
	for (int i = 1; i <= n; i++){
		bool isEven = 0;
		int vn = 0;
		for (int j = 1; j <= n; j++){
			if (M[j][i] != 0){
				pushing(vn, isEven, M[j][i]);
			}
		}
		int k = 0;
		for (int j = 1; j <= n; j++){
			filling(vn, j, i, k++, M);
			maxi = max(maxi, M[j][i]);
		}
	}
	return maxi;
}

int goRight(int M[][25]){
	int maxi = 0;
	for (int i = 1; i <= n; i++){
		bool isEven = 0;
		int vn = 0;
		for (int j = n; j >= 1; j--){
			if (M[i][j] != 0){
				pushing(vn, isEven, M[i][j]);
			}
		}
		int k = 0;
		for (int j = n; j >= 1; j--){
			filling(vn, i, j, k++, M);
			maxi = max(maxi, M[i][j]);
		}
	}
	return maxi;
}

void copy(int Tar[][25], int Src[][25]){
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			Tar[i][j] = Src[i][j];
		}
	}
}

void dfs(int depth, int M[][25], int not_move, int cmax){
	if (depth >= MD){
		ans = max(ans, cmax);
		return;
	}
	int T[25][25];
	copy(T, M);
	if (not_move != 0){
		int maxi = goDown(M);
		if (maxi > ans / (1 << (MD - depth - 1))){
			dfs(depth + 1, M, is_change(T, M, 0), maxi);
		}
	}

	copy(M, T);
	if (not_move != 1){
		int maxi = goLeft(M);
		if (maxi > ans / (1 << (MD - depth - 1))){
			dfs(depth + 1, M, is_change(T, M, 1), maxi);
		}
	}

	copy(M, T);
	if (not_move != 2){
		int maxi = goUp(M);
		if (maxi > ans / (1 << (MD - depth - 1))){
			dfs(depth + 1, M, is_change(T, M, 2), maxi);
		}
	}

	copy(M, T);
	if (not_move != 3){
		int maxi = goRight(M);
		if (maxi > ans / (1 << (MD - depth - 1))){
			dfs(depth + 1, M, is_change(T, M, 3), maxi);
		}
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	int M[25][25];
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			cin >> M[i][j];
		}
	}
	dfs(0, M, -1, 0);
	cout << ans;
	return 0;
}