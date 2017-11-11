//#include<queue>
//#include<vector>
//#include<iostream>
//#include<string>
//#include<list>
//using namespace std;
//
//int main(){
//	string a,t;
//	string q,rq="";
//	list<char> L;
//	cin >> a;
//	cin >> t;
//	int alength=a.length();
//	int tlength = t.length();
//
//	if (alength > tlength){
//		cout << t;
//		return 0;
//	}
//	for (int i = 0; i < t.length(); i++){
//		L.push_back(t.at(i));
//	}
//	auto li = L.begin();
//	auto le = --L.end();
//	for (int i = 0;i<alength-1;i++){
//		q += *li;
//		li++;
//	}
//	
//	for (; li != L.end(); li++){     //여기서 에러
//		   //1.앞에서부터 비교
//		q += *li;               //맨앞 예외.
//
//		if (q == a){
//			auto eli = ++li;
//			for (int i = 0; i < alength; i++){         //alength만큼 tli를 이동시키면 범위 벗어날 수 있다.
//				li--;
//			}
//			auto bli = li;
//			li--;
//			L.erase(bli,eli);
//			for (auto li3 = L.begin(); li3 != L.end(); li3++){
//				cout << *li3;
//			}
//			cout << '\n';
//			q = "";
//			q += *li;
//			q += *eli;
//
//
//
//			auto li2 = --L.end();
//			for (int i = 0; i<alength - 1; i++){
//				rq = (*li2) + rq;
//				li2--;
//			}
//		     
//			for (; li2 != L.begin(); li2--){           //L.begin()으로 하면 예외 생길 수 있다.
//				rq = (*li2) + rq;
//
//				if (rq == a){
//					auto bli2 = li2;
//					for (int i = 0; i < alength; i++){         //alength만큼 tli를 이동시키면 범위 벗어날 수 있다.
//						li2++;
//					}
//					auto eli2 = li2;
//					L.erase(bli2,eli2);
//					for (auto li3 = L.begin(); li3 != L.end(); li3++){
//						cout << *li3;
//					}
//					cout << '\n';
//					rq = "";
//					rq += *li2;
//					rq += *eli2;
//					break;
//				}
//				else{
//					rq.erase(rq.begin());
//				}
//			}
//		}
//		else{
//			q.erase(q.begin());
//		}
//		//2.a의 length만큼 저장한 후에 a와 비교 
//		//3.a와 같으면 연결 끊어버리기
//		//4.다르면 계속 넘어감.
//	}
//	return 0;
//}
#include<stdio.h>
#include<stack>
#include<vector>
#include<string>
using namespace std;

int main(){
	vector<char> T;
	stack<char> L, R;
	string sA;
	char t = NULL;
	while (t != '\n'){
		scanf("%c",&t);
		sA += t;
	}
	sA.erase(sA.size() - 1);
	t = NULL;
	while (t != '\n'){
		scanf("%c", &t);
		T.push_back(t);
	}
	int tsize = T.size()-1;
	int asize = sA.size();
	int lidx = 0 -1;
	int ridx = tsize - 1 +1;
	
	bool goRight = false;
	while (ridx-lidx > 1){ 
		L.push(T[++lidx]);
		string comp;
		for (int i = 0; (i < asize) && (!L.empty()); i++){
			comp=L.top()+comp;
			L.pop();
		}
		if (sA == comp){
			goRight = true;
		}
		else{
			int csize = comp.size();
			for (int i = 0; i <csize; i++){
				L.push(comp.at(i));
			}
		}



		while (goRight && ridx - lidx > 1){
			R.push(T[--ridx]);
			string comp2;
			for (int i = asize - 1; i >= 0 && (!R.empty()); i--){
				comp2 += R.top();
				R.pop();
			}
			if (sA == comp2){
				goRight = false;
			}
			else{
				int csize = comp2.size();
				for (int i = csize-1; i >= 0; i--){
					R.push(comp2.at(i));
				}
			}
		}
	}
	

	while (!L.empty()){
		R.push(L.top());
		L.pop();
		string comp2;
		for (int i = asize - 1; i >= 0 && (!R.empty()); i--){
			comp2 += R.top();
			R.pop();
		}

		if (comp2 == sA){
			continue;
		}
		else{
			int csize = comp2.size();
			for (int i = csize - 1; i >= 0; i--){
				R.push(comp2.at(i));
			}
		}
	}
	
	while (!R.empty()){
		printf("%c",R.top());
		R.pop();
	}

	return 0;
}