#include "stdafx.h"
#include "main.h"
#include "dir.h"

int nVpath;
int DWidth = 10;//global_intlengF;	//5


void Direction::GetDir(int n_quant_, float grad_thr_, float cl_tanh_he_thr_, int cl_itr_)
{
	grad_thr = grad_thr_;
	cl_tanh_he_thr = cl_tanh_he_thr_;
	cl_itr = cl_itr_;
	n_quant = n_quant_;

	cout << "computing direction..." << endl;


	NewMem();

	GetGrad();
	GetTangent();
	preprocessVpath();	// coherent line, vectorize cl, amap, fdir, fdir_
	DoTdirOption();

	Set_res_dir();

	cout << "done!" << endl;
}

int partition(int s, int e, V3DI *a)
{
	int low, high;
	float p;
	V3DI temp;

	p = a[e][2];
	low = s;
	high = e - 1;
	while (low <= high){
		while ((low <= e) && (high >= low) && (p < a[low][2]))	low++;
		while ((high >= s) && (high >= low) && (p >= a[high][2]))	high--;
		if (low <= high) {
			//			swap(&a[low], &a[high]);
			vcopy3i(temp, a[low]);
			vcopy3i(a[low], a[high]);
			vcopy3i(a[high], temp);

		}
	}
	//	swap(&a[low], &a[e]);
	vcopy3i(temp, a[low]);
	vcopy3i(a[low], a[e]);
	vcopy3i(a[e], temp);
	return low;
}

void qs(int s, int e, V3DI *a)
{
	if (s >= e)
		return;

	int p = partition(s, e, a);

	qs(s, p - 1, a);
	qs(p + 1, e, a);
}

int disjoint(V3DF min1, V3DF max1, V3DF min2, V3DF max2)
{
	return (((max2[0] > max1[0]) && (min2[0] > max1[0])) || ((max1[0] > max2[0]) && (min1[0] > max2[0]))) ||
		(((max2[1] > max1[1]) && (min2[1] > max1[1])) || ((max1[1] > max2[1]) && (min1[1] > max2[1])));
}



void Direction::GetGrad(){
	float **imG = new float *[MAX_X];	//Gaussian적용된 gray image
	for (int i = 0; i<MAX_X; i++){
		imG[i] = new float[MAX_Y];
	}
	GaussianFilter(im, imG, MAX_X, MAX_Y);

	int cnt = 0;
	int row, col;
	int colOffset, rowOffset;
	int colTotal, rowTotal;
	float GxMask[3][3];				// Sobel mask in the x direction
	float GyMask[3][3];				// Sobel mask in the y direction
	float Gx, Gy;	// Sum of Sobel mask products values in the x,y direction

	/* Declare Sobel masks */
	GxMask[0][2] = -1.0f; GxMask[1][2] = 0.0f; GxMask[2][2] = 1.0f;
	GxMask[0][1] = -2.0f; GxMask[1][1] = 0.0f; GxMask[2][1] = 2.0f;
	GxMask[0][0] = -1.0f; GxMask[1][0] = 0.0f; GxMask[2][0] = 1.0f;

	GyMask[0][2] = 1.0f; GyMask[1][2] = 2.0f; GyMask[2][2] = 1.0f;
	GyMask[0][1] = 0.0f; GyMask[1][1] = 0.0f; GyMask[2][1] = 0.0f;
	GyMask[0][0] = -1.0f; GyMask[1][0] = -2.0f; GyMask[2][0] = -1.0f;

	float vmax = -INFINITY;
	/* Determine edge directions and gradient strengths */
	for (col = 0; col<MAX_X; col++){	//col
		for (row = 0; row<MAX_Y; row++){	//row
			Gx = 0;
			Gy = 0;
			/* Calculate the sum of the Sobel mask times the nine surrounding pixels in the x and y direction */
			for (colOffset = -1; colOffset <= 1; colOffset++) {
				for (rowOffset = -1; rowOffset <= 1; rowOffset++) {
					colTotal = col + colOffset;
					rowTotal = row + rowOffset;
					//경계처리(대칭)
					if (rowTotal<0) rowTotal *= (-1.0f);
					else if (rowTotal >= MAX_Y)	rowTotal = MAX_Y - (rowTotal - (MAX_Y - 1));
					if (colTotal<0) colTotal *= (-1.0f);
					else if (colTotal >= MAX_X)	colTotal = MAX_X - (colTotal - (MAX_X - 1));

					Gx = Gx + (imG[colTotal][rowTotal] * GxMask[colOffset + 1][rowOffset + 1]);//??
					Gy = Gy + (imG[colTotal][rowTotal] * GyMask[colOffset + 1][rowOffset + 1]);//??
				}
			}
			grad[col][row][0] = Gx;
			grad[col][row][1] = Gy;
			grad[col][row][2] = sqrt(Gx*Gx + Gy*Gy);

			if (grad[col][row][2] < grad_thr){	//작은 gradient 제거	//[요기]
				vzero(grad[col][row]);
			}

			//gradMagNorm[col][row] = grad[col][row][2];
			//if ( vmax<gradMagNorm[col][row] )	vmax = gradMagNorm[col][row];
		}
	}
	//	cout << "제거된 gradient " << cnt << "개\n";

	// normalize
	//for (col=0; col<MAX_X; col++)
	//	for (row=0; row<MAX_Y; row++)
	//		gradMagNorm[col][row] = gradMagNorm[col][row] / vmax;

	for (int i = 0; i<MAX_X; i++)	delete[] imG[i];	delete[] imG;
}

void Direction::GetTangent(){
	int i, j;
	V3DF gradient;
	V3DF axis_z = { 0.0f, 0.0f, 1.0f };

	//gradient와 수직
	//tangent = grad x {0,0,1}
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			if (grad[i][j][2] == 0.0f){
				vzero(tangent[i][j]);
				vzero(etf[i][j]);
				continue;
			}
			vector3(gradient, grad[i][j][0], grad[i][j][1], 0.0f);
			vcross(tangent[i][j], gradient, axis_z);
			vcopy(etf[i][j], tangent[i][j]);	//etf 초기화
			//vcopy(sample_flow[i][j], tangent[i][j]);	//etf 초기화
		}
	}
}

void Direction::preprocessVpath(){

	// 1. coherent line
	SetFlowPath();

	for (int i = 0; i<cl_itr; i++)
		SetCoherentLine();

	// 2. vectorize the line
	nVPath = 0;
	SetVectorPath();
	VectorizeVectorPath();

	if (!StreamsExisting){	// Stream이 존재하지 않으면 배경처리
		cout << "Stream이 존재하지 않으므로, 영상 전체를 단일 방향으로 설정합니다.\n";
		SetUniDir();
	}

	// 3. amap, fdir, fdir_
	DmapFor3Files();	// amap
}

void Direction::DoTdirOption(){
	NewDir();

	//int i, j, idx;
	int i, j;
	int **qn_buf = new int *[MAX_X];
	for (i = 0; i<MAX_X; i++)		qn_buf[i] = new int[MAX_Y];
	for (i = 0; i<MAX_X; i++)		for (j = 0; j<MAX_Y; j++)			qn_buf[i][j] = 20;

	// 1. distmap(seed: fdir)
	//    closest fdir -> tdir
	DoDmap(dmap_fdir, fdirFortdir, tdir);

	// 2. option 선택(constant는 나중에 <- 잘 구해진 방향에 영향주므로)
	//float h, s, v;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			qn_buf[i][j] = n_quant;
			//idx = RG_label[i][j];
			//switch ( RG[idx].d_type ){
			//case DIR_EGSR2012:
			//	qn_buf[i][j] = RG[idx].d_nq;
			//	break;
			//case DIR_HUE_BASED:
			//	qn_buf[i][j] = RG[idx].d_nq;
			//	RGBtoHSV(cim_orig[i][j][0], cim_orig[i][j][1], cim_orig[i][j][2], &h, &s, &v);
			//	h *= 180.0f;
			//	h += RG[idx].d_shift_ang;	h = (int)h % 180;	// shift hue
			//	Ang2Vector(h, tdir[i][j]);
			//	break;
			//}
		}
	}

	// 3. Quantize: tdir -> tang_b, tang_t, wei_b
	DoTdirQ(qn_buf, tdir, qtdir);

	// 4. 급격히 변하는 곳의 방향 수정
	if (StreamsExisting){
		CorrectTdir(qn_buf, qtdir);
		GetAvg(tdir);	GetAvg(tdir);	GetAvg(tdir);

		DoTdirQ(qn_buf, tdir, qtdir);

		for (i = 0; i<MAX_X; i++)
		for (j = 0; j<MAX_Y; j++)
			Ang2Vector(qtdir[i][j], tdir[i][j]);
	}

	//// 5. constant 방향
	//for (i=0; i<MAX_X; i++){
	//	for (j=0; j<MAX_Y; j++){
	//		idx = RG_label[i][j];
	//		if ( RG[idx].d_type==DIR_CONSTANT ){
	//			vector(tdir[i][j], RG[idx].d_cnst_x, RG[idx].d_cnst_y, 0.0f);
	//			Vector2Ang(tdir[i][j], &(tang_b[i][j]));
	//			tang_t[i][j] = tang_b[i][j];	wei_b[i][j] = 0.0f;
	//		}
	//	}
	//}

	for (i = 0; i<MAX_X; i++)	delete[] qn_buf[i];	delete[] qn_buf;
}

void Direction::CorrectTdir(int **qn, float **idir){	// 급격히 변하는 곳의 방향 수정
	//printf("	CorrectTdir..");
	int MaskSize = 9;	// only 홀수

	// 1. diffAng // 이웃들이 각도 차이 나는 곳 찾기
	int i, j, r, c;
	if (!diffGrad){
		diffGrad = new float *[MAX_X];
		for (i = 0; i<MAX_X; i++)
			diffGrad[i] = new float[MAX_Y];
	}

	float d;	// = 180.0f / (float)qn;
	float thr;
	float diff;
	int itv = MaskSize / 2;
	float my_qn;

	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			my_qn = qn[i][j];
			d = 180.0f / my_qn;
			thr = d * 2;

			diffAng[i][j] = 1.0f;
			for (r = i - itv; r <= i + itv; r++){
				if (diffAng[i][j] == 0.0f)
					break;
				for (c = j - itv; c <= j + itv; c++){
					if (r<0 || r >= MAX_X || c<0 || c >= MAX_Y)	continue;
					diff = abs(idir[i][j] - idir[r][c]);
					if (diff>thr && diff<180.0f - thr){
						diffAng[i][j] = 0.0f;
						break;
					}
				}
			}
		}
	}

	// 2. diffAng로 gradient 구하기
	GetGradient(MaskSize, diffAng, diffGrad);	// MaskSize가 클수록 급격히 변하는 곳이 더 부드러워진다.

	// 3. diffAng에서, 평균 GetETF(diffA) & 그 수직 구하기
	// 3-1. 평균 GetETF(diffA)
	float **tang = new float*[MAX_X];
	for (i = 0; i<MAX_X; i++){
		tang[i] = new float[MAX_Y];
		for (j = 0; j<MAX_Y; j++)
			tang[i][j] = idir[i][j];
	}
	GetAvg(tang);

	// 3-2. (3-1) 에서 gradient와 더 수직에 가까운 방향 선택
	V3DF v0, v1, v2;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			if (diffAng[i][j] == 0.0f){
				// (diffGrad, tang) vs. (diffGrad, 수직(tang)) --> idir
				Ang2Vector(diffGrad[i][j], v0);
				Ang2Vector(tang[i][j], v1);
				Ang2Vector(tang[i][j], v2);		rotate_vtx_z(v2, 90.0f);

				if (vdot(v0, v1)>vdot(v0, v2))
					idir[i][j] = tang[i][j];
				else
					Vector2Ang(v2, &idir[i][j]);

				Ang2Vector(idir[i][j], tdir[i][j]);
			}
		}
	}

	for (i = 0; i<MAX_X; i++)	delete[] tang[i];	delete[] tang;
}

