//#include<stdio.h>
//#include<iostream>
//#include<algorithm>
//#include<vector>
//using namespace std;
//
//pair<int,int> M[100000];
//bool cmp(const pair<int,int> u,const pair<int,int> v){
//	return u.second < v.second;
//}
//int dist(const pair<int, int>& a,const pair<int, int>& b){
//	return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
//}
//
//int close(int si,int ei){
//	int n=ei - si+1;
//	if (n <= 3){
//		int mini = 1000000000;
//		for (int i = 0; i < n - 1; i++){            
//			for (int j = i+1; j < n; j++){
//				int d = dist(M[si + i], M[si + j]);
//				if (mini>d)
//					mini = d;
//			}
//		}
//		return mini;
//	}
//
//	int m = (si + ei) / 2;
//	int l=close(si,m);
//	int r=close(m + 1, ei);
//	int ans=min(l, r);
//
//	vector< pair<int, int> > v;
//	for (int i = si; i <= ei; i++){
//		int d = M[i].first - M[m].first;
//		if (ans > d*d)
//			v.push_back(M[i]);
//	}
//	sort(v.begin(), v.end(), cmp);
//
//	int vs = v.size();
//	for (int i = 0; i < vs - 1; i++){
//		for (int j = i + 1; j < vs; j++){
//			int y = v[j].second - v[i].second;
//			if (ans>y*y){
//				int d=dist(v[j], v[i]);
//				if (ans>d)
//					ans = d;
//			}
//			else
//				break;
//		}
//	}
//	return ans;
//}
//
//int main(){
//	int n;
//	scanf("%d",&n);
//	for (int i = 0; i < n; i++)
//		scanf("%d %d",&M[i].first,&M[i].second);
//	
//	sort(M,M+n);
//	printf("%d", close(0, n - 1));
//	return 0;
//}
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

struct Point{
	int x, y;
};

Point M[100000];

bool cmp1(const Point& p1, const Point& p2){
	return p1.x < p2.x;
}
bool cmp2(const Point& p1, const Point& p2){
	return p1.y < p2.y;
}

int dist(const Point& p1, const Point& p2){
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}


int shortest(int start,int end){
	int n = end - start + 1;
	if (n <= 3){
		int ans = 1000000000;
		for (int i = 0; i < n-1; i++){
			for (int j = i+1; j < n; j++){
				int d = dist(M[start+i], M[start+j]);
				if (ans>d){
					ans = d;
				}
			}
		}
		return ans;
	}

	int mid = (start + end) / 2;
	int left = shortest(start,mid);
	int right = shortest(mid + 1, end);
	int ans = min(left, right);

	vector<Point> v;	
	for (int i = start; i <= end; i++){
		int d = M[i].x - M[mid].x;
		if (ans > d*d){
			v.push_back(M[i]);
		}
	}

	sort(v.begin(), v.end() ,cmp2);
	int vs = v.size();
	for (int i = 0; i < vs - 1; i++){
		for (int j = i + 1; j < vs; j++){
			int y = v[j].y - v[i].y;
			if (ans>y*y){
				int d = dist(v[i], v[j]);
				if (ans > d){
					ans = d;
				}
			}
			else{
				break;
			}
		}
	}
	return ans;
}

int main(){
	int n; 
	freopen("input.txt", "r", stdin);
	scanf("%d",&n);
	for (int i = 0; i < n; i++){
		scanf("%d %d",&M[i].x,&M[i].y);
	}
	sort(M, M + n,cmp1);
	printf("%d",shortest(0,n-1));
	return 0;
}