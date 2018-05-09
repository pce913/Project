//#include<cstdio>
//#include<algorithm>
//using namespace std;
//int n, x[101] = { -1 }, y[101] = { -1 }, szx = 1, szy = 1, s[101][101], r = 1e9;
//pair<int, int> p[100];
//int main() {
//	scanf("%d", &n);
//	for (int i = 0; i < n; i++) {
//		scanf("%d%d", &p[i].first, &p[i].second);
//		x[szx++] = p[i].first;
//		y[szy++] = p[i].second;
//	}
//	sort(x, x + szx);
//	sort(y, y + szy);
//	szx = unique(x, x + szx) - x;
//	szy = unique(y, y + szy) - y;
//	for (int i = 0; i < n; i++) {
//		int tx = lower_bound(x, x + szx, p[i].first) - x,
//			ty = lower_bound(y, y + szy, p[i].second) - y;
//		s[tx][ty]++;
//	}
//	for (int i = 1; i < szx; i++) {
//		for (int j = 1; j < szy; j++) s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
//	}
//	for (int i = 1; i < szx; i++) {
//		for (int j = 1; j < szy; j++) {
//			int k = 0, l = j;
//			while (l >= 0) {
//				if (s[i][j] - s[k][j] - s[i][l] + s[k][l] < n / 2){
//					l--;
//					printf("a\n");
//				}
//				else {
//					r = min(r, (x[i] - x[k + 1] + 2)*(y[j] - y[l + 1] + 2));
//					k++;
//					printf("b\n");
//				}
//			}
//		}
//	}
//	printf("%d", r);
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

//http://codersbrunch.blogspot.kr/2017/01/1438.html

struct Point{
	int x, y;
};

vector<Point> point;
//vector<int> xpos, ypos;
int xpos[105] = { -1 }, ypos[105] = {-1};
int sum[105][105];
int M[105][105];
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		point.push_back({ x, y });
		xpos[i] = x;
		ypos[i] = y;
	}
	sort(xpos + 1, xpos + 1 + n);
	sort(ypos + 1, ypos + 1 + n);
	int nx = unique(xpos + 1, xpos + 1 + n) - xpos;
	int ny = unique(ypos + 1, ypos + 1 + n) - ypos;
	for (int i = 0; i < point.size(); i++){   //좌표 압축.
		int tx = lower_bound(xpos, xpos + nx, point[i].x) - xpos;
		int ty = lower_bound(ypos, ypos + ny, point[i].y) - ypos;
		sum[tx][ty]++;   //1베이스로 sum을 구성해 놓음.
	}
	for (int i = 1; i < nx; i++){   //내부 합을 미리 구해놓음.
		for (int j = 1; j < ny; j++){
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}

	int ans = 1e9;
	for (int i = 1; i < nx; i++){   //오른쪽 위 점을 고정 시키고,
		for (int j = 1; j < ny; j++){
			int k = 0;
			int l = j;
			while (l >= 0){   //아하. 마치 스위핑 같다.
				if (sum[i][j] - sum[k][j] - sum[i][l] + sum[k][l] < n / 2){
					l--;
				}
				else{
					ans = min(ans, (xpos[i] - xpos[k + 1] + 2)*(ypos[j] - ypos[l + 1] + 2));
					k++;
				}
			}
		}
	}
	printf("%d",ans);

	return 0;
}