void Direction::DoTdirQ(int **qn, V3DF **basic_dir, float **odir){	// tang_b, tang_t, wei_b 계산
	//printf("	DoTdirQ..");

	int i, j;
	V3DF vct, zero_degree = { 1.0f, 0.0f, 0.0f };
	if (!tang_b){
		tang_b = new float *[MAX_X];	// [비효율적]
		tang_t = new float *[MAX_X];
		wei_b = new float *[MAX_X];
		for (i = 0; i<MAX_X; i++){
			tang_b[i] = new float[MAX_Y];
			tang_t[i] = new float[MAX_Y];
			wei_b[i] = new float[MAX_Y];
		}
	}

	float tmp, ang, d;
	float range_b, range_t;	// ang의 bottom, top
	//float w_b, w_t;	// weight bottom, top
	float w_b;

	// quantize etf
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			if (is_zero_vector(basic_dir[i][j])){
				tang_b[i][j] = tang_t[i][j] = wei_b[i][j] = -1.0f;
				continue;
			}

			d = 180.0f / (float)qn[i][j];
			vcopy(vct, basic_dir[i][j]);
			vnorm(vct);

			// 1. vector -> angle
			Vector2Ang(vct, &ang);

			// 2. ang 로부터 가장 가까운 quantized dir
			tmp = (ang + d / 2.0f);		tmp = (int)tmp / (int)d;	tmp *= d;
			odir[i][j] = tmp;

			// 3. range
			if (ang > tmp){
				range_b = tmp;
				range_t = tmp + d;
			}
			else{
				range_b = tmp - d;
				range_t = tmp;
			}
			if (range_b == 180.0f)	range_b = 0.0f;
			if (range_t == 180.0f)	range_t = 0.0f;

			// 4. weight (range_b ~ range_t)
			w_b = (d - (ang - range_b)) / d;
			//w_t = (d - (range_t - ang)) / d;
			//ang = (w_b*range_b + w_t*range_t);

			tang_b[i][j] = range_b;
			tang_t[i][j] = range_t;
			wei_b[i][j] = w_b;
		}
	}
}

void Direction::DoDmap(SeedInfo **dmap, V3DF **InSeeds, V3DF **OutDir){
	//printf("	DoDmap..");
	int i, j;

	int cnt;

	// 1. seed 개수 세기, 저장
	V2DI *seeds = new V2DI[MAX_X*MAX_Y];
	cnt = 0;
	int r, c;

	// --- [임시] gradient 방향에서 최대 크기 구하기 ---
	float myGradMag = 0.0f;	// gradient 방향에서 최대 크기
	//V3DF gradMaxPoint;	// gradient가 max인 지점
	//V3DF pre_dir;		// 기준 방향. 이전 벡터와 일관성 위해

	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			if (is_zero_vector(InSeeds[i][j]))		continue;

			seeds[cnt][0] = i;
			seeds[cnt][1] = j;

			// --- [임시] gradient 방향에서 최대 크기 구하기 ---
			//GetTangentAtPoint(i, j, pre_dir);		// gradient와 일관성 위해 +- 방향 변환 안한 tangent를 참조 방향으로 간주한다.
			//myGradMag = GetBetaMaxTwin(i, j, gradMaxPoint, pre_dir);

			dmap[i][j].Set(cnt, 0.0f, InSeeds[i][j], myGradMag, i, j);
			//dmap[i][j].Set(cnt, 0.0f, InSeeds[i][j], gradMagNorm[i][j], i, j);
			dmap[i][j].isseed = true;

			cnt++;
		}
	}

	int nseeds = cnt;

	// 2. Jump flooding algorithm
	int px, py, k, idx, sx, sy;
	float d;
	int n = nseeds;
	k = min(MAX_X, MAX_Y);
	for (k = min(MAX_X, MAX_Y); k >= 1; k = k / 2){
		for (i = 0; i<nseeds; i++){
			// seeds[i]를 전파
			px = seeds[i][0];	py = seeds[i][1];
			for (r = px - k; r <= px + k; r += k){
				for (c = py - k; c <= py + k; c += k){
					if (r == px && c == py)	continue;	// 자신
					// 경계처리
					if (r<0 || r >= MAX_X || c<0 || c >= MAX_Y)	continue;

					//d =	sqrt( (float)(r-px)*(float)(r-px) + (float)(c-py)*(float)(c-py) );	// (r,c)~(px,py)
					// (r,c) ~ (x,y) of (px,py).sid
					idx = dmap[px][py].sid;
					sx = seeds[idx][0];		sy = seeds[idx][1];
					d = sqrt((float)(r - sx)*(float)(r - sx) + (float)(c - sy)*(float)(c - sy));

					if (dmap[r][c].dist>d){
						dmap[r][c].Set(dmap[px][py].sid, d, dmap[sx][sy].dir,
							dmap[sx][sy].BetaMaxGradMag, dmap[sx][sy].sx, dmap[sx][sy].sy);
						//dmap[r][c].dist = d;
						//dmap[r][c].sid = dmap[px][py].sid;
						//vcopy(dmap[r][c].dir, dmap[sx][sy].dir);
						//dmap[r][c].gradMag = dmap[sx][sy].gradMag;
						//dmap[r][c].sx = dmap[sx][sy].sx;
						//dmap[r][c].sy = dmap[sx][sy].sy;

						if (dmap[r][c].isseed == false){
							dmap[r][c].isseed = true;
							seeds[n][0] = r;	seeds[n][1] = c;
							n++;
						}
					}
				}
			}
		}
		nseeds = n;
	}

	delete[] seeds;

	// 3. dir_map, ang_map
	V3DF zero_degree = { 1.0f, 0.0f, 0.0f };
	int cx = MAX_X / 2;	int cy = MAX_Y / 2;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			vcopy(OutDir[i][j], dmap[i][j].dir);	// dir_map <- dmap.dir
		}
	}

	// 4. maximum distance
	maxdist = 0.0f;
	float threshold = INFINITY;	// like DWidth, default: INFINITY
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			if (dmap[i][j].dist>threshold)	continue;
			maxdist = (maxdist<dmap[i][j].dist) ? dmap[i][j].dist : maxdist;
		}
	}

	// 5. dist_arc = dist / maxdist
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			if (dmap[i][j].dist>threshold)
				dmap[i][j].dist_arc = 1.0f;
			else
				dmap[i][j].dist_arc = dmap[i][j].dist / maxdist;
		}
	}

	// 6. dist_by_grad = dist_arc / grad
	float BetaMaxGradMag;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			// dmap[i][j].dist_by_grad = dmap[i][j].dist_arc / (gradMagNorm[i][j]*10.0f + 1.0f);
			// 이게 아니라, seed 의 gradient로 나눠줘야 함.
			//grad2 = MatchValTanh(dmap[i][j].BetaMaxGradMag, 0.0f, 1.0f, 32.0f, 0.5f);
			BetaMaxGradMag = dmap[i][j].BetaMaxGradMag;
			dmap[i][j].dist_by_seed_grad = dmap[i][j].dist_arc / (BetaMaxGradMag + 1.0f);
		}
	}
}

void Direction::NewDir(){
	int i, j;
	if (!dmap_fdir){
		dmap_fdir = new SeedInfo *[MAX_X];
		for (i = 0; i<MAX_X; i++)	dmap_fdir[i] = new SeedInfo[MAX_Y];
	}
	for (i = 0; i<MAX_X; i++)
	for (j = 0; j<MAX_Y; j++)
		dmap_fdir[i][j].Init();

	if (!tdir){
		tdir = new V3DF *[MAX_X];
		for (i = 0; i<MAX_X; i++)	tdir[i] = new V3DF[MAX_Y];
	}
	for (i = 0; i<MAX_X; i++)
	for (j = 0; j<MAX_Y; j++)
		vzero(tdir[i][j]);

	if (!qtdir){
		qtdir = new float *[MAX_X];
		for (i = 0; i<MAX_X; i++)	qtdir[i] = new float[MAX_Y];
	}
	for (i = 0; i<MAX_X; i++)
	for (j = 0; j<MAX_Y; j++)
		qtdir[i][j] = 0.0f;

	if (!diffAng){
		diffAng = new float *[MAX_X];
		for (i = 0; i<MAX_X; i++)	diffAng[i] = new float[MAX_Y];
	}
	for (i = 0; i<MAX_X; i++)
	for (j = 0; j<MAX_Y; j++)
		diffAng[i][j] = 0.0f;
}
int Direction::max_stream(int px, int py){
	int i, j;
	V3DF vec;
	V3DF nvec;
	V3DF Zaxis;
	V3DF tpt1, tpt2;
	int qx, qy;

	int nbhd_cnt = 0;
	vector3(Zaxis, 0.0f, 0.0f, 1.0f);

	float max_cl;
	for (i = 0, max_cl = -1000.0f; i < vpath[px][py].sn; i++) {
		if (i == 0) {
			nvector(vec, vpath[px][py].Alpha[i + 1], vpath[px][py].Alpha[i]);
		}
		else if (i == vpath[px][py].sn - 1) {
			nvector(vec, vpath[px][py].Alpha[i], vpath[px][py].Alpha[i - 1]);
		}
		else {
			nvector(vec, vpath[px][py].Alpha[i + 1], vpath[px][py].Alpha[i - 1]);
		}

		nvcross(nvec, vec, Zaxis);

		vcopy(tpt1, vpath[px][py].Alpha[i]);
		qx = (int)tpt1[0];		if (qx<0)	qx = 0;		else if (qx >= MAX_X)	qx = MAX_X - 1;
		qy = (int)tpt1[1];		if (qy<0)	qy = 0;		else if (qy >= MAX_Y)	qy = MAX_Y - 1;
		if (qx != px && qy != py) {
			if (vpath[qx][qy].sn > 0)
				max_cl = (vpath[qx][qy].cl > max_cl) ? vpath[qx][qy].cl : max_cl;
		}
		for (j = 0; j < 3; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;

			qx = (int)tpt2[0];		if (qx<0)	qx = 0;		else if (qx >= MAX_X)	qx = MAX_X - 1;
			qy = (int)tpt2[1];		if (qy<0)	qy = 0;		else if (qy >= MAX_Y)	qy = MAX_Y - 1;
			if (qx != px && qy != py) {
				if (vpath[qx][qy].sn > 0)
					max_cl = (vpath[qx][qy].cl > max_cl) ? vpath[qx][qy].cl : max_cl;
			}
			vcopy(tpt1, tpt2);
		}

		vnegate(nvec);
		vcopy(tpt1, vpath[px][py].Alpha[i]);
		for (j = 0; j < 3; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;

			qx = (int)tpt2[0];		if (qx<0)	qx = 0;		else if (qx >= MAX_X)	qx = MAX_X - 1;
			qy = (int)tpt2[1];		if (qy<0)	qy = 0;		else if (qy >= MAX_Y)	qy = MAX_Y - 1;
			if (qx != px && qy != py) {
				if (vpath[qx][qy].sn > 0)
					max_cl = (vpath[qx][qy].cl > max_cl) ? vpath[qx][qy].cl : max_cl;
			}
			vcopy(tpt1, tpt2);
		}
	}
	return (vpath[px][py].cl > 0.2f * max_cl);
}

