#include<stdio.h>
int M[1001];
bool check[1001];
int main(){
	int T, N;
	scanf("%d", &T);
	for (int t = 0; t < T; t++){
		scanf("%d",&N);
		for (int i = 1; i <= N; i++){
			scanf("%d", &M[i]);
			check[i] = false;
		}
		int i = 1;
		int com = 0;
		int temp = 2;
		int count = 0;
		while (count <= N){
			if (check[i] == true){
				com++;
				if (count >= N)
					break;
				for (int h = temp; h <= N; h++){
					if (check[h] == false){
						i = h;
						temp = h+1;
						break;
					}
				}
			}
			else{
				check[i] = true;
				i = M[i];
				count++;
			}
		}
		printf("%d\n",com);
	}
	return 0;
}