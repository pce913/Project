#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> a[100005];
int cut_cnt = 0;

/*
7 2
7 2
2 1
1 4
4 3
4 5
5 6
*/    //이걸로 돌려보면 이해가 빠르다.

int dfs(int node,int parent,int s){
	vector<int> height;
	for (int i = 0; i < a[node].size(); i++){
		int next = a[node][i];
		if (next != parent){
			height.push_back(dfs(next, node, s)+1);  //아하.
		}
	}

	sort(height.begin(), height.end());
	while (height.size() >= 2 && height[height.size() - 2] + height.back() > s){  //내가 지정한 longest path보다 크면
		cut_cnt++;  //자른 횟수    --> 더 잘라야 하므로 자른 횟수++ 해준다.  여기서 잘라지는 부분은 v.back()에 해당하는 sub트리의 간선이다.
		height.pop_back();
	}
	if (height.size()>=1 && height.back() > s){
		cut_cnt++;
		height.pop_back();
	}

	if (height.empty())
		return 0;
	else
		return height.back();
}

int main(){
	int n, s;
	ReadInt(&n), ReadInt(&s);
	for (int i = 0; i < n - 1; i++){
		int x, y;
		ReadInt(&x), ReadInt(&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}

	int left = 0;
	int right = n - 1;
	int ans = 0;
	while (left <= right){
		int mid = (left + right) >> 1;
		cut_cnt = 0;
		dfs(1, -1, mid);
		if (cut_cnt <= s){   //mid라는 longest path를 만들기 위해 자른 횟수가 s보다 작다면
			ans = mid;
			right = mid - 1;  //longest path 단위를 줄여서 더 많이 자르게 해본다.
		}
		else{
			left = mid + 1;
		}
	}
	printf("%d",ans);
	return 0;
}