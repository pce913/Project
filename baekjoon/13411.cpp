#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*
	속도^2 을 곱해서 비교하는 이유.
	우리가 원래 비교 할 것은 시간이다. 즉, 거리/속력.
	일반적으로 두 값의 대소비교를 한다고 하면 거리1/속력1 , 거리2/속력2 를 비교한다.
	그런데 밑에서 distance 함수에서 sqrt를 안붙였으므로 우리의 목적은 거리1/속력1 , 거리2/속력2 이 아니라
	(거리1)^2/(속력1)^2 , (거리2)^2/(속력2)^2 을 비교하는 것이다.
	두 값의 대소비교를 할땐 양변에 같은 값을 곱해줘도 대소비교에 지장이 없으므로
	각각 분모 값인 (속력1)^2 과 (속력2)^2를 곱해준 것이다.
	
*/
struct Info{
	long long robot, dist, velo;
	bool operator<(const Info& e)const{
		long long a = dist*(e.velo*e.velo);   
		long long b = e.dist*(velo*velo);
		if (a != b){
			return a < b;
		}
		return robot < e.robot;
	}
};

vector<Info> info;

long long distance(long long x1, long long y1, long long x2, long long y2){
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	long long n;
	cin >> n;
	for (long long i = 1; i <= n; i++){
		long long x, y, z;
		cin >> x >> y >> z;
		info.push_back({ i, distance(0, 0, x, y), z });
	}
	sort(info.begin(), info.end());
	for (long long i = 0; i < info.size(); i++){
		cout << info[i].robot << "\n";
	}
}