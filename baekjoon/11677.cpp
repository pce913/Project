#include<stdio.h>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

bool check[5010];
vector<int> a[5010];
vector<int> rev[5010];
int connect_s_cnt;
int connect_t_cnt;
void find1(int start){
	queue<int> q;
	q.push(start);

	while(!q.empty()){
		int node=q.front();
		q.pop();
		for (int next : rev[node]){
			if (!check[next]){
				check[next] = true;
				connect_s_cnt++;
				q.push(next);
			}
			
		}
	}
}

void find2(int start){
	queue<int> q;
	q.push(start);

	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int next : a[node]){
			if (!check[next]){
				check[next] = true;
				connect_t_cnt++;
				q.push(next);
			}
			
		}
	}
}


int main(){
	int A, B, E, P;
	scanf("%d %d %d %d",&A,&B,&E,&P);
	for (int i = 0; i < P; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		rev[y].push_back(x);
	}

	int ans1 = 0, ans2 = 0, ans3=0;
	
	for (int i = 0; i < E; i++){
		connect_s_cnt = 0;     //어떤 사람이 승진하기 위해 앞서 승진해야 하는 사람 수. (자기자신 포함)
		connect_t_cnt = 0;     //어떤 사람이 승진하고 나서 차례로 승진 할 수 있는 사람 수. (자기자신 포함)

		find1(i);
		memset(check, false, sizeof(check));
		find2(i);
		memset(check, false, sizeof(check));
		int range_s = connect_s_cnt;  //어떤 사람이 승진하기 위해 앞서 승진해야 하는 사람 수. (자기자신 포함)
		int range_t = E - connect_t_cnt;  // 어떤 사람이 승진하는데 무관한 사람들과, 승진하기 위해 앞서 승진해야 하는 사람수의 합. (자기자신 포함)

		if (range_t <= A){
			ans1++;
		}
		if (range_t <= B){
			ans2++;
		}
		if (range_s >= B){
			ans3++;
		}

	}
	
	printf("%d\n%d\n%d",ans1,ans2,ans3);
	return 0;
}