#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	int k;
	scanf("%d", &k);
	while (k !=0){
		vector<int> a,b;
		int t;
		for (int i = 0; i < k; i++){
			scanf("%d",&t);
			a.push_back(t);
			if (i < 6)
				b.push_back(0);
			else
				b.push_back(1);
		}

		do{
			for (int i = 0; i < k; i++){
				if (b[i] == 0)
					printf("%d ",a[i]);
			}
			printf("\n");
		} while (next_permutation(b.begin(),b.end()));
		printf("\n");
		scanf("%d", &k);
	}
	return 0;
}