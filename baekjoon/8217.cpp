#include<stdio.h>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

struct Info{
	long long from, to, a;
};

struct Goal{
	long long goal, left, right;
};

long long n, m, k;
long long tree[300005], ans[300005];
Info forcast[300005];
Goal goal[300005];
vector<long long> query[300005];
vector<long long> admin[300005];

void init_query(){
	for (long long i = 1; i <= k; i++){
		query[i].clear();
	}
}
void init_tree(){
	for (long long i = 1; i <= m; i++){
		tree[i] = 0;
	}
}

void update(long long x, long long value){
	for (long long i = x; i <= m; i += i&-i){
		tree[i] += value;
	}
}

long long tree_query(long long x){
	long long ans = 0;
	for (long long i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}


int main(){
	scanf("%lld %lld", &n, &m);
	for (long long i = 1; i <= m; i++){
		long long x;
		scanf("%lld", &x);
		admin[x].push_back(i);
	}
	for (long long i = 1; i <= n; i++){
		scanf("%lld", &goal[i].goal);
	}

	scanf("%lld", &k);

	for (long long i = 1; i <= n; i++){
		goal[i].left = 1, goal[i].right = k;
	}
	for (long long i = 1; i <= k; i++){
		scanf("%lld %lld %lld", &forcast[i].from, &forcast[i].to, &forcast[i].a);
	}

	while (true){
		bool isFindAll = true;
		init_query();
		memset(tree, 0, sizeof(tree));
		for (long long i = 1; i <= n; i++){   //각 국가가 들어가야 한다.
			auto p = goal[i];
			long long left = p.left;
			long long right = p.right;
			if (left <= right){
				long long mid = (left + right) >> 1;
				query[mid].push_back(i);
				isFindAll = false;
			}
		}
		if (isFindAll)
			break;

		//트리 업데이트 후, 쿼리 포문
		for (long long i = 1; i <= k; i++){
			long long from = forcast[i].from;
			long long to = forcast[i].to;
			long long a = forcast[i].a;
			if (from <= to){
				update(from, a);   //이렇게 하면 range update 효과가 나타난다. 아하.
				if (to + 1 <= m)
					update(to + 1, -a);
			}
			else{
				update(from, a);
				update(1, a);
				if (to + 1 <= m)
					update(to + 1, -a);
			}

			for (long long j = 0; j<query[i].size();j++){
				long long who = query[i][j];
				long long sum = 0;
				auto& p = goal[who];
				for (long long w = 0; w < admin[who].size(); w++){
					long long idx = admin[who][w];
					sum += tree_query(idx);
					if (sum >= p.goal)    //이 코드가 반드시 있어야 한다.
						break;
				}
				if (sum >= p.goal){
					ans[who] = i;
					p.right = i - 1;
				}
				else{
					p.left = i + 1;
				}
			}

		}
	}
	for (long long i = 1; i <= n; i++){
		if (ans[i] == 0)
			printf("NIE\n");
		else
			printf("%lld\n", ans[i]);
	}

	return 0;
}
//#include<stdio.h>
//#include<vector>
//#include<cstring>
//#include<algorithm>
//using namespace std;
//
//struct Info{
//	long long from, to, a;
//};
//
//struct Goal{
//	long long goal, left, right;
//};
//
//long long n, m, k;
//long long tree[300005] ,ans[300005];
//Info forcast[300005];
//Goal goal[300005];
//vector<long long> query[300005];
//vector<long long> admin[300005];
//
//void init_query(){
//	for (long long i = 1; i <= k; i++){
//		query[i].clear();
//	}
//}
//void init_tree(){
//	for (long long i = 1; i <= m; i++){
//		tree[i] = 0;
//	}
//}
//
//
//void update(long long x,long long value){
//	for (long long i = x; i <= m; i += i&-i){
//		tree[i] += value;
//	}
//}
//
//long long tree_query(long long x){
//	long long ans = 0;
//	for (long long i = x; i > 0; i -= i&-i){
//		ans += tree[i];
//	}
//	return ans;
//}
//
//
//int main(){
//	scanf("%lld %lld",&n,&m);
//	for (long long i = 1; i <= m; i++){
//		long long x;
//		scanf("%lld", &x);
//		admin[x].push_back(i);
//	}
//	for (long long i = 1; i <= n; i++){
//		scanf("%lld", &goal[i].goal);
//	}
//		
//	scanf("%lld",&k);
//
//	for (long long i = 1; i <= n; i++){
//		goal[i].left = 1, goal[i].right = k + 1; //
//	}
//	for (long long i = 1; i <= k; i++){
//		scanf("%lld %lld %lld", &forcast[i].from, &forcast[i].to, &forcast[i].a);
//	}
//
//	bool isFindAll = true;
//	while (isFindAll){
//		isFindAll = false;
//		memset(tree, 0, sizeof(tree));
//		for (long long i = 1; i <= n; i++){   //각 국가가 들어가야 한다.
//			auto p = goal[i];
//			long long left = p.left;
//			long long right = p.right;
//			if (left < right){
//				long long mid = (left + right) >> 1;
//				query[mid].push_back(i);
//				isFindAll = true;
//			}
//		}
//		//트리 업데이트 후, 쿼리 포문
//		for (long long i = 1; i <= k; i++){
//			long long from = forcast[i].from;
//			long long to = forcast[i].to;
//			long long a = forcast[i].a;
//			if (from <= to){    
//				update(from, a);   //이렇게 하면 range update 효과가 나타난다. 아하.
//				if (to + 1 <= m)
//					update(to + 1, -a);
//			}
//			else{
//				update(from, a);
//				update(1, a);
//				if (to + 1 <= m)
//					update(to + 1, -a);
//			}
//
//			while(query[i].size()){
//				long long who = query[i].back();
//				query[i].pop_back();
//				long long sum = 0;
//				auto& p = goal[who];
//				for (long long w = 0; w < admin[who].size(); w++){
//					long long idx = admin[who][w];
//					sum += tree_query(idx);
//					if (sum >= p.goal)
//						break;
//					
//				}
//				if (sum >= p.goal){
//					//ans[who] = i;
//					p.right = i;
//				}
//				else{
//					p.left = i + 1;
//				}
//			}
//
//		}
//	}
//	for (long long i = 1; i <= n; i++){
//		if (goal[i].left == k+1)
//			printf("NIE\n");
//		else
//			printf("%lld\n", goal[i].left);
//	}
//
//	return 0;
//}