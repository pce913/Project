#include<iostream>
#include<algorithm>
using namespace std;

int n;
int ans;
int va[25];
int temp[25][25];
void goDown(int M[][25]){
	for (int i = 1; i <= n; i++){
		bool isEven = false;
		int vn = 0;
		for (int j = n ; j >= 1; j--){
			if (M[j][i] != 0){
				if (isEven && va[vn-1] == M[j][i]){
					va[vn-1] *= 2;
					isEven = false;
				}
				else{
					va[vn++] = M[j][i];
					isEven = true;
				}
			}
		}
		int k = 0;
		for (int j = n; j >= 1; j--){
			if (k < vn)
				M[j][i] = va[k++];
			else
				M[j][i] = 0;
		}
	}
}

void Rotate(int T[][25]){
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			temp[j][n - i + 1] = T[i][j];
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			T[i][j] = temp[i][j];
		}
	}
}


void copy(int Tar[][25],int Src[][25]){
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			Tar[i][j] = Src[i][j];
		}
	}
}

void dfs(int depth,int M[][25]){
	if (depth >= 5){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				ans = max(ans, M[i][j]);
			}
		}
		return;
	}
	int T[25][25];
	copy(T, M);
	goDown(M);
	dfs(depth + 1, M);

	Rotate(T);
	copy(M, T);
	goDown(M);
	dfs(depth + 1, M);

	Rotate(T);
	copy(M, T);
	goDown(M);
	dfs(depth + 1, M);

	Rotate(T);
	copy(M, T);
	goDown(M);
	dfs(depth + 1, M);
}

int main(){
	freopen("input.txt","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	int M[25][25];
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			cin >> M[i][j];
		}
	}
	dfs(0, M);
	cout << ans;
	return 0;
}