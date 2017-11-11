#include<stdio.h>
#include<algorithm>
using namespace std;
int N = 0;
void copy(int a[], int b[]){
	for (int i = 0; i < N; i++)
		a[i] = b[i];
}

bool comp(int a[], int b[]){
	for (int i = 0; i < N; i++){
		if (a[i]>b[i])
			return true;
	}
	return false;
}


int main(){
	while (scanf("%d",&N)==1){
		int mini[51];
		int w;
		int check2;
		int A[51];
		int temp[51];
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		
		sort(A, A + N);
		A[N] = NULL;
		copy(temp, A);
		bool check;

		if (N == 1)
			mini[0] = A[0];
		for (int k = 0; k < N - 1; k++){
			copy(A, temp);
			check = true;

			for (int i = k; i<N-1; i++){
				for (int j = k; j < N-1; j++){ 
					if (A[j] + 1 == A[j + 1])          
					{
						w = 2;
						check2 = true;
						while (w<N - j){
							if (A[j + 1] == A[j + w] || A[j + 1] - 1 == A[j + w]){ 
								w++;
							}
							else{
								swap(A[j + 1], A[j + w]);
								check2 = false;
								break;
							}
						}
						if (check2 == true)
							swap(A[j], A[j + 1]);
					}
				}
			}


			for (int x = 0; x < k; x++){
				if (A[x] + 1 == A[x + 1]){
					check = false;
					break;
				}
			}
			if (check == true){
				if (k == 0)
					copy(mini, A);
				else if (comp(mini, A))
					copy(mini, A);
			}
	
		}

		
		for (int i = 0; i < N; i++)
			printf("%d ", mini[i]);

		printf("\n");
	}
		
	return 0;
}