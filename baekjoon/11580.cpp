#include<iostream>
#include<set>
#include<string>
using namespace std;

char order[] = { 'E', 'W', 'S', 'N' };
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

struct Point{
	int x, y;
	bool operator<(const Point& p)const{
		if (this->x == p.x){
			return this->y < p.y;
		}
		return this->x < p.x;
	}
};
set<Point> st;

int main(){
	int L;
	string s;
	cin >> L;
	cin >> s;
	int cx = 0;
	int cy = 0;
	st.insert({ cx, cy });
	for (int i = 0; i < s.size(); i++){
		for (int j = 0; j < 4; j++){
			if (s[i] == order[j]){
				cx += dx[j];
				cy += dy[j];
				st.insert({cx,cy});
				break;
			}
		}
	}
	cout << st.size();

	return 0;
}