#include<stdio.h> 
#include<string.h>
int main() { int i, j, t, animalSize; scanf("%d", &t); while (t--) { char animal[100][101], all[10001], name[101], goes[5], said[101]; char *fox; while (getchar() != '\n'); gets(all);; i = animalSize = 0; while (1) { scanf("%s %s %s", name, goes, said); if (strcmp(goes, "goes")) break; strcpy(animal[animalSize++], said); } fox = strtok(all, " "); while (fox != NULL) { j = 1; for (i = 0; i < animalSize; i++) if (!strcmp(fox, animal[i])) { j = 0; break; } if (j) printf("%s ", fox); fox = strtok(NULL, " "); } puts(""); } return 0; }
//#include<stdio.h>
//#include<stdlib.h>
//#include<cstring>
//#include<string.h>
//#include<algorithm>
//#include<iostream>
//using namespace std;
//char question[] = "what does the fox say?";
//char input[20005];
//char temp[105];
//char hole[105][105];
//long long hash_set1[1005], hash_set2[1005];
//long long tn = 0;
//long long MOD1 = 1e9 + 513, MOD2 = 1e9 + 531;   //문자열 길이가 작으므로 1000만 + 513 소수로 잡음
//long long BASE = 27;
//bool check[105];
////27진법 +1 로 하자.
//void make_hash_set(long long idx){
//	long long t_hash1 = 0;
//	long long t_hash2 = 0;
//	for (long long i = 0; i < tn; i++){
//		t_hash1 = (t_hash1*BASE + (temp[i] - 'a' + 1)) % MOD1;
//		t_hash2 = (t_hash2*BASE + (temp[i] - 'a' + 1)) % MOD2;
//	}
//	hash_set1[idx] = t_hash1;
//	hash_set2[idx] = t_hash2;
//}
//
//long long get_hash1(char c[]){
//	long long t_hash1 = 0;
//	for (long long i = 0; i < tn; i++){
//		t_hash1 = (t_hash1*BASE + (c[i] - 'a' + 1)) % MOD1;
//	}
//	return t_hash1;
//}
//
//long long get_hash2(char c[]){
//	long long t_hash2 = 0;
//	for (long long i = 0; i < tn; i++){
//		t_hash2 = (t_hash2*BASE + (c[i] - 'a' + 1)) % MOD2;
//	}
//	return t_hash2;
//}
//
//void init(){
//	memset(check, false, sizeof(check));
//	for (int i = 0; i < 1001; i++){
//		hash_set1[i] = hash_set1[i] = 0;
//	}
//	tn = 0;
//}
//
//void solve(){
//	init();
//	gets(input);
//	long long n = strlen(input);
//	long long hn = 0;  //전체 단어 갯수
//	for (long long i = 0;i < n; i++){
//		if (input[i] != ' '){
//			temp[tn++] = input[i];
//		}
//		else{
//			for (long long j = 0; j < tn; j++){
//				hole[hn][j] = temp[j];  //각각의 단어를 저장하고 있음.
//			}
//			hole[hn][tn] = '\0';
//			make_hash_set(hn);
//			tn = 0;
//			hn++;
//		}
//	}
//
//	while (true){
//		gets(input);
//		if (strcmp(input, question) == 0)
//			break;
//		long long nn = strlen(input);
//		tn = 0;
//		for (long long i = nn - 1; i >= 0; i--){
//			if (input[i] != ' '){
//				temp[tn++] = input[i];
//			}
//			else
//				break;
//		}
//		reverse(temp, temp + tn);
//		long long h1 = get_hash1(temp);
//		long long h2 = get_hash2(temp);
//		for (long long i = 0; i < hn; i++){   //전체 단어들을 확인해봄
//			if (hash_set1[i] == h1 && hash_set2[i] == h2){
//				check[i] = true;
//			}
//		}
//	}
//	for (long long i = 0; i < hn; i++){
//		if (!check[i]){
//			printf("%s ",hole[i]);
//		}
//	}
//	printf("\n");
//}
//
//int main(){
//	long long T;
//	scanf("%lld",&T);
//	getchar();
//	for (long long test = 1; test <= T; test++){
//		solve();
//	}
//	return 0;
//}
