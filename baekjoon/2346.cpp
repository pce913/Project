#include<iostream>
#include<list>
using namespace std;
int x;
int tx;
int rsize;
list<pair<int, int>> R;
auto it = R.begin();
auto tempit = it;
void calc(){
	tx = 0;
	if (rsize>1)
		tx = (it->first) % (rsize - 1);

	x = (tx != 0) ? tx : it->first;    //몇 칸을 움직일 것인가.

	cout << it->second << " ";
	if (x>0)
		it = (it == (--R.end())) ? R.begin() : ++it;
	else
		it = (it == R.begin()) ? (--R.end()) : --it;

	R.erase(tempit);
	rsize--;
}

int main(){
	int N;
	int temp;
	cin >> N;
	for (int i = 1; i < N + 1; i++){
		cin >> temp;
		R.push_back(make_pair(temp, i));
	}
	rsize = R.size();
	it = R.begin();
	tempit = it;

	calc();
	for (int i = 0; i < N - 1; i++){             //갯수 하나 적게
		if (x > 0){
			for (int j = 0; j < x - 1; j++){
				if (it == (--R.end())){
					it = R.begin();
					continue;
				}
				it++;
			}
		}
		else{
			x = -x;
			for (int j = 0; j < x - 1; j++){
				if (it == R.begin())
					it = R.end();
				it--;
			}
		}

		tempit = it;
		calc();
	}
	return 0;
}