int Direction::close_stream(int nbhd_idx, int **nbhd_board, int px, int py, int qx, int qy, int dist)
{
	//	(px, py) & (qx, qy)
	int i, j;
	V3DF vec;
	V3DF nvec;
	V3DF Zaxis;
	V3DF tpt1, tpt2;

	int nbhd_cnt1 = 0;
	int nbhd_cnt2 = 0;
	vector3(Zaxis, 0.0f, 0.0f, 1.0f);

	//	draw 3-ring band of (px, py)
	for (i = 0; i < vpath[px][py].sn; i++) {
		if (i == 0) {
			nvector(vec, vpath[px][py].Alpha[i + 1], vpath[px][py].Alpha[i]);
		}
		else if (i == vpath[px][py].sn - 1) {
			nvector(vec, vpath[px][py].Alpha[i], vpath[px][py].Alpha[i - 1]);
		}
		else {
			nvector(vec, vpath[px][py].Alpha[i + 1], vpath[px][py].Alpha[i - 1]);
		}

		nvcross(nvec, vec, Zaxis);

		vcopy(tpt1, vpath[px][py].Alpha[i]);
		if (tpt1[0]<0)	tpt1[0] = 0;	else if (tpt1[0] >= MAX_X)	tpt1[0] = MAX_X - 1;
		if (tpt1[1]<0)	tpt1[1] = 0;	else if (tpt1[1] >= MAX_Y)	tpt1[1] = MAX_Y - 1;
		nbhd_board[(int)tpt1[0]][(int)tpt1[1]] = nbhd_idx;
		for (j = 0; j <= dist; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;
			nbhd_board[(int)tpt2[0]][(int)tpt2[1]] = nbhd_idx;
			vcopy(tpt1, tpt2);
		}

		vnegate(nvec);
		vcopy(tpt1, vpath[px][py].Alpha[i]);
		for (j = 0; j <= dist; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;
			nbhd_board[(int)tpt2[0]][(int)tpt2[1]] = nbhd_idx;
			vcopy(tpt1, tpt2);
		}
	}

	//	draw 3-ring band of (qx, qy)
	for (i = 0; i < vpath[qx][qy].sn; i++) {
		if (i == 0) {
			nvector(vec, vpath[qx][qy].Alpha[i + 1], vpath[qx][qy].Alpha[i]);
		}
		else if (i == vpath[qx][qy].sn - 1) {
			nvector(vec, vpath[qx][qy].Alpha[i], vpath[qx][qy].Alpha[i - 1]);
		}
		else {
			nvector(vec, vpath[qx][qy].Alpha[i + 1], vpath[qx][qy].Alpha[i - 1]);
		}

		nvcross(nvec, vec, Zaxis);

		vcopy(tpt1, vpath[qx][qy].Alpha[i]);
		if (tpt1[0]<0)	tpt1[0] = 0;	else if (tpt1[0] >= MAX_X)	tpt1[0] = MAX_X - 1;
		if (tpt1[1]<0)	tpt1[1] = 0;	else if (tpt1[1] >= MAX_Y)	tpt1[1] = MAX_Y - 1;
		if (nbhd_board[(int)tpt1[0]][(int)tpt1[1]] == nbhd_idx) {
			nbhd_board[(int)tpt1[0]][(int)tpt1[1]] *= -1;
			nbhd_cnt1++;
			nbhd_cnt2++;
			continue;
		}
		for (j = 0; j <= dist; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;

			if (nbhd_board[(int)tpt2[0]][(int)tpt2[1]] == nbhd_idx) {
				nbhd_board[(int)tpt2[0]][(int)tpt2[1]] *= -1;
				nbhd_cnt1++;
				break;
			}
			vcopy(tpt1, tpt2);
		}

		vnegate(nvec);
		vcopy(tpt1, vpath[qx][qy].Alpha[i]);
		for (j = 0; j <= dist; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;
			if (nbhd_board[(int)tpt2[0]][(int)tpt2[1]] == nbhd_idx) {
				nbhd_board[(int)tpt2[0]][(int)tpt2[1]] *= -1;
				nbhd_cnt2++;
				break;
			}
			vcopy(tpt1, tpt2);
		}
	}

	//	printf("%d, %d => %d, %d\n", Streams[px][py].nPoints, Streams[qx][qy].nPoints, nbhd_cnt1, nbhd_cnt2);
	//	estimate the 
	if (nbhd_cnt1 >= 0.8f * min2i(vpath[px][py].sn, vpath[qx][qy].sn))
		return 1;
	else
		return 0;
}


void Direction::GetETFAtPoint(float px, float py, V3DF resETF)
{
	int ulx, uly, lrx, lry;		//	upper-left (x, y), lower-right (x, y)
	V3DF etfA, etfB, etfC, etfD;	//	etf at A,B,C,D
	V3DF e1, e2, t1, t2;

	if (px + 1 >= MAX_X || py + 1 >= MAX_Y){
		vector3(resETF, 0.0f, 0.0f, 0.0f);
		return;
	}

	ulx = (int)(px);
	uly = (int)(py + 1);
	lrx = (int)(px + 1);
	lry = (int)(py);
	vcopy(etfA, etf[ulx][lry]);
	vcopy(etfB, etf[lrx][lry]);
	vcopy(etfC, etf[ulx][uly]);
	vcopy(etfD, etf[lrx][uly]);

	//distA: A~(px,py) 거리
	//eA: etf at A
	//1. distB*etfA + distA*etfB
	vcopy(t1, etfA);	vcopy(t2, etfB);
	vscale(t1, lrx - px);	vscale(t2, px - ulx);
	vadd(e1, t1, t2);
	//2. distD*etfC + distC*etfD
	vcopy(t1, etfC);	vcopy(t2, etfD);
	vscale(t1, lrx - px);	vscale(t2, px - ulx);
	vadd(e2, t1, t2);
	//3. distC*1 + distA*2
	vcopy(t1, e1);		vcopy(t2, e2);
	vscale(t1, uly - py);	vscale(t2, py - lry);
	vadd(resETF, t1, t2);

	vnorm(resETF);
	//return vlength(resETF);
}

void Direction::GetETFAtPoint(float px, float py, V3DF resETF, V3DF preDir){


	// 크기 있는 etf로
	int ulx, uly, lrx, lry;		//	upper-left (x, y), lower-right (x, y)
	V3DF etfA, etfB, etfC, etfD;	//	etf at A,B,C,D
	V3DF e1, e2, t1, t2;

	if (px + 1 >= MAX_X || py + 1 >= MAX_Y){
		vzero(resETF);
		return;
	}

	ulx = (int)(px);
	uly = (int)(py + 1);
	lrx = (int)(px + 1);
	lry = (int)(py);
	vcopy(etfA, etf[ulx][lry]);
	vcopy(etfB, etf[lrx][lry]);
	vcopy(etfC, etf[ulx][uly]);
	vcopy(etfD, etf[lrx][uly]);

	// 방향 맞추기
	if (vdot(preDir, etfA)<0.0f)	vscale(etfA, -1.0f);
	if (vdot(preDir, etfB)<0.0f)	vscale(etfB, -1.0f);
	if (vdot(preDir, etfC)<0.0f)	vscale(etfC, -1.0f);
	if (vdot(preDir, etfD)<0.0f)	vscale(etfD, -1.0f);
	// w *= (vdot ( oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]] ) > 0.0f) ? 1.0f : -1.0f;

	//distA: A~(px,py) 거리
	//eA: etf at A
	//1. distB*etfA + distA*etfB
	vcopy(t1, etfA);	vcopy(t2, etfB);
	vscale(t1, lrx - px);	vscale(t2, px - ulx);
	vadd(e1, t1, t2);
	//2. distD*etfC + distC*etfD
	vcopy(t1, etfC);	vcopy(t2, etfD);
	vscale(t1, lrx - px);	vscale(t2, px - ulx);
	vadd(e2, t1, t2);
	//3. distC*1 + distA*2
	vcopy(t1, e1);		vcopy(t2, e2);
	vscale(t1, uly - py);	vscale(t2, py - lry);
	vadd(resETF, t1, t2);

	float Gx = resETF[0];
	float Gy = resETF[1];
	//float size = sqrt(Gx*Gx + Gy*Gy);	if ( size<0.1f )	vzero(resETF);
	vnorm(resETF);
}
void LineBresenham(int x0, int y0, int x1, int y1,
	int *on, V3DF *obuf){	// obuf에 선 위치를 저장
	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;
	if (dy<0){	// 기울기를 양수처리함
		dy = -dy;
		stepy = -1;
	}
	else
		stepy = 1;

	if (dx<0){
		dx = -dx;
		stepx = -1;
	}
	else
		stepx = 1;

	dy <<= 1;	// dy*2
	dx <<= 1;

	int cnt = 0;
	//glBegin(GL_POINTS);	glVertex3f (Window2OpenGL_X (x0), Window2OpenGL_Y (y0), 0.0f);	glEnd();	// setpixel(x0,y0)
	vector3(obuf[cnt++], x0, y0, 0.0f);

	int fraction;
	if (dx>dy){
		fraction = dy - (dx >> 1);	// dx/2
		while (x0 != x1){
			if (fraction >= 0){
				y0 += stepy;
				fraction -= dx;	// fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy;	// fraction -= 2*dy
			//glBegin(GL_POINTS);	glVertex3f (Window2OpenGL_X (x0), Window2OpenGL_Y (y0), 0.0f);	glEnd();	// setpixel(x0,y0)
			vector3(obuf[cnt++], x0, y0, 0.0f);
		}
	}
	else{
		fraction = dx - (dy >> 1);
		while (y0 != y1){
			if (fraction >= 0){
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			//glBegin(GL_POINTS);	glVertex3f (Window2OpenGL_X (x0), Window2OpenGL_Y (y0), 0.0f);	glEnd();	// setpixel(x0,y0)
			vector3(obuf[cnt++], x0, y0, 0.0f);
		}
	}

	*on = cnt;
}

void Direction::DmapFor3Files(int idx, DistInfoSet **dmap, DistInfo **tdmap){
	int i, j, r, c;
	int px = rlist[idx][0];
	int py = rlist[idx][1];
	V3DF dir;
	float tx, ty;
	FlowPath * p = &(vpath[px][py]);
	int n = p->sn;

	int x0, y0, x1, y1;
	int cnt;
	V3DF *buf = new V3DF[MAX_X*MAX_Y];	// 넉넉히
	for (i = 0; i < n - 1; i++){
		//tx = p->Alpha[(i+1>n-1)? n-1: i+1][0] - p->Alpha[(i-1<0)? 0: i-1][0];
		//ty = p->Alpha[(i+1>n-1)? n-1: i+1][1] - p->Alpha[(i-1<0)? 0: i-1][1];
		tx = p->Alpha[i + 1][0] - p->Alpha[i][0];
		ty = p->Alpha[i + 1][1] - p->Alpha[i][1];
		vector3(dir, tx, ty, 0.0f);

		cnt = 0;
		// Bresenham
		x0 = (int)p->Alpha[i][0];		y0 = (int)p->Alpha[i][1];
		x1 = (int)p->Alpha[i + 1][0];	y1 = (int)p->Alpha[i + 1][1];
		LineBresenham(x0, y0, x1, y1, &cnt, buf);

		for (j = 0; j<cnt; j++){
			r = (int)buf[j][0];	if (r<0) r = 0;	else if (r >= MAX_X) r = MAX_X - 1;
			c = (int)buf[j][1];	if (c<0) c = 0;	else if (c >= MAX_Y) c = MAX_Y - 1;
			tdmap[r][c].Set(idx, i, (float)i / (float)n, 0, dir);	// arc 계산 추가
		}
	}

	int k, l;
	cnt = 0;
	while (cnt < DWidth) {	// dist map 두께
		for (i = 1; i < MAX_X - 1; i++) {
			for (j = 1; j < MAX_Y - 1; j++) {
				if (tdmap[i][j].dist == cnt) {
					for (k = -1; k <= 1; k++) {
						for (l = -1; l <= 1; l++) {
							if (k == 0 && l == 0)
								continue;

							if (tdmap[i + k][j + l].dist == INFINITY)
								tdmap[i + k][j + l].Set(idx, tdmap[i][j].p_idx, tdmap[i][j].arc, cnt + 1, tdmap[i][j].direction);
						}
					}
				}
			}
		}
		cnt++;
	}
	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			if (tdmap[i][j].f_idx == idx){
				if (tdmap[i][j].dist < dmap[i][j].dinfo[0].dist) {
					dmap[i][j].Copy(2, 1);
					dmap[i][j].Copy(1, 0);
					dmap[i][j].Set(0, tdmap[i][j]);
				}
				else if (tdmap[i][j].dist < dmap[i][j].dinfo[1].dist) {
					dmap[i][j].Copy(2, 1);
					dmap[i][j].Set(1, tdmap[i][j]);
				}
				else if (tdmap[i][j].dist < dmap[i][j].dinfo[2].dist) {
					dmap[i][j].Set(2, tdmap[i][j]);
				}
			}
		}
	}
	delete[] buf;
}

