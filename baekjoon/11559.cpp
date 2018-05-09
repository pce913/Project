#include<stdio.h>
template <typename T>
struct queue{
	T* arr;
	int n;    //  들어있는 갯수
	int ffront, rear;    //왼쪽이 ffront, 오른쪽이 rear
	queue(){
		arr = new T[10000005];
		n = 0;
		rear = 0, ffront = 0;
	}
	~queue(){
		delete[] arr;
	}
	void push(T t){
		arr[rear++] = t;
		n++;
	}
	T front(){
		return arr[ffront];
	}
	T back(){
		return arr[rear - 1];
	}
	void pop(){
		ffront++;
		n--;
	}
	bool empty(){
		return n == 0;
	}
};

struct Point{
	int x, y;
	Point(){}
	Point(int _x, int _y) :x(_x), y(_y){}
};

char M[15][15];
bool check[15][15];
//bool isBoom[15][15];
int n = 12, m = 6;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
Point candi[105];
int cidx = 0;

queue<Point> q;    //큐를 bfs안쪽에 넣으면 왠지 메모리초과 날것 같다.
template <typename T>
void swap(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}

bool bfs(int sx, int sy, char w){
	cidx = 0;
	check[sx][sy] = true;
	q.push(Point(sx, sy));
	candi[cidx++] = Point(sx, sy);
	while (!q.empty()){
		Point p = q.front();
		q.pop();
		int cx = p.x;
		int cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m){
				if (M[nx][ny] == w){
					if (!check[nx][ny]){
						check[nx][ny] = true;
						q.push(Point(nx, ny));
						candi[cidx++] = Point(nx, ny);
					}
				}
			}
		}
	}

	if (cidx >= 4){
		for (int i = 0; i < cidx; i++){
			int x = candi[i].x;
			int y = candi[i].y;
			M[x][y] = '.';
		}
		return true;
	}
	return false;
}

void go_down(int cx, int cy){
	int nx = cx;
	int ny = cy;
	while (nx + 1 >= 1 && nx + 1 <= n && M[nx + 1][ny] == '.'){
		nx += 1;
	}
	swap(M[nx][ny], M[cx][cy]);
}

void init(){
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			check[i][j] = false;
		}
	}
}

int main(){
	for (int i = 1; i <= n; i++){
		scanf("%s", &M[i][1]);
	}
	int ans = 0;
	while (true){
		init();
		bool isNot = true;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if (M[i][j] != '.'){
					if (!check[i][j]){
						if (bfs(i, j, M[i][j])){
							isNot = false;
						}
					}
				}
			}
		}

		if (isNot){
			break;
		}
		else{
			ans++;
		}

		//터진 콤보들 재배치하는 코드 넣기.
		for (int i = n; i >= 1; i--){
			for (int j = m; j >= 1; j--){
				if (M[i][j] != '.'){
					go_down(i, j);
				}
			}
		}
	}
	printf("%d", ans);
	return 0;
}