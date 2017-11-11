#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Line{
	int start, end;
	bool operator<(const Line& l)const{
		if (this->end == l.end)
			return this->start < l.start;
		return this->end < l.end;
	}
};

vector<Line> a;
int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a.push_back({ x, y });
	}
	sort(a.begin(), a.end());   //일찍 끝나는 녀석부터 회의실을 배정한다.
	int cur = 0;
	int ans = 0;
	for (int i = 0; i < a.size(); i++){
		if (cur <= a[i].start){
			cur = a[i].end;
			ans += 1;
		}
	}
	printf("%d",ans);
	return 0;
}