void Direction::DmapFor3Files(){
	//if ( StreamsExisting ){
	//	cout << "Stream이 존재하지 않으므로, 방향을 계산하지 않습니다.\n";
	//	return;
	//}

	//printf("DmapFor3Files..");
	int i, j, k;

	if (!dmap){
		dmap = new DistInfoSet *[MAX_X];
		for (i = 0; i<MAX_X; i++)
			dmap[i] = new DistInfoSet[MAX_Y];
	}
	for (i = 0; i<MAX_X; i++)
	for (j = 0; j<MAX_Y; j++)
		dmap[i][j].Init();

	DistInfo **tdmap = new DistInfo *[MAX_X];
	for (i = 0; i<MAX_X; i++)
		tdmap[i] = new DistInfo[MAX_Y];

	//printf("1\n");

	for (i = 0; i < min2i(6000, n_qlist); i++) {
		if (vpath[rlist[i][0]][rlist[i][1]].length <= 10)
			break;

		for (j = 0; j < MAX_X; j++)
		for (k = 0; k < MAX_Y; k++)
			tdmap[j][k].Init();

		DmapFor3Files(i, dmap, tdmap);
	}

	//printf("2\n");

	//dmap.dist_arc 구하기 (단, DWidth 이상은 취급X)
	float maxdist = -INFINITY;
	float curdist;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			curdist = dmap[i][j].dinfo[0].dist;
			if (curdist == INFINITY)	continue;
			maxdist = (maxdist<curdist) ? curdist : maxdist;
		}
	}
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			dmap[i][j].dinfo[0].Set_Dist_arc(maxdist);
			dmap[i][j].dinfo[1].Set_Dist_arc(maxdist);
		}
	}

	DoAmap(dmap);	DoFdir(dmap);

	for (i = 0; i<MAX_X; i++)	delete[] tdmap[i];	delete[] tdmap;
	//printf("done\n");
}

void Direction::SetUniDir(){
	int i, j;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			vector3(res_dir[i][j], 1.0f, 0.1f, 0.0f);
			vnorm(res_dir[i][j]);
		}
	}
}

void Direction::VectorizeVectorPath(){	// load_CL()
	int i, j;
	if (!skltn){
		skltn = new int *[MAX_X];
		for (i = 0; i<MAX_X; i++){
			skltn[i] = new int[MAX_Y];
			for (j = 0; j<MAX_Y; j++)
				skltn[i][j] = 0;
		}
	}
	else{
		for (i = 0; i<MAX_X; i++)
		for (j = 0; j<MAX_Y; j++)
			skltn[i][j] = 0;
	}

	build_skltn();			//	모든 pixel에서 skeleton값 계산 -->	0: outside
	//										1: border
	//										2: border에서 한 픽셀 안쪽으로
	//										3: border에서 두 픽셀 안쪽으로
	compute_center_line();	//	Streams[i][j]에서 stream 계산
	//	stream이 계산된 pixel의 index (i, j)를 slist에 저장
	if (!StreamsExisting){	// Stream이 존재하지 않으면
		return;
	}
	build_center_line1();	//	stream들 중에서 max stream 계산
	//	max stream을 plist에 저장
	build_center_line2();	//	이웃한 stream을 찾아서 제거함
	//	이웃한 stream을 제거한 stream들을 qlist에 저장

	sort_length();			//	qlist의 stream들을 길이순으로 저장
	//	길이순으로 정렬한 stream들을 rlist에 저장
	curv_line();			//	compute the curvatures at each point
}

void Direction::SetVectorPath(){	// PushStream(교수님 주신 코드에서 함수명)
	int i, j, k;
	if (!vpath){
		vpath = new FlowPath *[MAX_X];
		for (i = 0; i<MAX_X; i++)
			vpath[i] = new FlowPath[MAX_Y];
	}
	else{
		for (i = 0; i<MAX_X; i++)
		for (j = 0; j<MAX_Y; j++)
			vpath[i][j].Init();
	}

	int n;
	FlowPath tmp;
	int N = 1000;
	tmp.Alpha = new V3DF[N + 1];
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			// 1. 걸러내기(not coherent line OR zero etf)
			if (imCL[i][j] != 0.0f || is_zero_vector(etf[i][j])){
				vpath[i][j].sn = 0;		vpath[i][j].tn = 0;
				continue;
			}

			tmp.InitShallow();

			// 2. 임시저장 공간에 점들 넣기 & 개수 세기 (S 방향)
			tmp.sn = N;
			SetFlowAtPointS4Vectorization(i, j, &(tmp.sn), tmp.Alpha);	// flow 따르다가 coherent line이 아니면 멈춘다

			// 3. 메모리 할당 및 복사 (S 방향)
			n = vpath[i][j].sn = tmp.sn;
			if (n != 0){
				if (vpath[i][j].Alpha)	delete[] vpath[i][j].Alpha;
				vpath[i][j].Alpha = new V3DF[n];
				for (k = 0; k<n; k++)
					vcopy(vpath[i][j].Alpha[k], tmp.Alpha[k]);
			}
		}
	}
}

void Direction::SetCoherentLine()
{
	//printf("SetCoherentLine..");
	int i, j, k;

	if (oldim == NULL){
		oldim = new float*[MAX_X];
		for (int i = 0; i<MAX_X; i++){
			oldim[i] = new float[MAX_Y];
		}
		for (int i = 0; i<MAX_X; i++){
			for (int j = 0; j<MAX_Y; j++){
				oldim[i][j] = im[i][j];
			}
		}
	}

	// For Hg
	int MaskSize = threshold_T;
	float *Mc = new float[MaskSize];
	float *Ms = new float[MaskSize];
	float *DogMask = new float[MaskSize];
	float sigmaS = SigmaC*1.6f;
	// Dog mask;	f(t) = G(sigma_c)(t) - P*G(sigma_s)(t)
	BuildGaussianMask(MaskSize, SigmaC, Mc);	//G(sigma_c)(t)
	BuildGaussianMask(MaskSize, sigmaS, Ms);	//G(sigma_s)(t)
	ScalarBuf(Ms, P, MaskSize);	//P*G(sigma_s)(t)
	DifferenceBuf(DogMask, Mc, Ms, MaskSize);	//f(t)
	float px, py, intensity;
	float Hg, He;
	float **clhg = new float*[MAX_X];
	float **clhe = new float*[MAX_X];
	for (i = 0; i<MAX_X; i++){
		clhg[i] = new float[MAX_Y];
		clhe[i] = new float[MAX_Y];
	}

	// For He
	//MaskSize = this->threshold_S;
	//float *GaussianMask = new float[MaskSize];
	//BuildGaussianMask(MaskSize, SigmaM, GaussianMask);

	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			clhg[i][j] = Hg = 0.0f;

			if (is_zero_vector(etf[i][j])){
				continue;
			}

			// 1. Hg
			if (fpath[i][j].tn < threshold_T){
				for (k = 0; k<fpath[i][j].tn; k++){
					px = fpath[i][j].Beta[k][0];	py = fpath[i][j].Beta[k][1];
					if (px<0 || px >= MAX_X || py<0 || py >= MAX_Y)	continue;
					GetValAtPoint(oldim, MAX_X, MAX_Y, px, py, &intensity);
					Hg += (intensity*DogMask[k]);
				}
			}
			else{
				for (k = 0; k<threshold_T; k++){
					px = fpath[i][j].Beta[k][0];	py = fpath[i][j].Beta[k][1];
					if (px<0 || px >= MAX_X || py<0 || py >= MAX_Y)	continue;
					GetValAtPoint(oldim, MAX_X, MAX_Y, px, py, &intensity);
					Hg += (intensity*DogMask[k]);
				}
			}
			clhg[i][j] = Hg;
		}
	}

	float s, div, div2;
	div = sqrt(2 * PI)*SigmaM;
	div2 = 2 * SigmaM*SigmaM;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			clhe[i][j] = 0.0f;

			// S passing (Obama image 51.01 sec -> 12.89 sec)
			if (is_zero_vector(etf[i][j])){
				imCL[i][j] = 1.0f;
				continue;
			}

			// 2. He
			//|		He(x) = (-S~+S) G(s) Hg(cx(s)) ds
			//|	모든 T에 대해 밝기xDog filter
			He = 0.0f;
			for (k = 0; k<fpath[i][j].sn; k++){
				px = fpath[i][j].Alpha[k][0];	py = fpath[i][j].Alpha[k][1];
				if (px<0 || px >= MAX_X || py<0 || py >= MAX_Y)	continue;
				GetValAtPoint(clhg, MAX_X, MAX_Y, px, py, &Hg);

				//He += (GaussianMask[k]*Hg);
				s = sqrt((i - px)*(i - px) + (j - py)*(j - py));	// (i,j)~(px,py)
				He += ((exp(-(s*s) / div2) / div)*Hg);
			}

			// 3. set line(0 or 1)
			if (He<0 && 1.0f + tanh(He)<cl_tanh_he_thr)	// 0.997f or 1.0f
				//if ( 1.0f+tanh(He)<srcCL_tanh_he_thr )	// 0.997f or 1.0f
				imCL[i][j] = 0.0f;
			else
				imCL[i][j] = 1.0f;

			// 4. set old im -> line으로(반복위해)
			if (imCL[i][j] == 0.0f)
				oldim[i][j] = 0.0f;

			clhe[i][j] = He;
		}
	}

	delete[] Mc;		delete[] Ms;
	delete[] DogMask;
	for (i = 0; i<MAX_X; i++)	delete[] clhg[i];	delete[] clhg;
	for (i = 0; i<MAX_X; i++)	delete[] clhe[i];	delete[] clhe;
	//printf("done\n");
}

void Direction::SetFlowPath(){
	// etf <- tangent 초기화
	init_buf(etf, tangent, MAX_X, MAX_Y);
	GetETF();	GetETF();

	//int i, j, k;
	int i, j;

	if (fpath == NULL){
		fpath = new FlowPath *[MAX_X];
		for (i = 0; i<MAX_X; i++){
			fpath[i] = new FlowPath[MAX_Y];
		}
	}
	else{
		for (i = 0; i<MAX_X; i++)
		for (j = 0; j<MAX_Y; j++)
			fpath[i][j].Init();
	}

	V3DF zerov = { 0.0f, 0.0f, 0.0f };
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			//if ( is_zero_vector(etf[i][j]) ){
			if (is_similar_vector(etf[i][j], zerov, 0.000001f)){
				fpath[i][j].sn = fpath[i][j].tn = 0;
				continue;
			}

			fpath[i][j].sn = threshold_S;
			if (fpath[i][j].Alpha)	delete[] fpath[i][j].Alpha;
			fpath[i][j].Alpha = new V3DF[threshold_S];
			SetFlowAtPointS(i, j, &(fpath[i][j].sn), fpath[i][j].Alpha);

			if (fpath[i][j].Beta)		delete[] fpath[i][j].Beta;
			fpath[i][j].Beta = new V3DF[threshold_T];
			fpath[i][j].tn = threshold_T;
			SetFlowAtPointT(i, j, &(fpath[i][j].tn), fpath[i][j].Beta);
		}
	}
}

void Direction::GetAvg(V3DF **flow)
{
	int i, j, a, b;
	int nbhd = 5;
	V3DI xvec, yvec;
	V3DF tcur, tsum;
	float w;
	float r = (float)nbhd;

	V3DF **oldetf = new V3DF *[MAX_X];
	for (i = 0; i<MAX_X; i++){
		oldetf[i] = new V3DF[MAX_Y];
		for (j = 0; j<MAX_Y; j++)
			vcopy(oldetf[i][j], flow[i][j]);	//old etf 초기화
	}

	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			vectori(xvec, i, j, 0);
			vzero(tsum);
			for (a = -nbhd; a <= nbhd; a++){
				for (b = -nbhd; b <= nbhd; b++){
					vectori(yvec, i + a, j + b, 0);

					// 경계처리
					if (yvec[0]<0) yvec[0] *= (-1.0f);
					else if (yvec[0] >= MAX_X)	yvec[0] = MAX_X - (yvec[0] - (MAX_X - 1));
					if (yvec[1]<0) yvec[1] *= (-1.0f);
					else if (yvec[1] >= MAX_Y)	yvec[1] = MAX_Y - (yvec[1] - (MAX_Y - 1));

					//if (grad[yvec[0]][yvec[1]][2] == 0.0f)	continue;

					//1. w_s(x,y) = 0, if |xvec-yvec| >= r
					//if ( pdist2(xvec,yvec) >= r)
					if (pdist2(xvec, yvec) > r)
						continue;

					//2. w_m = 0.5 (1 + tanh[(g(y) - g(x))])
					//w = 0.5f * (1.0f + (grad[yvec[0]][yvec[1]][2] - grad[xvec[0]][xvec[1]][2]));

					//3. w_d = | etf(x) DOT etf(y) |
					//w *= fabs( vdot( oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]] ) );

					//4. phi
					//w *= (vdot ( oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]] ) > 0.0f) ? 1.0f : -1.0f;
					w = (vdot(oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]]) > 0.0f) ? 1.0f : -1.0f;

					//5. t_cur(y)
					vector3(tcur, w*oldetf[yvec[0]][yvec[1]][0], w*oldetf[yvec[0]][yvec[1]][1], w*oldetf[yvec[0]][yvec[1]][2]);

					vsum(tsum, tcur);
				}
			}
			//normalizing tsum
			vnorm(tsum);
			vcopy(flow[i][j], tsum);
		}
	}
	for (i = 0; i<MAX_X; i++)
		delete[] oldetf[i];
	delete[] oldetf;
}

