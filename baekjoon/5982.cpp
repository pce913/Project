#include<iostream>
#include<string>
using namespace std;

string words[1005];
string D[1005];        //D[k]: 뒤에서 k까지 보았을때 답이 되는 경우. (not 경우의 수) 답은 D[0]에 저장되어 있다.
string pass;
bool canGo(int x, int y){
	bool isMatch = true;
	for (int i = 0; i < words[y].size(); i++){
		if (pass[x + i] != '?' && pass[x + i] != words[y][i]){
			isMatch = false;
			break;
		}
	}
	return isMatch;
}
//bool canGo(int x, int y){
//	bool isMatch = true;
//	for (int i = 0; i <words[y].size(); i++){
//		if (pass[x - i] != '?' && pass[x - i] != words[y][words[y].size()-1-i]){
//			isMatch = false;
//			break;
//		}
//	}
//	return isMatch;
//}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int l, n;

	cin >> l >> n;
	cin >> pass;
	for (int i = 0; i < n; i++){
		cin >> words[i];
	}
	for (int i = l - 1; i >= 0; i--){
		for (int j = 0; j < n; j++){
			int k = i + words[j].length();
			if (k>l)
				continue;

			if (k==l || D[k] != ""){        //D[k] 가 비어있지 않거나, k==l 일 경우
				if (canGo(i, j)){
					if (D[i] == "" || D[i] > words[j] + D[k]){   //사전순 출력을 위해
						D[i] = words[j] + D[k];    //D[i] 를 만들기 위해 words와 D[k]를 합친다. 아하. D[k]인 이유를 깨달았다.
					}
				}
			}
		}
	}
	cout << D[0] << "\n";
	//for (int i = 0; i < l; i++){

	//	for (int j = 0; j < n; j++){
	//		int k = i - words[j].length();
	//		if (k<-1)
	//			continue;

	//		if (k == -1 || D[k] != ""){
	//			if (canGo(i, j)){
	//				if (k == -1){
	//					if (D[i] == "" || D[i]> words[j]){
	//						D[i] = words[j];
	//					}
	//				}
	//				else{
	//					if (D[i] == "" || D[i] > D[k] + words[j]){
	//						D[i] = D[k] + words[j];
	//					}
	//				}		
	//			}
	//		}
	//	}
	//}
	//cout << D[l-1] << "\n";
	return 0;
}