#include<stdio.h>
#include<cmath>

char M[6500][6500];


int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= 2 * n - 1; j++){
			M[i][j] = ' ';
		}
	}
	M[1][n] = '*';
	M[2][n - 1] = '*';
	M[2][n + 1] = '*';
	for (int i = n - 2; i <= n + 2; i++){
		M[3][i] = '*';
	}


	int px = 1;
	int py = n-2;
	int clx;
	int cly;
	int crx;
	int cry;

	int blx = px;
	int bly = py;
	int brx = px;
	int bry = py;
	int ylen = 0;
	int h = log2(n / 3);
	clx = px;
	crx = py;
	cly = px;
	cry = py;
	//전략: 첫번째만 예외적으로 처리해주고 나머지는 for문으로 처리.
	for (int k = 1; k <= h; k++){
		clx = clx + 2*blx;    //x: 0 3 6 12 24   //바로 직전에 값의 두배씩 늘어난다. 3부터 들어가야 한다.
		cly = bly - 2*ylen;    //y: 0 3 9 21   -> 전에 움직인 거리의 2배씩 늘어난다.
		if (k == 1){
			cly = bly - 3;
		}
		crx = crx + 2 * brx;
		cry = bly + 2 * ylen;
		blx = clx;
		bly = cly;
		brx = crx;
		bry = cry;
		ylen = 2 * ylen;

		int w = clx;
		int z = cly;

		int sx = px;
		int sy = cly + 3*k;
		int ex = clx - 1;
		int ey = cry;
		for (int i = sx; i <= ex; i++){
			for (int j = sy; j <=ey ; j++){
				M[w][z] = M[i][j];
				z++;
			}
			w++;
			z = 1;
		}

		w = crx;
		z = cry;
		for (int i = px; i <= clx - 1; i++){
			for (int j = py; j <= 2 * clx - 1; j++){
				M[w][z] = M[i][j];
				z++;
			}
			w++;
			z = 1;
		}

		bx = sx;
		by = sy;
	}


	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= 2 * n - 1; j++){
			printf("%c", M[i][j]);
		}
		printf("\n");
	}
	return 0;
}