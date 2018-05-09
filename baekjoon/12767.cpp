#include<iostream>
#include<set>
#include<string>
using namespace std;

int lr[52][52][2];    //left : 0, right: 1
int v[52][52];
set<string> st;

void preorder(int num, int cur,int node , string& s){
	if (v[num][cur] == 0){
		return;
	}

	s += to_string(node);
	preorder(num, lr[num][cur][0],2*node , s);
	preorder(num, lr[num][cur][1],2*node+1 , s);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++){
		cin >> v[i][1];          //첫번째 노드만 예외적으로 루트로 박아 놓는다. lr을 사용하면 안됨.
		for (int j = 2; j <= k; j++){
			cin >> v[i][j];
			int cur = 1;
			while (true){
				if (v[i][j] > v[i][cur]){
					if (lr[i][cur][1] == 0){
						lr[i][cur][1] = j;
						break;
					}
					else{
						cur = lr[i][cur][1];
					}
				}
				else{
					if (lr[i][cur][0] == 0){
						lr[i][cur][0] = j;
						break;
					}
					else{
						cur = lr[i][cur][0];
					}
				}
			}
		}
	}

	for (int i = 1; i <= n; i++){
		string s = "";
		preorder(i, 1, 1,s);
		st.insert(s);
	}
	cout << st.size();
	return 0;
}
//#include<iostream>
//#include<set>
//#include<string>
//using namespace std;
//
//int tree[51][2500000];
//set<string> st;
//
//void make_tree(int num, int node, int x){
//	if (tree[num][node] == 0){
//		tree[num][node] = x;
//		return;
//	}
//
//	if (x < tree[num][node]){
//		make_tree(num, 2 * node, x);
//	}
//	else{
//		make_tree(num, 2 * node + 1, x);
//	}	
//}
//
//void preorder(int num, int node,string& s){
//	if (tree[num][node] == 0){
//		return;
//	}
//
//	s += to_string(node);
//	preorder(num, 2 * node,s);
//	preorder(num, 2 * node + 1,s);
//	
//}
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	int n,k;
//	cin >> n >> k;
//	for (int i = 1; i <= n; i++){
//		for (int j = 0; j < k; j++){
//			int x;
//			cin >> x;
//			make_tree(i, 1, x);
//		}
//	}
//	
//	for (int i = 1; i <= n; i++){
//		string s = "";
//		preorder(i, 1, s);
//		st.insert(s);
//	}
//	cout << st.size();
//	return 0;
//}
//
