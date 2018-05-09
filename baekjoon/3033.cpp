//#include <cstdio>
//#include <vector>
//using namespace std;
//const int MOD = 100003;
//char W[200001];
//vector<int> pos[MOD]; // pos[i]: 해시값이 i인 부분 문자열의 등장 위치들
//inline int mod(long long n){
//	if (n >= 0) return n % MOD;
//	return ((-n / MOD + 1)*MOD + n) % MOD;
//}
//
//int main(){
//	int L;
//
//	scanf("%d %s", &L, W);
//
//	int lo = 0, hi = L; // lo: 가능, hi: 불가능
//	while (lo + 1 < hi){
//		int mid = (lo + hi) / 2;
//
//		int H = 0, power = 1;
//		for (int i = 0; i < MOD; i++)
//			pos[i].clear();
//		bool found = false;
//
//		// 가능한 모든 위치에서 길이 mid인 부분 문자열들의 해시값을 구해 보며 처리
//		for (int i = 0; i <= L - mid; i++){
//			if (i == 0){
//				for (int j = 0; j<mid; j++){
//					H = mod(H + 1LL * W[mid - 1 - j] * power);
//					if (j < mid - 1) power = mod(power * 2);
//				}
//			}
//			else H = mod(2 * (H - 1LL * W[i - 1] * power) + W[i + mid - 1]);
//
//			// 해시값 충돌이 일어남
//			if (!pos[H].empty()){
//				// 같은 문자열이 앞서 등장했는지 모두 비교
//				for (int p : pos[H]){
//					bool same = true;
//					for (int j = 0; j<mid; j++){
//						if (W[i + j] != W[p + j]){
//							same = false;
//							break;
//						}
//					}
//					// 동일한 부분 문자열이 등장했음
//					if (same){
//						found = true;
//						break;
//					}
//				}
//			}
//			if (found) break; // 찾음
//			else pos[H].push_back(i); // 찾지 못함: 루프 계속
//		}
//
//		// 길이 mid인 부분 문자열이 2번 등장했느냐에 따라 상하값 조절
//		(found ? lo : hi) = mid;
//	}
//	printf("%d\n", lo);
//}


//#include<iostream>
//#include<map>
//#include<string>
//#include<cstring>
//#include<vector>
//using namespace std;
//
//const int MOD = 100003;
//const int sign = 2;
//string s;
////char s[200001];
//int n;
//
//int mod(long long n){
//	if (n >= 0){
//		return n%MOD;
//	}
//	return((-n / MOD + 1)*MOD + n) % MOD;
//}
//
//vector<int> pos[MOD];
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin >> n >> s;
//	int left = 0;
//	int right = s.size();
//	int ans = 0;
//	while (left+1 < right){
//		int mid = (left + right) / 2;
//		for (int i = 0; i < MOD; i++){
//			pos[i].clear();
//		}
//		bool isfound = false;
//		int ss = 1;
//		int hash = 0;
//		for (int i = 0; i <= s.size() - mid; i++){
//			if (i == 0){
//				for (int j = 0; j < mid; j++){
//					hash = mod(hash + 1LL * s[mid - 1 - j]*ss);
//					if (j < mid - 1){
//						ss = mod(sign*ss);
//					}
//				}
//			}
//			else{
//				hash = mod(sign*(hash - 1LL * s[i - 1] * ss) + s[i + mid - 1]);
//			}
//			if (!pos[hash].empty()){
//				for (int p : pos[hash]){
//					bool issame = true;
//					for (int j = 0; j < mid; j++){
//						if (s[i + j] != s[p + j]){
//							issame = false;
//							break;
//						}
//					}
//					if (issame){
//						isfound = true;
//						break;
//					}
//				}
//			}
//			if (isfound){
//				break;
//			}
//			else{
//				pos[hash].push_back(i);
//			}
//		}
//
//		(isfound ? left : right) = mid;
//	}
//	cout << left;
//
//	return 0;
//}
#include<iostream>
#include<map>
#include<string>
#include<cstring>
#include<vector>
using namespace std;