void Direction::GetAvg(float **flow)
{
	int i, j, a, b;
	int nbhd = 5;
	V3DI xvec, yvec;
	float tcur, tsum;
	float w;
	float r = (float)nbhd;

	float **oldetf = new float *[MAX_X];
	for (i = 0; i<MAX_X; i++){
		oldetf[i] = new float[MAX_Y];
		for (j = 0; j<MAX_Y; j++)
			oldetf[i][j] = flow[i][j];	//old etf 초기화
	}

	int cnt;
	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			w = 1.0f;	cnt = 0;
			vectori(xvec, i, j, 0);
			tsum = 0.0f;
			for (a = -nbhd; a <= nbhd; a++){
				for (b = -nbhd; b <= nbhd; b++){
					vectori(yvec, i + a, j + b, 0);

					// 경계처리
					if (yvec[0]<0) yvec[0] *= (-1.0f);
					else if (yvec[0] >= MAX_X)	yvec[0] = MAX_X - (yvec[0] - (MAX_X - 1));
					if (yvec[1]<0) yvec[1] *= (-1.0f);
					else if (yvec[1] >= MAX_Y)	yvec[1] = MAX_Y - (yvec[1] - (MAX_Y - 1));

					//if (grad[yvec[0]][yvec[1]][2] == 0.0f)	continue;

					//1. w_s(x,y) = 0, if |xvec-yvec| >= r
					//if ( pdist2(xvec,yvec) >= r)
					if (pdist2(xvec, yvec) > r)
						continue;

					//2. w_m = 0.5 (1 + tanh[(g(y) - g(x))])
					//w = 0.5f * (1.0f + (grad[yvec[0]][yvec[1]][2] - grad[xvec[0]][xvec[1]][2]));

					//3. w_d = | etf(x) DOT etf(y) |
					//w *= fabs( vdot( oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]] ) );

					//4. phi
					//w *= (vdot ( oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]] ) > 0.0f) ? 1.0f : -1.0f;
					//w = (vdot ( oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]] ) > 0.0f) ? 1.0f : -1.0f;

					//5. t_cur(y)
					//vector(tcur, w*oldetf[yvec[0]][yvec[1]][0], w*oldetf[yvec[0]][yvec[1]][1], w*oldetf[yvec[0]][yvec[1]][2] );
					tcur = oldetf[yvec[0]][yvec[1]];

					//vsum(tsum, tcur);
					tsum += tcur;
					cnt++;
				}
			}
			//normalizing tsum
			//vnorm(tsum);
			tsum /= (float)cnt;
			flow[i][j] = tsum;
		}
	}
	for (i = 0; i<MAX_X; i++)
		delete[] oldetf[i];
	delete[] oldetf;
}

