#include<stdio.h>
#include<queue>
#include<vector>
#include<functional>
using namespace std;

priority_queue<int, vector<int>, greater<int>> q;

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		q.push(x);
	}
	for (int i = 1; i < n; i++){
		for (int j = 0; j < n; j++){
			int x;
			scanf("%d", &x);
			int num = q.top();
			if (num < x){
				q.pop();
				q.push(x);
			}
		}
	}
	printf("%d", q.top());
	return 0;
}