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