void Direction::GetGradient(int MaskSize, float **img, float **ang){
	if (MaskSize % 2 == 0 || MaskSize>9){
		printf("GetGradient(): 마스크 사이즈는 홀수여야 합니다.\n");
		printf("GetGradient(): 마스크 사이즈는 9이하여야 합니다.\n");
		exit(0);
	}
	int cnt = 0;
	int row, col;
	int colOffset, rowOffset;
	int colTotal, rowTotal;
	//float GxMask[3][3];				// Sobel mask in the x direction
	//float GyMask[3][3];				// Sobel mask in the y direction
	float **GxMask;
	float **GyMask;
	float Gx, Gy;	// Sum of Sobel mask products values in the x,y direction
	int itv = MaskSize / 2;

	/* Declare Sobel masks */
	//GxMask[0][2] = -1.0f; GxMask[1][2] = 0.0f; GxMask[2][2] = 1.0f;
	//GxMask[0][1] = -2.0f; GxMask[1][1] = 0.0f; GxMask[2][1] = 2.0f;
	//GxMask[0][0] = -1.0f; GxMask[1][0] = 0.0f; GxMask[2][0] = 1.0f;

	//GyMask[0][2] =  1.0f; GyMask[1][2] =  2.0f; GyMask[2][2] =  1.0f;
	//GyMask[0][1] =  0.0f; GyMask[1][1] =  0.0f; GyMask[2][1] =  0.0f;
	//GyMask[0][0] = -1.0f; GyMask[1][0] = -2.0f; GyMask[2][0] = -1.0f;
	int i;
	GxMask = new float *[MaskSize];
	GyMask = new float *[MaskSize];
	for (i = 0; i<MaskSize; i++){
		GxMask[i] = new float[MaskSize];
		GyMask[i] = new float[MaskSize];
	}
	switch (MaskSize){
	case 3:
		GxMask[0][2] = -1.0f; GxMask[1][2] = 0.0f; GxMask[2][2] = 1.0f;
		GxMask[0][1] = -2.0f; GxMask[1][1] = 0.0f; GxMask[2][1] = 2.0f;
		GxMask[0][0] = -1.0f; GxMask[1][0] = 0.0f; GxMask[2][0] = 1.0f;

		GyMask[0][2] = 1.0f; GyMask[1][2] = 2.0f; GyMask[2][2] = 1.0f;
		GyMask[0][1] = 0.0f; GyMask[1][1] = 0.0f; GyMask[2][1] = 0.0f;
		GyMask[0][0] = -1.0f; GyMask[1][0] = -2.0f; GyMask[2][0] = -1.0f;
		break;
	case 5:
		GxMask[0][4] = -2.0f;	GxMask[1][4] = -1.0f;	GxMask[2][4] = 0.0f;	GxMask[3][4] = 1.0f;	GxMask[4][4] = 2.0f;
		GxMask[0][3] = -3.0f;	GxMask[1][3] = -2.0f;	GxMask[2][3] = 0.0f;	GxMask[3][3] = 2.0f;	GxMask[4][3] = 3.0f;
		GxMask[0][2] = -4.0f;	GxMask[1][2] = -3.0f;	GxMask[2][2] = 0.0f;	GxMask[3][2] = 3.0f;	GxMask[4][2] = 4.0f;
		GxMask[0][1] = -3.0f;	GxMask[1][1] = -2.0f;	GxMask[2][1] = 0.0f;	GxMask[3][1] = 2.0f;	GxMask[4][1] = 3.0f;
		GxMask[0][0] = -2.0f;	GxMask[1][0] = -1.0f;	GxMask[2][0] = 0.0f;	GxMask[3][0] = 1.0f;	GxMask[4][0] = 2.0f;

		GyMask[0][4] = 2.0f;	GyMask[1][4] = 3.0f;	GyMask[2][4] = 4.0f;	GyMask[3][4] = 3.0f;	GyMask[4][4] = 2.0f;
		GyMask[0][3] = 1.0f;	GyMask[1][3] = 2.0f;	GyMask[2][3] = 3.0f;	GyMask[3][3] = 2.0f;	GyMask[4][3] = 1.0f;
		GyMask[0][2] = 0.0f;	GyMask[1][2] = 0.0f;	GyMask[2][2] = 0.0f;	GyMask[3][2] = 0.0f;	GyMask[4][2] = 0.0f;
		GyMask[0][1] = -1.0f;	GyMask[1][1] = -2.0f;	GyMask[2][1] = -3.0f;	GyMask[3][1] = -2.0f;	GyMask[4][1] = -1.0f;
		GyMask[0][0] = -2.0f;	GyMask[1][0] = -3.0f;	GyMask[2][0] = -4.0f;	GyMask[3][0] = -3.0f;	GyMask[4][0] = -2.0f;
		break;
	case 7:
		GxMask[0][6] = -3.0f;	GxMask[1][6] = -2.0f;	GxMask[2][6] = -1.0f;	GxMask[3][6] = 0.0f;	GxMask[4][6] = 1.0f;	GxMask[5][6] = 2.0f;	GxMask[6][6] = 3.0f;
		GxMask[0][5] = -4.0f;	GxMask[1][5] = -3.0f;	GxMask[2][5] = -2.0f;	GxMask[3][5] = 0.0f;	GxMask[4][5] = 2.0f;	GxMask[5][5] = 3.0f;	GxMask[6][5] = 4.0f;
		GxMask[0][4] = -5.0f;	GxMask[1][4] = -4.0f;	GxMask[2][4] = -3.0f;	GxMask[3][4] = 0.0f;	GxMask[4][4] = 3.0f;	GxMask[5][4] = 4.0f;	GxMask[6][4] = 5.0f;
		GxMask[0][3] = -6.0f;	GxMask[1][3] = -5.0f;	GxMask[2][3] = -4.0f;	GxMask[3][3] = 0.0f;	GxMask[4][3] = 4.0f;	GxMask[5][3] = 5.0f;	GxMask[6][3] = 6.0f;
		GxMask[0][2] = -5.0f;	GxMask[1][2] = -4.0f;	GxMask[2][2] = -3.0f;	GxMask[3][2] = 0.0f;	GxMask[4][2] = 3.0f;	GxMask[5][2] = 4.0f;	GxMask[6][2] = 5.0f;
		GxMask[0][1] = -4.0f;	GxMask[1][1] = -3.0f;	GxMask[2][1] = -2.0f;	GxMask[3][1] = 0.0f;	GxMask[4][1] = 2.0f;	GxMask[5][1] = 3.0f;	GxMask[6][1] = 4.0f;
		GxMask[0][0] = -3.0f;	GxMask[1][0] = -2.0f;	GxMask[2][0] = -1.0f;	GxMask[3][0] = 0.0f;	GxMask[4][0] = 1.0f;	GxMask[5][0] = 2.0f;	GxMask[6][0] = 3.0f;

		GyMask[0][6] = 3.0f;	GyMask[1][6] = 4.0f;	GyMask[2][6] = 5.0f;	GyMask[3][6] = 6.0f;	GyMask[4][6] = 5.0f;	GyMask[5][6] = 4.0f;	GyMask[6][6] = 3.0f;
		GyMask[0][5] = 2.0f;	GyMask[1][5] = 3.0f;	GyMask[2][5] = 4.0f;	GyMask[3][5] = 5.0f;	GyMask[4][5] = 4.0f;	GyMask[5][5] = 3.0f;	GyMask[6][5] = 2.0f;
		GyMask[0][4] = 1.0f;	GyMask[1][4] = 2.0f;	GyMask[2][4] = 3.0f;	GyMask[3][4] = 4.0f;	GyMask[4][4] = 3.0f;	GyMask[5][4] = 2.0f;	GyMask[6][4] = 1.0f;
		GyMask[0][3] = 0.0f;	GyMask[1][3] = 0.0f;	GyMask[2][3] = 0.0f;	GyMask[3][3] = 0.0f;	GyMask[4][3] = 0.0f;	GyMask[5][3] = 0.0f;	GyMask[6][3] = 0.0f;
		GyMask[0][2] = -1.0f;	GyMask[1][2] = -2.0f;	GyMask[2][2] = -3.0f;	GyMask[3][2] = -4.0f;	GyMask[4][2] = -3.0f;	GyMask[5][2] = -2.0f;	GyMask[6][2] = -1.0f;
		GyMask[0][1] = -2.0f;	GyMask[1][1] = -3.0f;	GyMask[2][1] = -4.0f;	GyMask[3][1] = -5.0f;	GyMask[4][1] = -4.0f;	GyMask[5][1] = -3.0f;	GyMask[6][1] = -2.0f;
		GyMask[0][0] = -3.0f;	GyMask[1][0] = -4.0f;	GyMask[2][0] = -5.0f;	GyMask[3][0] = -6.0f;	GyMask[4][0] = -5.0f;	GyMask[5][0] = -4.0f;	GyMask[6][0] = -3.0f;
		break;
	case 9:
		GxMask[0][8] = -4.0f;	GxMask[1][8] = -3.0f;	GxMask[2][8] = -2.0f;	GxMask[3][8] = -1.0f;	GxMask[4][8] = 0.0f;	GxMask[5][8] = 1.0f;	GxMask[6][8] = 2.0f;	GxMask[7][8] = 3.0f;	GxMask[8][8] = 4.0f;
		GxMask[0][7] = -5.0f;	GxMask[1][7] = -4.0f;	GxMask[2][7] = -3.0f;	GxMask[3][7] = -2.0f;	GxMask[4][7] = 0.0f;	GxMask[5][7] = 2.0f;	GxMask[6][7] = 3.0f;	GxMask[7][7] = 4.0f;	GxMask[8][7] = 5.0f;
		GxMask[0][6] = -6.0f;	GxMask[1][6] = -5.0f;	GxMask[2][6] = -4.0f;	GxMask[3][6] = -3.0f;	GxMask[4][6] = 0.0f;	GxMask[5][6] = 3.0f;	GxMask[6][6] = 4.0f;	GxMask[7][6] = 5.0f;	GxMask[8][6] = 6.0f;
		GxMask[0][5] = -7.0f;	GxMask[1][5] = -6.0f;	GxMask[2][5] = -5.0f;	GxMask[3][5] = -4.0f;	GxMask[4][5] = 0.0f;	GxMask[5][5] = 4.0f;	GxMask[6][5] = 5.0f;	GxMask[7][5] = 6.0f;	GxMask[8][5] = 7.0f;
		GxMask[0][4] = -8.0f;	GxMask[1][4] = -7.0f;	GxMask[2][4] = -6.0f;	GxMask[3][4] = -5.0f;	GxMask[4][4] = 0.0f;	GxMask[5][4] = 5.0f;	GxMask[6][4] = 6.0f;	GxMask[7][4] = 7.0f;	GxMask[8][4] = 8.0f;
		GxMask[0][3] = -7.0f;	GxMask[1][3] = -6.0f;	GxMask[2][3] = -5.0f;	GxMask[3][3] = -4.0f;	GxMask[4][3] = 0.0f;	GxMask[5][3] = 4.0f;	GxMask[6][3] = 5.0f;	GxMask[7][3] = 6.0f;	GxMask[8][3] = 7.0f;
		GxMask[0][2] = -6.0f;	GxMask[1][2] = -5.0f;	GxMask[2][2] = -4.0f;	GxMask[3][2] = -3.0f;	GxMask[4][2] = 0.0f;	GxMask[5][2] = 3.0f;	GxMask[6][2] = 4.0f;	GxMask[7][2] = 5.0f;	GxMask[8][2] = 6.0f;
		GxMask[0][1] = -5.0f;	GxMask[1][1] = -4.0f;	GxMask[2][1] = -3.0f;	GxMask[3][1] = -2.0f;	GxMask[4][1] = 0.0f;	GxMask[5][1] = 2.0f;	GxMask[6][1] = 3.0f;	GxMask[7][1] = 4.0f;	GxMask[8][1] = 5.0f;
		GxMask[0][0] = -4.0f;	GxMask[1][0] = -3.0f;	GxMask[2][0] = -2.0f;	GxMask[3][0] = -1.0f;	GxMask[4][0] = 0.0f;	GxMask[5][0] = 1.0f;	GxMask[6][0] = 2.0f;	GxMask[7][0] = 3.0f;	GxMask[8][0] = 4.0f;

		GyMask[0][8] = 4.0f;	GyMask[1][8] = 5.0f;	GyMask[2][8] = 6.0f;	GyMask[3][8] = 7.0f;	GyMask[4][8] = 8.0f;	GyMask[5][8] = 7.0f;	GyMask[6][8] = 6.0f;	GyMask[7][8] = 5.0f;	GyMask[8][8] = 4.0f;
		GyMask[0][7] = 3.0f;	GyMask[1][7] = 4.0f;	GyMask[2][7] = 5.0f;	GyMask[3][7] = 6.0f;	GyMask[4][7] = 7.0f;	GyMask[5][7] = 6.0f;	GyMask[6][7] = 5.0f;	GyMask[7][7] = 4.0f;	GyMask[8][7] = 3.0f;
		GyMask[0][6] = 2.0f;	GyMask[1][6] = 3.0f;	GyMask[2][6] = 4.0f;	GyMask[3][6] = 5.0f;	GyMask[4][6] = 6.0f;	GyMask[5][6] = 5.0f;	GyMask[6][6] = 4.0f;	GyMask[7][6] = 3.0f;	GyMask[8][6] = 2.0f;
		GyMask[0][5] = 1.0f;	GyMask[1][5] = 2.0f;	GyMask[2][5] = 3.0f;	GyMask[3][5] = 4.0f;	GyMask[4][5] = 5.0f;	GyMask[5][5] = 4.0f;	GyMask[6][5] = 3.0f;	GyMask[7][5] = 2.0f;	GyMask[8][5] = 1.0f;
		GyMask[0][4] = 0.0f;	GyMask[1][4] = 0.0f;	GyMask[2][4] = 0.0f;	GyMask[3][4] = 0.0f;	GyMask[4][4] = 0.0f;	GyMask[5][4] = 0.0f;	GyMask[6][4] = 0.0f;	GyMask[7][4] = 0.0f;	GyMask[8][4] = 0.0f;
		GyMask[0][3] = -1.0f;	GyMask[1][3] = -2.0f;	GyMask[2][3] = -3.0f;	GyMask[3][3] = -4.0f;	GyMask[4][3] = -5.0f;	GyMask[5][3] = -4.0f;	GyMask[6][3] = -3.0f;	GyMask[7][3] = -2.0f;	GyMask[8][3] = -1.0f;
		GyMask[0][2] = -2.0f;	GyMask[1][2] = -3.0f;	GyMask[2][2] = -4.0f;	GyMask[3][2] = -5.0f;	GyMask[4][2] = -6.0f;	GyMask[5][2] = -5.0f;	GyMask[6][2] = -4.0f;	GyMask[7][2] = -3.0f;	GyMask[8][2] = -2.0f;
		GyMask[0][1] = -3.0f;	GyMask[1][1] = -4.0f;	GyMask[2][1] = -5.0f;	GyMask[3][1] = -6.0f;	GyMask[4][1] = -7.0f;	GyMask[5][1] = -6.0f;	GyMask[6][1] = -5.0f;	GyMask[7][1] = -4.0f;	GyMask[8][1] = -3.0f;
		GyMask[0][0] = -4.0f;	GyMask[1][0] = -5.0f;	GyMask[2][0] = -6.0f;	GyMask[3][0] = -7.0f;	GyMask[4][0] = -8.0f;	GyMask[5][0] = -7.0f;	GyMask[6][0] = -6.0f;	GyMask[7][0] = -5.0f;	GyMask[8][0] = -4.0f;
		break;
	};

	V3DF vct;
	/* Determine edge directions and gradient strengths */
	for (col = 0; col<MAX_X; col++){	//col
		for (row = 0; row<MAX_Y; row++){	//row
			vzero(vct);
			Gx = 0.0f;		Gy = 0.0f;
			/* Calculate the sum of the Sobel mask times the nine surrounding pixels in the x and y direction */
			for (colOffset = -itv; colOffset <= itv; colOffset++) {
				for (rowOffset = -itv; rowOffset <= itv; rowOffset++) {
					colTotal = col + colOffset;
					rowTotal = row + rowOffset;
					//경계처리(대칭)
					if (rowTotal<0) rowTotal *= (-1.0f);
					else if (rowTotal >= MAX_Y)	rowTotal = MAX_Y - (rowTotal - (MAX_Y - 1));
					if (colTotal<0) colTotal *= (-1.0f);
					else if (colTotal >= MAX_X)	colTotal = MAX_X - (colTotal - (MAX_X - 1));

					Gx = Gx + (img[colTotal][rowTotal] * GxMask[colOffset + itv][rowOffset + itv]);//??
					Gy = Gy + (img[colTotal][rowTotal] * GyMask[colOffset + itv][rowOffset + itv]);//??
				}
			}
			//grad[col][row][0] = Gx;
			//grad[col][row][1] = Gy;
			//grad[col][row][2] = sqrt(Gx*Gx + Gy*Gy);
			vct[0] = Gx;
			vct[1] = Gy;
			vct[2] = 0.0f;
			Vector2Ang(vct, &ang[col][row]);
		}
	}

	for (i = 0; i<MaskSize; i++){
		delete[] GxMask[i];	delete[] GyMask[i];
	}
	delete[] GxMask;	delete[] GyMask;
}

void Direction::GetETF(int nbhd)
{
	int i, j, a, b;
	//int nbhd = 5;
	V3DI xvec, yvec;
	V3DF tcur, tsum;
	float w;
	float r = (float)nbhd;

	V3DF **oldetf = new V3DF *[MAX_X];
	for (i = 0; i<MAX_X; i++){
		oldetf[i] = new V3DF[MAX_Y];
		for (j = 0; j<MAX_Y; j++)
			vcopy(oldetf[i][j], etf[i][j]);	//old etf 초기화
	}

	for (i = 0; i<MAX_X; i++){
		for (j = 0; j<MAX_Y; j++){
			if (grad[i][j][2] == 0.0f){
				vzero(etf[i][j]);
				continue;
			}

			vectori(xvec, i, j, 0);
			vzero(tsum);
			for (a = -nbhd; a <= nbhd; a++){
				for (b = -nbhd; b <= nbhd; b++){
					vectori(yvec, i + a, j + b, 0);

					// 경계처리
					if (yvec[0]<0) yvec[0] *= (-1.0f);
					else if (yvec[0] >= MAX_X)	yvec[0] = MAX_X - (yvec[0] - (MAX_X - 1));
					if (yvec[1]<0) yvec[1] *= (-1.0f);
					else if (yvec[1] >= MAX_Y)	yvec[1] = MAX_Y - (yvec[1] - (MAX_Y - 1));

					if (grad[yvec[0]][yvec[1]][2] == 0.0f)	continue;

					//1. w_s(x,y) = 0, if |xvec-yvec| >= r
					//if ( pdist2(xvec,yvec) >= r)
					if (pdist2(xvec, yvec) > r)
						continue;

					//2. w_m = 0.5 (1 + tanh[(g(y) - g(x))])
					w = 0.5f * (1.0f + (grad[yvec[0]][yvec[1]][2] - grad[xvec[0]][xvec[1]][2]));

					//3. w_d = | etf(x) DOT etf(y) |
					w *= fabs(vdot(oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]]));

					//4. phi
					w *= (vdot(oldetf[xvec[0]][xvec[1]], oldetf[yvec[0]][yvec[1]]) > 0.0f) ? 1.0f : -1.0f;

					//5. t_cur(y)
					vector3(tcur, w*oldetf[yvec[0]][yvec[1]][0], w*oldetf[yvec[0]][yvec[1]][1], w*oldetf[yvec[0]][yvec[1]][2]);

					vsum(tsum, tcur);
				}
			}
			//normalizing tsum
			vnorm(tsum);
			vcopy(etf[i][j], tsum);
		}
	}
	for (i = 0; i<MAX_X; i++)		delete[] oldetf[i];	delete[] oldetf;
}

