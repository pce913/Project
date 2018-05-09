#define test1
#ifdef test1
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
//플러드필처럼 표시해두고 바이너리서치 하자.
struct Point{
	int x, y;
};

struct Point_B{
	int x, y, d;  //d: 한번의 이동으로 얼마만큼 이동했는가.
};

int dx[] = { 1, 0, - 1, 0 };
int dy[] = { 0, -1, 0, 1 };
bool check[2005][2005];
char M[2005][2005];
int E[2005][2005];   //꿀벌이 해당 지역을 장악하는데 걸리는 시간.
int n, m;
queue<Point> q;

int sx, sy, ex, ey;
void bfs_bee(){
	while (!q.empty()){
		auto p = q.front();
		q.pop();
		int cx = p.x, cy = p.y;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				if (check[nx][ny])continue;
				if (M[nx][ny] != 'G')continue;
				check[nx][ny] = true;
				E[nx][ny] = E[cx][cy] + m;
				q.push({ nx, ny });
			}
		}
	}
}
//
bool bfs_bear(int t){   //꿀벌이 이미 장악한 지역은 가지 않는다. //한번에 m칸씩 가는거 처리.
	if (t*m >= E[sx][sy])   //이거 없으면 바로 틀린다
		return false;
	memset(check, false, sizeof(check));
	check[sx][sy] = true;
	queue<Point_B> qb;
	qb.push({ sx, sy, t*m });  //처음엔 m을 넣고 시작  그 다음부터는 1 2 3 , 1 2 3 , 1 2 3 이런식으로 들어가게 해야함.
	while (!qb.empty()){
		auto p = qb.front();
		qb.pop();
		int cx = p.x, cy = p.y;
		int cd = p.d;
		if (cx == ex && cy == ey)
			return true;
		for (int i = 0; i < 4; i++){
			int nx = cx + dx[i], ny = cy + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
				if (check[nx][ny])continue;
				if (M[nx][ny] == 'T')continue;
				if (cd + 1 >= E[nx][ny])continue;    //>=  , >
				check[nx][ny] = true;
				qb.push({ nx, ny, cd + 1 });
			}
		}
	}
	return false;
}
int go(){
	int left = 0;
	int right = 2*n*n;   //n*n분 이상 꿀을 먹을 수 없다.
	int ans = -1;   //얼만큼 꿀을 먹을 수 있니?
	while (left <= right){
		int mid = (left + right) >> 1;   //mid 시간부터 시작해서 출발하면 D에 도달 할 수 있니?
		if (bfs_bear(mid)){   // 곰이 자기 집에 도착 할 수 있다면
			ans = mid;
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}
	return ans;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> &M[i][1];
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (M[i][j] == 'M'){
				M[i][j] = 'G';
				sx = i, sy = j;
			}
			else if (M[i][j] == 'D'){
				ex = i, ey = j;
			}
			else if (M[i][j] == 'H'){
				q.push({ i, j });
				//check[i][j] = true;
			}
		}
	}
	bfs_bee();
	E[ex][ey] = n*n*m;
	cout << go();
	return 0;
}
#endif
/**
* A binary search solution for IOI 2009 problem "mecho"
*
* This solution should score 100%
*
* Carl Hultquist, chultquist@gmail.com
*/


#ifdef test2
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>
#include<cstring>

using namespace std;

#define MAX_N 2000

int cx[4] = { 1, -1, 0, 0 };
int cy[4] = { 0, 0, 1, -1 };

char mainMap[MAX_N][MAX_N];
bool reachable[MAX_N][MAX_N];

// The time that it takes the bees to reach any cell in the map
int beeDistance[MAX_N][MAX_N];

int n, s;
int dx, dy;
int mx, my;

/**
* Tests if Mecho is able to reach his home after staying with
* the honey for the given delay time.
*/
bool test(int delay)
{
	// Check if the bees catch Mecho whilst he is still with
	// the honey.
	if (delay * s >= beeDistance[mx][my])
		return false;

	// Initialise data structures -- at the beginning of the search,
	// Mecho has only reached the cell with the honey. Note that it
	// is possible for the bees to catch Mecho at the honey -- but
	// we checked for this case above, and so if we reach this point
	// we know that Mecho is safe with the honey after the given
	// delay.
	memset(reachable, 0, sizeof(reachable));
	//deque<pair<int, pair<int, int> > > q;
	queue<pair<int, pair<int, int> > > q;
	q.push(make_pair(delay * s, make_pair(mx, my)));
	reachable[mx][my] = true;

	// Now do the main loop to see what other cells Mecho can reach.
	while (!q.empty())
	{
		int distance = q.front().first;
		int x = q.front().second.first;
		int y = q.front().second.second;

		q.pop();

		// If Mecho has reached his home, then we are done.
		if (mainMap[x][y] == 'D')
			return true;

		// Check neighbouring cells
		for (int c = 0; c < 4; c++)
		{
			int nx = x + cx[c];
			int ny = y + cy[c];

			// Check that the cell is valid, that it is not a tree, and
			// that Mecho can get here before the bees.
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || mainMap[nx][ny] == 'T' || (distance + 1) >= beeDistance[nx][ny] || reachable[nx][ny])
				continue;

			// All OK, so add it to the queue
			q.push(make_pair(distance + 1, make_pair(nx, ny)));
			reachable[nx][ny] = true;
		}
	}

	// If we reach here, then Mecho was unable to reach his home.
	return false;
}
int main(int argc, char **argv)
{
		//freopen("input.txt","r",stdin);
		//freopen("output.txt","w",stdout);
	// Read in the data
	cin >> n >> s;

	deque<pair<int, int> > bq;
	memset(beeDistance, -1, sizeof(beeDistance));

	for (int i = 0; i < n; i++)
	{
		cin >> ws;
		for (int j = 0; j < n; j++)
		{
			cin >> mainMap[i][j];
			if (mainMap[i][j] == 'H')
			{
				bq.push_back(make_pair(i, j));
				beeDistance[i][j] = 0;
			}
			else if (mainMap[i][j] == 'M')
			{
				mx = i;
				my = j;

				// Bees can travel through the location of the honey
				mainMap[i][j] = 'G';
			}
			else if (mainMap[i][j] == 'D')
			{
				dx = i;
				dy = j;
			}
		}
	}

	// Precompute the time that it takes the bees to reach any other
	// cell in the map.
	while (!bq.empty())
	{
		int x = bq.front().first;
		int y = bq.front().second;

		bq.pop_front();

		for (int c = 0; c < 4; c++)
		{
			int nx = x + cx[c];
			int ny = y + cy[c];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n || mainMap[nx][ny] != 'G' || beeDistance[nx][ny] != -1)
				continue;

			beeDistance[nx][ny] = beeDistance[x][y] + s;
			bq.push_back(make_pair(nx, ny));
		}
	}

	// The bees can never enter Mecho's home, so set this to a large
	// sentinel value.
	beeDistance[dx][dy] = n * n * s;

	// Binary search to find the maximum delay time.
	int low = -1, high = 2 * n * n;
	while (high - low > 1)
	{
		int mid = (low + high) >> 1;
		if (test(mid))
			low = mid;
		else
			high = mid;
	}

	cout << low << endl;
	return 0;
}
#endif