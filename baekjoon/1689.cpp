#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Info{
	int p;
	bool isOpen;
	int over;
	bool operator<(const Info& e)const{
		if (this->p == e.p){
			return this->isOpen<e.isOpen;
		}
		return this->p < e.p;
	}

};
vector<Info> line;

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		line.push_back({ x, true ,0});
		line.push_back({ y, false,0 });
	}
	sort(line.begin(), line.end());

	int sum = 0;
	for (int i = 0; i < line.size(); i++){
		if (line[i].isOpen){
			sum += 1;
			line[i].over = sum;
		}
		else{
			line[i].over = sum;
			sum -= 1;
		}
	}

	int ans = 0;
	for (int i = 0; i < line.size(); i++){
		ans = max(ans, line[i].over);
	}
	printf("%d",ans);
	return 0;
}