void Direction::SetFlowAtPointS(int px, int py, int *nPoints, V3DF *Alpha){
	float x, y, x_, y_;	//첫점, 후점
	V3DF etf_/*,etf__/*전etf*/;
	int nN, nP, i;
	int init_n = (*nPoints);
	int my_n = 2;
	V3DF **alpha = new V3DF*[my_n];
	for (i = 0; i<my_n; i++)
		alpha[i] = new V3DF[init_n / 2 + 1];

	nP = nN = 0;
	x = px;	y = py;

	float angle;
	int threshold_Angle = 15.0f;
	int threshold_Angle2 = 135.0f;
	V3DF etf__;	vcopy(etf__, etf[px][py]);

	float sqrt2 = sqrt(2.0f);	//sqrt(2)만큼 가자.
	//-S
	while (nN<init_n / 2){
		if (x<0 || x >= MAX_X || y<0 || y >= MAX_Y)	break;	//image 밖

		//1. 해당 점에서 etf
		GetETFAtPoint(x, y, etf_);
		//2. normalize
		vnorm(etf_);
		if (is_zero_vector(etf_))	break;

		angle = angle_r(etf_, etf__)*180.0f / PI;
		if (angle > threshold_Angle2){
			vnegate(etf_);
		}
		if (angle > threshold_Angle)	//연속한 etf가 이루는 각이 임계치 이상이면
			break;

		x_ = x - etf_[0];		y_ = y - etf_[1];
		if (x == x_ && y == y_)	break;	// 무한루프 방지
		if (((int)x != (int)x_) || ((int)y != (int)y_))	// 너무 자잘하게 하지 않기 위해
			vector3(alpha[NEGATIVE][nN++], x_, y_, 0.0f);
		x = x_;	y = y_;

		vcopy(etf__, etf_);
	}

	//+S
	x = px;	y = py;
	vcopy(etf__, etf[px][py]);
	while (nP<init_n / 2){
		if (x<0 || x >= MAX_X || y<0 || y >= MAX_Y)	break;	//image 밖

		//1. 해당 점에서 etf
		GetETFAtPoint(x, y, etf_);
		//2. normalize
		vnorm(etf_);
		if (is_zero_vector(etf_))	break;

		angle = angle_r(etf_, etf__)*180.0f / PI;
		if (angle > threshold_Angle2){
			vnegate(etf_);
		}
		if (angle > threshold_Angle)	//연속한 etf가 이루는 각이 임계치 이상이면
			break;

		x_ = x + etf_[0];		y_ = y + etf_[1];
		if (x == x_ && y == y_)	break;	// 무한루프 방지
		if (((int)x != (int)x_) || ((int)y != (int)y_))	// 너무 자잘하게 하지 않기 위해
			vector3(alpha[POSITIVE][nP++], x_, y_, 0.0f);
		x = x_;	y = y_;

		vcopy(etf__, etf_);
	}
	(*nPoints) = nN + nP + 1;
	if ((*nPoints) < 10){
		(*nPoints) = 0;
		for (i = 0; i<2; i++)		delete[] alpha[i];	delete[] alpha;
		return;
	}

	//최종 alpha(2D) -> Alpha(1D)(-S ~ +S)
	for (i = 0; i<init_n; i++)	vzero(Alpha[i]);	//0. 초기화
	for (i = 0; i<nN; i++)
		vcopy(Alpha[i], alpha[NEGATIVE][nN - 1 - i]);	//1. negative 값
	vector3(Alpha[i], px, py, 0.0f);	//2. 중심값
	int n = nN + 1;	//지금까지 정의된 Alpha 개수
	for (i = 0; i<nP; i++)
		vcopy(Alpha[n + i], alpha[POSITIVE][i]);	//3. positive 값

	//for (i = 0; i<my_n; i++)		delete[] alpha[i];	//힙손상으로 인해 주석처리함
	delete[] alpha;
}

void Direction::SetFlowAtPointT(int px, int py, int *nPoints, V3DF *Beta){
	//gradient 방향의 선분 찾기
	float x, y, x_, y_;	//첫점, 후점
	V3DF grad_;
	int nN, nP, i;
	int init_n = (*nPoints);
	V3DF **beta = new V3DF*[2];
	for (i = 0; i<2; i++)
		beta[i] = new V3DF[init_n];

	nP = nN = 0;
	x = px;	y = py;
	//vector3(beta[NEGATIVE][(*nN)++],x,y,0.0f);
	//vector3(beta[POSITIVE][(*nP)++],x,y,0.0f);
	vcopy(grad_, grad[px][py]);
	vnorm(grad_);	//normalize

	if (is_zero_vector(grad_)){
		(*nPoints) = 1;
		vector3(Beta[0], px, py, 0.0f);
		for (i = 0; i<2; i++)
			delete[] beta[i];
		delete[] beta;
		return;
	}

	//-T
	while (nN < (init_n / 2)){
		if (x<0 || x >= MAX_X || y<0 || y >= MAX_Y)	break;	//image 밖
		//if ( sg.Li[px][py] != sg.Li[(int)x][(int)y] )	break;	//시작라벨과다르면
		//GetGradientAtPoint(x,y,grad_);
		//if ( vuangle(etf_,etf__)*180.0f/PI > threshold_Angle )	//연속한etf가이루는각이임계치이상이면
		//break;

		x_ = x - grad_[0];
		y_ = y - grad_[1];
		vector3(beta[NEGATIVE][nN++], x_, y_, grad_[2]/*크기*/);
		x = x_;	y = y_;
	}

	//+T
	x = px;	y = py;
	while (nP < (init_n / 2)){
		if (x<0 || x >= MAX_X || y<0 || y >= MAX_Y)	break;	//image 밖
		//if ( sg.Li[px][py] != sg.Li[(int)x][(int)y] )	break;	//시작라벨과다르면
		//GetGradientAtPoint(x,y,grad_);
		//if ( vuangle(etf_,etf__)*180.0f/PI > threshold_Angle )	//연속한etf가이루는각이임계치이상이면
		//break;

		x_ = x + grad_[0];
		y_ = y + grad_[1];
		vector3(beta[POSITIVE][nP++], x_, y_, grad_[2]/*크기*/);
		x = x_;	y = y_;
	}

	//최종 beta(2D) -> Beta(1D)(-T ~ +T)
	for (i = 0; i<init_n; i++)	vzero(Beta[i]);	//0. 초기화
	for (i = 0; i<nN; i++)	vcopy(Beta[i], beta[NEGATIVE][nN - 1 - i]);		//1. negative 값
	vector3(Beta[i], px, py, 0.0f);	//2. 중심값
	int n = nN + 1;	//지금까지 정의된 Beta 개수
	for (i = 0; i<nP; i++)	vcopy(Beta[n + i], beta[POSITIVE][i]);	//3. positive 값
	(*nPoints) = nN + nP + 1;

	//for (i = 0; i<2; i++)			// 외부 참조로 인해 delete시 힙손상이 일어나 프로그램이 중단되어서 주석처리
	//delete[] beta[i];
	delete[] beta;
}

void Direction::SetFlowAtPointS4Vectorization(int px, int py, int *nPoints, V3DF *Alpha){
	// flow 따르다가 coherent line이 아니면 멈춘다
	float x, y, x_, y_;	//첫점, 후점
	V3DF etf_/*,etf__/*전etf*/;
	int nN, nP, i;
	int init_n = (*nPoints);
	V3DF **alpha = new V3DF*[2];
	for (i = 0; i<2; i++)
		alpha[i] = new V3DF[init_n];

	nP = nN = 0;
	x = px;	y = py;

	float angle;
	int threshold_Angle = 15.0f;
	int threshold_Angle2 = 135.0f;
	V3DF etf__;	vcopy(etf__, etf[px][py]);

	float sqrt2 = sqrt(2.0f);	//sqrt(2)만큼 가자.
	//-S
	while (nN<init_n / 2){
		if (x<0 || x >= MAX_X || y<0 || y >= MAX_Y)	break;	//image 밖

		//1. 해당 점에서 etf
		GetETFAtPoint(x, y, etf_);
		//2. normalize
		vnorm(etf_);
		if (is_zero_vector(etf_))	break;

		angle = angle_r(etf_, etf__)*180.0f / PI;
		if (angle > threshold_Angle2){
			vnegate(etf_);
		}
		if (angle > threshold_Angle)	//연속한 etf가 이루는 각이 임계치 이상이면
			break;

		x_ = x - etf_[0];
		y_ = y - etf_[1];
		if (x_<0 || x_ >= MAX_X || y_<0 || y_ >= MAX_Y || imCL[(int)x_][(int)y_] != 0.0f)	break;				// coherent line 이 아니면 stop
		if (((int)x != (int)x_) || ((int)y != (int)y_))	// 너무 자잘하게 하지 않기 위해
			vector3(alpha[NEGATIVE][nN++], x_, y_, 0.0f);
		x = x_;	y = y_;

		vcopy(etf__, etf_);
	}

	//+S
	x = px;	y = py;
	vcopy(etf__, etf[px][py]);
	while (nP<init_n / 2){
		if (x<0 || x >= MAX_X || y<0 || y >= MAX_Y)	break;	//image 밖

		//1. 해당 점에서 etf
		GetETFAtPoint(x, y, etf_);
		//2. normalize
		vnorm(etf_);
		if (is_zero_vector(etf_))	break;

		angle = angle_r(etf_, etf__)*180.0f / PI;
		if (angle > threshold_Angle2){
			vnegate(etf_);
		}
		if (angle > threshold_Angle)	//연속한 etf가 이루는 각이 임계치 이상이면
			break;

		x_ = x + etf_[0];
		y_ = y + etf_[1];
		if (x_<0 || x_ >= MAX_X || y_<0 || y_ >= MAX_Y || imCL[(int)x_][(int)y_] != 0.0f)	break;				// coherent line 이 아니면 stop
		if (((int)x != (int)x_) || ((int)y != (int)y_))
			vector3(alpha[POSITIVE][nP++], x_, y_, 0.0f);
		x = x_;	y = y_;

		vcopy(etf__, etf_);
	}
	(*nPoints) = nN + nP + 1;
	if ((*nPoints) < 10){
		(*nPoints) = 0;
		for (i = 0; i<2; i++)		delete[] alpha[i];	delete[] alpha;
		return;
	}

	//최종 alpha(2D) -> Alpha(1D)(-S ~ +S)
	for (i = 0; i<init_n; i++)	vzero(Alpha[i]);	//0. 초기화
	for (i = 0; i<nN; i++)
		vcopy(Alpha[i], alpha[NEGATIVE][nN - 1 - i]);	//1. negative 값
	vector3(Alpha[i], px, py, 0.0f);	//2. 중심값
	int n = nN + 1;	//지금까지 정의된 Alpha 개수
	for (i = 0; i<nP; i++)
		vcopy(Alpha[n + i], alpha[POSITIVE][i]);	//3. positive 값

	for (i = 0; i<2; i++)		delete[] alpha[i];	delete[] alpha;
}

