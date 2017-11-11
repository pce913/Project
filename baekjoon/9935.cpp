//#include<iostream>
//#include<string>
//using namespace std;
//
//struct Info{
//	int sidx, tidx;
//};
//
//bool check[1000005];
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	string s,t;
//	cin >> s>>t;
//
//	Info p = {-1,-1};
//	for (int i = 0; i < s.size(); i++){
//		if (p = && s[i] == t[0]){
//			p = { i, 0 };
//		}
//	}
//
//	return 0;
//}

#include<iostream>
#include<stack>
#include<string>
using namespace std;
const int MAXN = 1000001;
bool check[MAXN];

struct Index{
	int sidx, bidx;
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	string bumb;
	cin >> s >> bumb;
	int cnt = 0;
	if (bumb.size() <= 1){
		for (int i = 0; i < s.size(); i++){
			if (s[i] == bumb[0]){
				check[i] = true;
				cnt++;
			}
		}
		if (cnt != s.size()){
			for (int i = 0; i < s.size(); i++){
				if (!check[i]){
					cout << s[i];
				}
			}
		}
		else{
			cout << "FRULA";
		}
		
		return 0;
	}

	stack<Index> st;
	for (int i = 0; i < s.size(); i++){
		if (s[i] == bumb[0]){   //폭발문자열의 첫번째 글자는 무조건 넣어준다.
			st.push({i,0});
		}
		else{
			if (!st.empty()){   //스택이 비어있다면 그냥 넘어가기.
				auto p = st.top();
				if (s[i] == bumb[p.bidx + 1]){
					st.push({ i, p.bidx + 1 });
					if (p.bidx + 1 == bumb.size() - 1){  //폭발문자열이 완성됐다면
						for (int k = 0; k < bumb.size(); k++){ //완성된 폭발문자열은 스택에서 지운다.
							auto bb = st.top();
							check[bb.sidx] = true;   //답을 출력하기 위함.
							cnt++;
							st.pop();
						}
					}
				}
				else{  //폭발문자열이 아닌 패턴이 들어왔을경우
					while (!st.empty()){   //스택을 몽땅 비워준다.
						st.pop();
					}
				}

			}
		}
	}
	if (cnt != s.size()){
		for (int i = 0; i < s.size(); i++){
			if (!check[i]){
				cout << s[i];
			}
		}
	}
	else{
		cout << "FRULA";
	}
	return 0;
}