const int MOD = 1e5 + 3;
const int SIGN = 27;
string s;
int n;
vector<int> pos[MOD];
bool go(int len){
	for (int i = 0; i < MOD; i++){
		pos[i].clear();
	}
	int ss = 1;
	int hash = 0;
	for (int i = len - 1; i >= 0; i--){
		hash = (hash + ((s[i] - 'a')*ss) % MOD) % MOD;
		if (i != 0){
			ss = (ss * SIGN) % MOD;
		}
	}
	pos[hash].push_back(len-1);

	for (int i = len; i < s.size(); i++){
		int fidx = i - len;
		hash = (hash - ((s[fidx] - 'a')*ss) % MOD + MOD) % MOD;  //맨 앞자리수 빼주기
		//hash = (ss*(hash - ((s[fidx] - 'a'))) % MOD + MOD) % MOD;  //맨 앞자리수 빼주기
		hash = (hash * SIGN) % MOD;
		hash = (hash + (s[i] - 'a')) % MOD;  //맨 뒤자리수 더해주기
		
		if (!pos[hash].empty()){
			bool isSame = true;
			for (int j = pos[hash].size() - 1; j >= 0; j--){
				int x = pos[hash][j];
				for (int k = 0; k < len; k++){
					if (s[i - k] != s[x - k]){
						isSame = false;
						break;
					}
				}
				if (isSame)
					return true;
			}
		}

		pos[hash].push_back(i);
	}
	return false;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> s;
	int left = 1;
	int right = s.size();
	int ans = 0;
	while (left <= right){
		int mid = (left + right) >> 1;
		if (go(mid)){
			ans = mid;
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}
	cout << ans;

	return 0;
}
//#include<iostream>
//#include<map>
//#include<string>
//#include<cstring>
//using namespace std;
//
//const long long MOD1 = 1e9 + 7;
////const long long MOD2 = 1e9 + 9;
////const int MOD1 = 756839;
////const int MOD2 = 859433;
//const long long SIGN = 27;
//
//int cnt1[10000010];
//int cnt2[10000010];
//string s;
//int n;
//bool go(int len){
//	map<int, int> mm1;
//	//map<int, int> mm2;
//	//memset(cnt1, 0, sizeof(cnt1));
//	//memset(cnt2, 0, sizeof(cnt2));
//	long long ss1 = 1;
//	long long ss2 = 1;
//	long long hash1 = 0;
//	long long hash2 = 0;
//	for (int i = len - 1; i >= 0; i--){
//		hash1 = (hash1 + ((s[i] - 'a')*ss1) % MOD1) % MOD1;
//		//hash2 = (hash2 + ((s[i] - 'a')*ss2)% MOD2) % MOD2;
//		if (i != 0){
//			ss1 = (ss1 * SIGN) % MOD1;
//			//ss2 = (ss2 * SIGN) % MOD2;
//		}
//	}
//	mm1[hash1]++;
//	//mm2[hash2]++;
//	//cnt1[hash1]++;
//	//cnt2[hash2]++;
//
//	for (int i = len; i < s.size(); i++){
//		int fidx = i - len;
//		hash1 = (hash1 - ((s[fidx] - 'a')*ss1) % MOD1 + MOD1) % MOD1;  //맨 앞자리수 빼주기
//		//hash2 = (hash2 - ((s[fidx] - 'a')*ss2)%MOD2 + MOD2)%MOD2;
//
//		hash1 = (hash1 * SIGN) % MOD1;
//		//hash2 = (hash2 * SIGN)%MOD2;
//
//		hash1 = (hash1 + (s[i] - 'a')) % MOD1;  //맨 뒤자리수 더해주기
//		//hash2 = (hash2 + (s[i] - 'a')) % MOD2;
//		mm1[hash1]++;
//		//mm2[hash2]++;
//		if (mm1[hash1] >= 2){ //  && mm2[hash2] >= 2    //바이너리 서치 사용이 잘못되었다.
//			return true;            //예를들면 정답이 540 인데, mid가 511인 경우 길이가 511인 문자열 중에
//		}                          //두번 등장하는 녀석이 없다면 mid값이 작아지므로 올바른 값을 얻지 못한다.   아니다. 맞게 사용하고 있다. 슈퍼마리오 블로그 참고.
//		/*	cnt1[hash1]++;
//		cnt2[hash2]++;
//		if (cnt1[hash1] >= 2 && cnt2[hash2] >= 2){
//		return true;
//		}*/
//
//	}
//	return false;
//}
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cin >> n >> s;
//	int left = 1;
//	int right = n;
//	int ans = 0;
//	while (left <= right){
//		int mid = (left + right) >> 1;
//		if (go(mid)){
//			ans = mid;
//			left = mid + 1;
//		}
//		else{
//			right = mid - 1;
//		}
//	}
//	cout << ans;
//
//	return 0;
//}