void Direction::build_skltn(){
	int i, j, k, l, px, py;

	//	1. 초기화: Streams가 지나가는 pixel은 1, 그렇지 않은 pixel은 0으로 setting
	for (i = 0; i < MAX_X; i++)  {
		for (j = 0; j < MAX_Y; j++) {
			if (vpath[i][j].sn == 0)	continue;

			vector3(vpath[i][j].BBox[0], 10000.0f, 10000.0f, 10000.0f);
			vector3(vpath[i][j].BBox[1], -10000.0f, -10000.0f, -10000.0f);
			for (k = 0; k < vpath[i][j].sn; k++) {
				px = (int)vpath[i][j].Alpha[k][0];	if (px<0) px = 0;	else if (px >= MAX_X) px = MAX_X - 1;
				py = (int)vpath[i][j].Alpha[k][1];	if (py<0) py = 0;	else if (py >= MAX_Y) py = MAX_Y - 1;
				skltn[px][py] = 1;
				if (vpath[i][j].BBox[0][0] > px)	vpath[i][j].BBox[0][0] = px;
				if (vpath[i][j].BBox[0][1] > py)	vpath[i][j].BBox[0][1] = py;

				if (vpath[i][j].BBox[1][0] < px)	vpath[i][j].BBox[1][0] = px;
				if (vpath[i][j].BBox[1][1] < py)	vpath[i][j].BBox[1][1] = py;
			}
		}
	}

	int cnt, scnt;
	int flag = 1;
	do {
		for (i = 1, cnt = 0; i < MAX_X - 1; i++) {
			for (j = 1; j < MAX_Y - 1; j++) {
				if (skltn[i][j] != flag)
					continue;
				for (k = i - 1, scnt = 0; k <= i + 1; k++) {
					for (l = j - 1; l <= j + 1; l++) {
						scnt += (skltn[k][l] >= flag);
					}
				}
				if (scnt == 9) {
					skltn[i][j] = flag + 1;
					cnt++;
				}
			}
		}
		flag++;
	} while (cnt > 0);

	//printf("Maximum skeleton: %d\n", flag);

	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			vpath[i][j].skltn = 0.0f;
			if (vpath[i][j].sn == 0)
				continue;

			for (k = 0; k < vpath[i][j].sn; k++) {
				px = (int)vpath[i][j].Alpha[k][0];	if (px<0) px = 0;	else if (px >= MAX_X) px = MAX_X - 1;
				py = (int)vpath[i][j].Alpha[k][1];	if (py<0) py = 0;	else if (py >= MAX_Y) py = MAX_Y - 1;
				vpath[i][j].skltn += skltn[px][py];
			}
			vpath[i][j].skltn /= vpath[i][j].sn;
		}
	}
}
void Direction::compute_center_line(int px, int py){
	int i, j, r, c;
	V3DF vec;
	V3DF nvec;
	V3DF Zaxis;
	float tcl;
	V3DF tpt1, tpt2;
	V3DF weights = { 0.5f, 0.3f, 0.2f };

	vector3(Zaxis, 0.0f, 0.0f, 1.0f);
	vpath[px][py].cl = 0;
	for (i = 0; i < vpath[px][py].sn; i++) {
		if (i == 0) {
			nvector(vec, vpath[px][py].Alpha[i + 1], vpath[px][py].Alpha[i]);
		}
		else if (i == vpath[px][py].sn - 1) {
			nvector(vec, vpath[px][py].Alpha[i], vpath[px][py].Alpha[i - 1]);
		}
		else {
			nvector(vec, vpath[px][py].Alpha[i + 1], vpath[px][py].Alpha[i - 1]);
		}

		nvcross(nvec, vec, Zaxis);

		r = (int)vpath[px][py].Alpha[i][0];	if (r<0) r = 0;	else if (r >= MAX_X) r = MAX_X - 1;
		c = (int)vpath[px][py].Alpha[i][1];	if (c<0) c = 0;	else if (c >= MAX_Y) c = MAX_Y - 1;
		tcl = skltn[r][c];

		vcopy(tpt1, vpath[px][py].Alpha[i]);
		for (j = 0; j < 3; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;
			tcl += weights[j] * skltn[(int)tpt2[0]][(int)tpt2[1]];
			vcopy(tpt1, tpt2);
		}

		vnegate(nvec);
		vcopy(tpt1, vpath[px][py].Alpha[i]);
		for (j = 0; j < 3; j++) {
			get_point(tpt2, tpt1, 1.0f, nvec);
			if (tpt2[0] < 0.0f)
				tpt2[0] = 0.0f;
			if (tpt2[1] < 0.0f)
				tpt2[1] = 0.0f;
			if (tpt2[0] > MAX_X - 1)
				tpt2[0] = MAX_X - 1;
			if (tpt2[1] > MAX_Y - 1)
				tpt2[1] = MAX_Y - 1;
			tcl += weights[j] * skltn[(int)tpt2[0]][(int)tpt2[1]];
			vcopy(tpt1, tpt2);
		}

		vpath[px][py].cl += tcl;
	}
}
void Direction::compute_center_line(){
	int i, j;
	float max_cl;
	int cl_cnt;

	for (i = 0, max_cl = 0.0f, cl_cnt = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			if (vpath[i][j].sn == 0)
				continue;

			//	1. estimate center_line
			compute_center_line(i, j);
			cl_cnt++;
			if (vpath[i][j].cl > max_cl)
				max_cl = vpath[i][j].cl;
		}
	}
	n_slist = cl_cnt;

	if (slist)	delete[] slist;
	slist = new V3DI[n_slist];
	for (i = 0, cl_cnt = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			if (vpath[i][j].cl > 0) {
				slist[cl_cnt][0] = i;
				slist[cl_cnt][1] = j;
				slist[cl_cnt++][2] = (int)(vpath[i][j].cl * 10000.0f);
			}
		}
	}

	if (n_slist == 0){	// There is no Stream
		nVpath = n_qlist = n_plist = n_slist;
		StreamsExisting = false;
		return;
	}

	qs(0, n_slist - 1, slist);
}
void Direction::build_center_line1(){
	int i;

	n_plist = 0;
	if (plist)	delete[] plist;
	plist = (V3DI *)calloc(n_slist, sizeof(V3DI));

	for (i = 0; i < n_slist; i++) {
		if (max_stream(slist[i][0], slist[i][1]))
			vcopy3i(plist[n_plist++], slist[i]);
	}
	//printf("slist -> plist: %d -> %d\n", n_slist, n_plist);
}
void Direction::build_center_line2(){
	//printf("build_center_line2..");
	int i, j;
	int flag;

	int nbhd_idx;
	int **nbhd_board = new int *[MAX_X];
	for (i = 0; i<MAX_X; i++){
		nbhd_board[i] = new int[MAX_Y];
		for (j = 0; j<MAX_Y; j++)
			nbhd_board[i][j] = 0;
	}
	nbhd_idx = 1;

	n_qlist = 0;
	if (qlist)	delete[] qlist;
	qlist = new V3DI[n_plist];

	vcopy3i(qlist[n_qlist++], plist[0]);
	for (i = 1; i < n_plist; i++) {
		//	1. determine the nearest one from qlist
		for (j = 0, flag = 0; j < n_qlist; j++) {
			if (disjoint(vpath[plist[i][0]][plist[i][1]].BBox[0], vpath[plist[i][0]][plist[i][1]].BBox[1], vpath[qlist[j][0]][qlist[j][1]].BBox[0], vpath[qlist[j][0]][qlist[j][1]].BBox[1]))
				continue;
			if (close_stream(nbhd_idx, nbhd_board, plist[i][0], plist[i][1], qlist[j][0], qlist[j][1], 2)) {
				flag = 1;
				break;
			}
		}

		//	2. if there is no close slist, then add to qlist
		if (flag == 0) {
			vcopy3i(qlist[n_qlist++], plist[i]);
		}
		//	2. if slist[i] is (i) mergible to the one, (ii) not mergible
		nbhd_idx++;
		if (i % 1000 == 0)
			printf("%d / %d -> %d\n", i, n_plist, n_qlist);
	}

	nVpath = n_qlist;

	for (i = 0; i<MAX_X; i++)	delete[] nbhd_board[i];	delete[] nbhd_board;
}


void Direction::sort_length(){
	int i;
	if (rlist)	delete[] rlist;
	rlist = new V3DI[n_qlist];
	int px, py;
	FlowPath *p;

	for (i = 0; i < n_qlist; i++) {
		px = qlist[i][0];	py = qlist[i][1];
		if (px<0)	px *= (-1.0f);
		else if (px >= MAX_X)	px = MAX_X - (px - (MAX_X - 1));
		if (py<0)	py *= (-1.0f);
		else if (py >= MAX_Y)	py = MAX_Y - (py - (MAX_Y - 1));

		if (px<0 || px >= MAX_X || py<0 || py >= MAX_Y)	continue;

		p = &(vpath[px][py]);
		p->get_length();
		rlist[i][0] = px;
		rlist[i][1] = py;
		rlist[i][2] = (int)(1000000.0f * vpath[px][py].length);
	}

	// normalize length
	float max_len = -INFINITY;
	for (i = 0; i<n_qlist; i++){
		px = qlist[i][0];	py = qlist[i][1];	p = &(vpath[px][py]);
		max_len = (max_len<p->length) ? p->length : max_len;
	}
	for (i = 0; i<n_qlist; i++){
		px = qlist[i][0];	py = qlist[i][1];	p = &(vpath[px][py]);
		p->nlength = p->length / max_len;
	}

	qs(0, n_qlist - 1, rlist);
}
float curv(V3DF p1, V3DF p2, V3DF p3)
{
	float xp, yp, xpp, ypp;

	xp = (p3[0] - p1[0]) / 2.0f;
	yp = (p3[1] - p1[1]) / 2.0f;
	xpp = (p3[0] + p1[0] - 2.0f * p2[0]) / 2.0f;
	ypp = (p3[1] + p1[1] - 2.0f * p2[1]) / 2.0f;
	if (fabs(xp) < 0.00001f && fabs(yp) < 0.00001f) {
		xp = 0.00001f;
		yp = 0.00001f;
	}
	return fabs(xp * ypp - yp * xpp) / pow(xp*xp + yp*yp, 1.5f);

}
void Direction::compute_curv(int x, int y)
{
	int i;

	FlowPath *p = &(vpath[x][y]);
	p->curv[0] = p->curv[p->sn - 1] = 0.0f;

	for (i = 1; i < p->sn - 1; i++) {
		p->curv[i] = curv(p->Alpha[i - 1], p->Alpha[i], p->Alpha[i + 1]);
	}

	int k;
	float csum;
	p->crange[0][0] = p->crange[0][1] = -1;
	p->crange[p->sn - 1][0] = p->crange[p->sn - 1][1] = -1;

	for (i = 1; i < p->sn - 1; i++) {
		for (k = i, csum = 0.0f; k > 0; k--) {
			csum += p->curv[k];
			if (csum >= p->tcurv)
				break;
		}
		p->crange[i][0] = k;
		for (k = i, csum = 0.0f; k < p->sn - 1; k++) {
			csum += p->curv[k];
			if (csum >= p->tcurv)
				break;
		}
		p->crange[i][1] = k;
	}
}

void Direction::curv_line(){
	//	n_qlist동안 rlist 처리
	int i;
	int x, y;

	FlowPath *p;
	for (i = 0; i < n_qlist; i++) {
		x = rlist[i][0];
		y = rlist[i][1];
		p = &(vpath[x][y]);

		p->tcurv = 0.1f;
		p->curv = new float[p->sn];
		p->crange = new V2DI[p->sn];

		compute_curv(x, y);
	}
}


void Direction::DoAmap(DistInfoSet **dmap){
	int i, j;
	int width1 = 5;
	int width2 = 2;
	int width_s = 2;

	if (!amap){
		amap = new float *[MAX_X];
		for (i = 0; i<MAX_X; i++)	amap[i] = new float[MAX_Y];
	}

	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			amap[i][j] = 0.0f;

			if (0 <= dmap[i][j].dinfo[0].dist && dmap[i][j].dinfo[0].dist <= width1) {
				amap[i][j] = (width1 - dmap[i][j].dinfo[0].dist) / (float)width1;
				amap[i][j] = pow(amap[i][j], 0.5f);
			}
			else
				amap[i][j] = 0.0f;
		}
	}
}

void Direction::DoFdir(DistInfoSet **dmap){
	int i, j;
	if (!fdir){
		fdir = new V3DF *[MAX_X];
		for (i = 0; i<MAX_X; i++)	fdir[i] = new V3DF[MAX_Y];
	}
	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			if (dmap[i][j].dinfo[0].dist > DWidth){
				vzero(fdir[i][j]);
				continue;
			}
			if (dmap[i][j].dinfo[0].f_idx == -1)
				vector3(fdir[i][j], 1.0f, 1.0f, 0.0f);
			else
				vcopy(fdir[i][j], dmap[i][j].dinfo[0].direction);
			vnorm(fdir[i][j]);
		}
	}

	if (!fdirFortdir){
		fdirFortdir = new V3DF *[MAX_X];
		for (i = 0; i<MAX_X; i++)	fdirFortdir[i] = new V3DF[MAX_Y];
	}
	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			if (dmap[i][j].dinfo[0].dist > 0){
				vzero(fdirFortdir[i][j]);
				continue;
			}
			if (dmap[i][j].dinfo[0].f_idx == -1)
				vector3(fdirFortdir[i][j], 1.0f, 1.0f, 0.0f);
			else
				vcopy(fdirFortdir[i][j], dmap[i][j].dinfo[0].direction);
			vnorm(fdirFortdir[i][j]);
		}
	}
}

void Direction::Set_res_dir()
{
	int i, j;
	for (i = 0; i < MAX_X; i++) {
		for (j = 0; j < MAX_Y; j++) {
			if (!is_zero_vector(fdirFortdir[i][j]))//&& amap[i][j]>0.5f ){
				vector3(res_dir[i][j], fdirFortdir[i][j][0], fdirFortdir[i][j][1], 0.0f);
			else
				vector3(res_dir[i][j], tdir[i][j][0], tdir[i][j][1], 0.0f);
		}
	}
}
