#include<tuple>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;

struct Sub{
	string name;      //또는 string tuple 비교할때 char는 안 될 수도 있다.
	int kor,eng,math;
};

bool cmp(const Sub& u, const Sub& v){
	return make_tuple(-u.kor, u.eng, -u.math, u.name) < make_tuple(-v.kor, v.eng, -v.math, v.name);       //true 일 경우 u 를 v 앞에 두어라.
}
int main(){
	int N;
	cin >> N;

	Sub* M = new Sub[N];
	for (int i = 0; i < N; i++)
		cin >> M[i].name >> M[i].kor >> M[i].eng >> M[i].math;
	
	sort(M,M+N,cmp);
	
	for (int i = 0; i < N; i++)
		cout << M[i].name << "\n";
	return 0;
}