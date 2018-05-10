#include "stdafx.h"
#include "Pix.h"


extern int Width;
extern int Height;

void merge(int s, int m, int e, V2DFI *a)
{
	V2DFI *t = (V2DFI *)calloc(sizeof(V2DFI), e - s + 1);
	int i = s;
	int j = m + 1;
	int q = 0;


	while (i <= m && j <= e)
	{
		if (a[i].a < a[j].a){
			t[q].a = a[i].a;
			t[q++].b = a[i++].b;
		}
		else{
			t[q].a = a[j].a;
			t[q++].b = a[j++].b;
		}
	}


	for (; i <= m;){
		t[q].a = a[i].a;
		t[q++].b = a[i++].b;
	}

	for (; j <= e;){
		t[q].a = a[j].a;
		t[q++].b = a[j++].b;
	}

	for (int x = 0; x < e - s + 1; x++){
		a[s + x].a = t[x].a;
		a[s + x].b = t[x].b;
	}


	free(t);
}

void msort(int s, int e, V2DFI *a)
{
	if (s == e)
		return;

	int mid = (s + e) / 2;
	msort(s, mid, a);
	msort(mid + 1, e, a);
	merge(s, mid, e, a);
}

float gaussian(float x, float sigma, float mean)
{
	return exp((x - mean)*(x - mean) / (-2.0f*sigma*sigma)) / sqrt(6.28319*sigma*sigma);
}

void Pix::create(V3DF **cim, int iw, int ih, int resol)
{
	int wh = 32;

	input_w = iw;
	input_h = ih;

	cout << "insert number of box ( width or height) : ";

	if (input_w < input_h) {
		//output_h = wh;
		output_h = resol;
		output_w = (input_w * output_h) / input_h;
	}
	else{
		//output_w = wh;
		output_w = resol;
		output_h = (input_h * output_w) / input_w;
	}
	printf("output_w : %d\noutput_h : %d\n", output_w, output_h);

	if (output_w % 8 != 0)
		output_w = (int)(output_w / 8) * 8;
	if (output_h % 8 != 0)
		output_h = (int)(output_h / 8) * 8;
	printf("output_w : %d\noutput_h : %d\n", output_w, output_h);


	output_img = (V3DF **)malloc(output_w*sizeof(V3DF*));
	palette_assign = (int **)malloc(output_w*sizeof(int*));
	superpixel_pos = (V2DF**)malloc(output_w*sizeof(V2DF*));
	superpixel_color = (V3DF**)malloc(output_w*sizeof(V3DF*));
	superpixel_weights = (float**)malloc(output_w*sizeof(float*));
	output_NearPaletteImg = (V3DF **)malloc(output_w*sizeof(V3DF*));
	for (int i = 0; i < output_w; i++) {
		output_img[i] = (V3DF *)malloc(output_h*sizeof(V3DF));
		palette_assign[i] = (int*)malloc(output_h*sizeof(int));
		superpixel_pos[i] = (V2DF *)malloc(output_h*sizeof(V3DF));
		superpixel_color[i] = (V3DF *)malloc(output_h*sizeof(V3DF));
		superpixel_weights[i] = (float*)malloc(output_h*sizeof(float));
		output_NearPaletteImg[i] = (V3DF *)malloc(output_h*sizeof(V3DF));
		for (int j = 0; j < output_h; j++){
			vector3(output_img[i][j], 0.0f, 0.0f, 0.0f);
			palette_assign[i][j] = 0;
			superpixel_weights[i][j] = 0.0f;
		}
	}

	region_map = (V2DI**)malloc(input_w*sizeof(V2DI*));
	for (int i = 0; i < input_w; i++) {
		region_map[i] = (V2DI*)malloc(input_h*sizeof(V2DI));
	}

	input_img = (V3DF**)malloc(input_w*sizeof(V3DF*));
	input_weights = (float **)malloc(input_w*sizeof(float*));
	for (int i = 0; i < input_w; i++) {
		input_img[i] = (V3DF*)malloc(input_h*sizeof(V3DF));
		input_weights[i] = (float*)malloc(input_h*sizeof(float));
		for (int j = 0; j < input_h; j++){
			input_weights[i][j] = 1.0f;
			vassign(input_img[i][j], cim[i][j]);
		}
	}

	conv_RGBtoLAB(input_img, input_w, input_h);
}

void Pix::initialize()
{
	V3DF first_color;					// palette 기본 값 ==> input_img 평균 색
	V3DF Evec;
	float Eval;

	V3DF RGB;

	vzero(Evec);
	Eval = 0.0f;

	iteration = 0;

	//palette크기를 조절///////////////////////////////////////
	//max_palette_size = 15;
	cout << "insert max palette size : ";
	//cin >> max_palette_size;
	max_palette_size = 18; // 입력받지 않고 고정
	///////////////////////////////////////////////////////////

	palette_size = 0;
	prob_c_size = 0;
	slic_factor = 45;
	smooth_pos_factor = 0.4f;
	sigma_color = 0.87f;
	sigma_position = 0.87f;

	converged_flag = false;
	palette_maxed_flag = false;

	// 슈퍼픽셀에 속하는 픽셀 수 계산
	range_ = sqrt((input_h / (float)output_h) * (input_w / (float)output_w));

	// 슈퍼픽셀을 regular grid로 초기화
	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {
			superpixel_pos[i][j][0] = ((i + 0.5f) / (float)output_w * input_w);
			superpixel_pos[i][j][1] = ((j + 0.5f) / (float)output_h * input_h);
		}
	}

	// 각 픽셀들이 어떤 슈퍼픽셀에 속하는지 계산
	for (int i = 0; i < input_w; i++) {
		for (int j = 0; j < input_h; j++) {
			region_map[i][j][0] = (int)(i / (float)input_w*output_w);
			region_map[i][j][1] = (int)(j / (float)input_h*output_h);
		}
	}


	// 각 슈퍼픽셀의 중심 위치와 대표색을 업데이트
	Update_Superpixel_Means();

	// 팔레트에 들어갈 첫 색을 초기화 ( 슈퍼픽셀 대표색들의 평균값 )
	vzero(first_color);
	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {
			vadd(first_color, superpixel_color[i][j]);
		}
	}

	// 각 확률 초기화
	prob_c = (float*)malloc((max_palette_size * 3)*sizeof(float));
	prob_co = (float**)malloc((max_palette_size * 3)*sizeof(float*));
	for (int i = 0; i < max_palette_size * 3; i++) {
		prob_co[i] = (float*)malloc((output_w*output_h)*sizeof(float));
	}
	prob_oc = (float**)malloc((max_palette_size * 3)*sizeof(float*));
	for (int i = 0; i < max_palette_size * 3; i++) {
		prob_oc[i] = (float*)malloc((output_w*output_h)*sizeof(float));
	}

	prob_o = 1.0f / (float)(output_w*output_h);
	prob_c[prob_c_size++] = 0.5f;
	prob_c[prob_c_size++] = 0.5f;

	printf("prob_c == %d\n", prob_c_size);

	// 각 팔레트의 색에 대한 슈퍼픽셀의 확률
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < output_w*output_h; j++)
			prob_co[i][j] = 0.5f;
	}
	prob_co_size = 2;

	// 팔레트에 첫색과 첫색을 perturb한 값 넣기
	RGB_palette = (V3DF*)malloc((max_palette_size)*sizeof(V3DF));
	palette = (V3DF*)malloc((max_palette_size * 5)*sizeof(V3DF));
	vscalar(first_color, prob_o);
	vassign(palette[palette_size++], first_color);

	// 팔레트 기본 색에 대한 eigen value & vector 구하기
	Eval = GetMaxEigen(0, Evec);
	vscalar(Evec, kSubclusterPertubation);					// eigen vector * 0.8
	vadd(first_color, Evec);
	vassign(palette[palette_size++], first_color);

	//printf("\nevec : %f %f %f\n", Evec[0], Evec[1], Evec[2]);
	//printf("eval  : %f\n\n", Eval);


	//LABtoRGB(palette[0][0], palette[0][1], palette[0][2], &RGB[0], &RGB[1], &RGB[2]);
	//printf("[0] plaette :	%f %f %f	\n", RGB[0] * 255.0f, RGB[1] * 255.0f, RGB[2] * 255.0f);
	//LABtoRGB(palette[1][0], palette[1][1], palette[1][2], &RGB[0], &RGB[1], &RGB[2]);
	//printf("[1] plaette :	%f %f %f	\n\n", RGB[0] * 255.0f, RGB[1] * 255.0f, RGB[2] * 255.0f);


	// 서브 슈퍼픽셀 페어 넣기
	sub_superpixel_pairs = (V2DI*)malloc((max_palette_size * 3)*sizeof(V2DI));
	sub_pair_size = 0;
	vector2(sub_superpixel_pairs[sub_pair_size++], 0, 1);

	// T값 초기화 ( 1.1 * Max eigenvalue )
	temperature = kT0SafteyFactor * sqrt(2.0f * Eval);

	// 확정된 palette 색
	locked_colors = (bool*)malloc(max_palette_size*sizeof(bool));
	for (int i = 0; i < max_palette_size; i++)
		locked_colors[i] = false;


	pixel_constraints = (int**)malloc((output_w*output_h)*sizeof(int*));
	constraints_size = (int*)malloc((output_w*output_h)*sizeof(int));
	for (int i = 0; i < output_w*output_h; i++) {
		pixel_constraints[i] = (int*)malloc((max_palette_size * 3)*sizeof(int));
		constraints_size[i] = 0;
	}
}

void Pix::Associate_Palette()
{
	int curr_palette_size, constraints_idx;
	int probs_size;
	int c_s = 0;
	int idx, color_idx, best_idx;
	double overT = -1.0 / temperature;
	double best_err, sum_prob;
	double color_err, prob, prob_sp, normalized_prob;

	V3DF pixel;

	int *constraints;
	float *new_prob_c;
	double *probs;

	curr_palette_size = palette_size;
	new_prob_c = (float*)malloc(curr_palette_size*sizeof(float));
	for (int i = 0; i < curr_palette_size; i++)
		new_prob_c[i] = 0.0f;

	constraints = (int*)malloc((max_palette_size * 3)*sizeof(int));
	probs = (double*)malloc((max_palette_size * 3)*sizeof(double));

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			probs_size = 0;
			best_idx = -1;
			vassign(pixel, superpixel_color[i][j]);
			sum_prob = 0;

			c_s = constraints_size[i + (j*output_w)];
			if (c_s == 0) {
				for (int k = 0; k < palette_size; k++)
					constraints[c_s++] = k;
			}
			else {
				for (int k = 0; k < c_s; k++)
					constraints[k] = pixel_constraints[i + (j*output_w)][k];
			}



			//printf("======\n");

			for (int nCol = 0; nCol < c_s; nCol++) {									// 팔레트 색만큼 반복

				idx = nCol;
				color_err = vlength(palette[idx], pixel);								// 슈퍼픽셀 색과 팔레트 색의 차이
				prob = prob_c[idx] * exp(color_err * overT);							// P( c_k | p_s ) 계산
				probs[probs_size++] = prob;
				sum_prob += prob;

				//printf("요놈 [%d] %f, %f\n", idx, prob_c[idx], prob);


				if (best_idx == -1 || prob > best_err) {							// 슈퍼픽셀에 팔레트 색이 할당되지 않은 경우 || 더 차이가 적은 색인 경우

					best_idx = idx;														// best idx와
					best_err = prob;												// best err 교체
				}

				//if (best_idx == -1 || color_err < best_err) {							// 슈퍼픽셀에 팔레트 색이 할당되지 않은 경우 || 더 차이가 적은 색인 경우
				//	best_idx = idx;														// best idx와
				//	best_err = color_err;												// best err 교체
				//}

			}


			palette_assign[i][j] = best_idx;											// 가장 적은 err가진 팔레트 색을 슈퍼픽셀에 할당

			prob_sp = superpixel_weights[i][j];
			constraints_idx = 0;


			for (int nCol = 0; nCol < c_s; nCol++) {
				color_idx = nCol;
				normalized_prob = probs[constraints_idx] / sum_prob;
				//printf("요놈 %d) %f / %f = %f\n", nCol, probs[constraints_idx], sum_prob, normalized_prob);
				prob_co[color_idx][i + (j*output_w)] = (float)normalized_prob;
				new_prob_c[color_idx] += prob_sp * normalized_prob;
				//printf("요놈 [%d]%f %f\n", color_idx, new_prob_c[color_idx], prob_sp * normalized_prob);
				constraints_idx++;
			}
			prob_co_size = c_s;
		}
	}

	for (int i = 0; i <= color_idx; i++){
		prob_c[i] = new_prob_c[i];
		//printf("요놈 prob_c[%d] = %f\n", i, new_prob_c[i]); 
	}

	free(constraints);
	free(new_prob_c);
	free(probs);
}

float Pix::Refine_Palette()
{
	int current_palette_size;
	float prob_sp, palette_err;
	double w;
	V3DF pixel_clr, tmp, color, new_color;
	V3DF *color_sums;

	current_palette_size = palette_size;

	color_sums = (V3DF *)malloc(current_palette_size*sizeof(V3DF));
	for (int i = 0; i < current_palette_size; i++)
		vzero(color_sums[i]);

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			prob_sp = superpixel_weights[i][j];				// = P(p_s)
			vassign(pixel_clr, superpixel_color[i][j]);		// = m_s'

			for (int k = 0; k < palette_size; k++) {
				//printf("ㅠㅠㅠㅠ%d) %f\n", k, prob_co[k][i + (j*output_w)]);
				w = prob_sp * prob_co[k][i + (j*output_w)];
				vassign(tmp, pixel_clr);
				//vscalar(tmp, w);
				tmp[0] *= w;	tmp[1] *= w;	tmp[2] *= w;
				vadd(color_sums[k], tmp);
			}
		}
	}

	//for (int i = 0; i < palette_size; i++)
	//	printf("^color_sums[%d] : %f %f %f\n", i, color_sums[i][0], color_sums[i][1], color_sums[i][2]);


	palette_err = 0;
	for (int i = 0; i < palette_size; i++) {

		vassign(color, palette[i]);
		if (!locked_colors[i] && prob_c[i] > 0) {

			vassign(tmp, color_sums[i]);
			//printf("	^1tmp = %f %f %f\n", tmp[0], tmp[1], tmp[2]);
			if (prob_c[i] == 0)
				vzero(new_color);
			else
				vscalar(tmp, 1.0f / prob_c[i]);
			//printf("	^2tmp = %f %f %f\n", tmp[0], tmp[1], tmp[2]);
			vassign(new_color, tmp);
			vassign(palette[i], new_color);
			palette_err += vlength(color, new_color);

		}

	}

	free(color_sums);

	return palette_err;
}

void Pix::Expand_Palette()
{

	if (palette_maxed_flag)
		return;

	int num_colors, num_subclusters, idx1, idx2, splits_size;
	float subcluster_err, Eval;
	V2DFI *splits;
	V3DF clr1, clr2, Evec;

	num_colors = palette_size;
	num_subclusters = sub_pair_size;
	splits = (V2DFI*)malloc((max_palette_size * 3)*sizeof(V2DFI));
	splits_size = 0;

	vzero(Evec);
	Eval = 0.0f;

	for (int i = 0; i < num_subclusters; i++) {

		idx1 = sub_superpixel_pairs[i][0];
		idx2 = sub_superpixel_pairs[i][1];
		vassign(clr1, palette[idx1]);
		vassign(clr2, palette[idx2]);

		subcluster_err = vlength(clr1, clr2);									// sub superpixel간의 색 차이
		if (subcluster_err > kPaletteErrorTolerance) {							// 색 차이가 오차 범위보다 클 경우	
			splits[splits_size].a = subcluster_err;								// 새로 분리하기 위해 splits에 넣어줌
			splits[splits_size++].b = i;										// splits.a : err | splits.b : sub_pixel의 index
		}
		else {
			Eval = GetMaxEigen(idx1, Evec);										// 색 차이가 오차 범위보다 작을 경우
			vscalar(Evec, kSubclusterPertubation);								// 분리할 필요가 없기 때문에
			vadd(palette[idx2], Evec);											// 첫번째 색의 Eigen vector * 0.8한 값을 두번째 색에 더해준다.
		}

	}

	if (splits_size > 0)														// 팔레트의 공간은 한정되어 있기 때문에
		msort(0, splits_size - 1, splits);										// 오차가 큰 순서로 정렬하여 분리하는 데에 우선순위를 부여


	for (int i = splits_size - 1; i >= 0; i--) {									// 오차가 큰 순서로 분리 진행 ( 뒤에서 부터 )
		splitColor(splits[i].b);

		if (palette_size >= 2 * max_palette_size) {
			Condense_Palette();
			break;
		}
	}

	free(splits);
}

void Pix::splitColor(int pair_idx)
{
	int idx1, idx2, next_idx1, next_idx2;
	float Eval;
	V3DF clr1, clr2, subcluster_clr1, subcluster_clr2, Evec;
	V2DI new_pair;

	vzero(Evec);
	Eval = 0.0f;

	idx1 = sub_superpixel_pairs[pair_idx][0];									// 분리해야 될 색 1의 idx
	idx2 = sub_superpixel_pairs[pair_idx][1];									// 분리해야 될 색 2의 idx
	next_idx1 = palette_size;
	next_idx2 = next_idx1 + 1;
	vassign(clr1, palette[idx1]);
	vassign(clr2, palette[idx2]);

	Eval = GetMaxEigen(idx1, Evec);
	vscalar(Evec, kSubclusterPertubation);
	vadd(subcluster_clr1, clr1, Evec);											// 분리해야 될 색 1에 Evec * 0.8 값을 더해 subcluster_clr1에 저장

	Eval = GetMaxEigen(idx2, Evec);
	vscalar(Evec, kSubclusterPertubation);
	vadd(subcluster_clr2, clr2, Evec);											// 분리해야 될 색 2에 Evec * 0.8 값을 더해 subcluster_clr2에 저장

	vassign(palette[palette_size++], subcluster_clr1);							// palette에 subcluster_clr1 넣기
	sub_superpixel_pairs[pair_idx][1] = next_idx1;								// 현재 sub_superpixel_pairs의 두번째 자리에 subcluster_clr1 넣기
	prob_c[idx1] *= 0.5f;
	prob_c[prob_c_size++] = prob_c[idx1];
	for (int i = 0; i < output_w*output_h; i++)
		prob_co[prob_c_size][i] = prob_co[idx1][i];
	prob_co_size++;

	vassign(palette[palette_size++], subcluster_clr2);
	vector2(new_pair, idx2, next_idx2);
	vassign(sub_superpixel_pairs[sub_pair_size++], new_pair);
	prob_c[idx2] *= 0.5f;
	prob_c[prob_c_size++] = prob_c[idx2];
	for (int i = 0; i < output_w*output_h; i++)
		prob_co[prob_co_size][i] = prob_co[idx2][i];
	prob_co_size++;

}

void Pix::Condense_Palette()
{
	palette_maxed_flag = true;

	int idx1, idx2, new_palette_size, new_prob_c_size, new_prob_co_size;
	float weight1, weight2, total_w;

	int **nPaletteAssign;
	float **new_prob_co;
	float *new_prob_c;
	V3DF tmp1, tmp2;
	V3DF *old_palette, *new_palette;

	nPaletteAssign = (int**)malloc(output_w*sizeof(int*));
	for (int i = 0; i < output_w; i++)
		nPaletteAssign[i] = (int*)malloc(output_h*sizeof(int));

	new_palette_size = new_prob_c_size = new_prob_co_size = 0;
	new_prob_c = (float*)malloc((max_palette_size * 3)*sizeof(float));
	new_prob_co = (float**)malloc((max_palette_size * 3)*sizeof(float*));
	for (int i = 0; i < max_palette_size * 3; i++) {
		new_prob_co[i] = (float*)malloc((output_w*output_h)*sizeof(float));
	}

	old_palette = (V3DF*)malloc(palette_size*sizeof(V3DF));
	new_palette = (V3DF*)malloc(max_palette_size*sizeof(V3DF));
	for (int i = 0; i < palette_size; i++)
		vassign(old_palette[i], palette[i]);

	for (int i = 0; i < sub_pair_size; i++) {

		idx1 = sub_superpixel_pairs[i][0];
		idx2 = sub_superpixel_pairs[i][1];
		weight1 = prob_c[idx1];
		weight2 = prob_c[idx2];
		total_w = weight1 + weight2;

		weight1 /= total_w;
		weight2 /= total_w;

		vassign(tmp1, old_palette[idx1]);
		vassign(tmp2, old_palette[idx2]);
		vscalar(tmp1, weight1);
		vscalar(tmp2, weight2);
		vadd(new_palette[new_palette_size++], tmp1, tmp2);

		new_prob_c[new_prob_c_size++] = prob_c[idx1] + prob_c[idx2];
		for (int j = 0; j < output_w*output_h; j++)
			new_prob_co[new_prob_co_size][j] = prob_co[idx1][j];
		new_prob_co_size++;

		for (int x = 0; x < output_w; x++) {
			for (int y = 0; y < output_h; y++) {

				if (palette_assign[x][y] == idx1 || palette_assign[x][y] == idx2)
					nPaletteAssign[x][y] = i;

			}
		}
	}

	for (int i = 0; i < new_palette_size; i++)
		vassign(palette[i], new_palette[i]);
	palette_size = new_palette_size;

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++)
			palette_assign[i][j] = nPaletteAssign[i][j];
	}

	for (int i = 0; i < new_prob_c_size; i++)
		prob_c[i] = new_prob_c[i];
	prob_c_size = new_prob_c_size;

	for (int i = 0; i < new_prob_co_size; i++) {
		for (int j = 0; j < output_w*output_h; j++)
			prob_oc[i][j] = new_prob_co[i][j];
	}
	prob_oc_size = new_prob_co_size;

	for (int i = 0; i < output_w; i++)
		free(nPaletteAssign[i]);
	for (int i = 0; i < max_palette_size * 3; i++)
		free(new_prob_co[i]);

	free(nPaletteAssign);
	free(new_prob_co);
	free(new_prob_c);
	free(old_palette);
	free(new_palette);
}

void Pix::GetAveragedPalette(V3DF *avg)
{
	V3DF average_color, clr1, clr2;
	int idx1, idx2;
	float weight1, weight2, total_w;

	for (int i = 0; i < palette_size; i++)
		vassign(avg[i], palette[i]);

	if (!palette_maxed_flag) {															// palette의 색이 꽉 차지 않았을 경우

		for (int i = 0; i < sub_pair_size; i++) {

			idx1 = sub_superpixel_pairs[i][0];
			idx2 = sub_superpixel_pairs[i][1];

			vassign(clr1, palette[idx1]);
			vassign(clr2, palette[idx2]);

			weight1 = prob_c[idx1];
			weight2 = prob_c[idx2];
			total_w = weight1 + weight2;

			weight1 /= total_w;
			weight2 /= total_w;

			vector3(average_color, (weight1 * clr1[0]) + (weight2 * clr2[0]), (weight1 * clr1[1]) + (weight2 * clr2[1]), (weight1 * clr1[2]) + (weight2 * clr2[2]));

			vassign(avg[idx1], average_color);											// sub superpixel 간의 평균값
			vassign(avg[idx2], average_color);
		}

	}
}

void Pix::Update_Superpixel_Mapping()
{
	V2DF pos, tmp;
	V2DI sp;
	V3DF *averaged_palette, sc, pixel_color;
	float **distance;
	int min_x, min_y, max_x, max_y, idx;
	int ti, tj;
	float color_err, dist_err, err;

	averaged_palette = (V3DF*)malloc(palette_size*sizeof(V3DF));
	GetAveragedPalette(averaged_palette);

	distance = (float**)malloc(input_w*sizeof(float*));
	for (int i = 0; i < input_w; i++) {
		distance[i] = (float*)malloc(input_h*sizeof(float));
		for (int j = 0; j < input_h; j++) {
			distance[i][j] = -5.0f;
			vector2(region_map[i][j], -1, -1);
		}
	}


	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			vassign2(pos, superpixel_pos[i][j]);
			min_x = (int)max2f(0.0f, pos[0] - (float)range_);
			min_y = (int)max2f(0.0f, pos[1] - (float)range_);
			max_x = min2i(input_w - 1, (int)pos[0] + range_);
			max_y = min2i(input_h - 1, (int)pos[1] + range_);

			vassign(sc, averaged_palette[palette_assign[i][j]]);						// 현재 슈퍼픽셀에 할당된 팔레트의 색

			idx = i + (output_w * j);

			for (int ii = min_x; ii < max_x; ii++) {									// 슈퍼픽셀 범위 만큼 ( range_ )
				for (int jj = min_y; jj < max_y; jj++) {

					vassign(pixel_color, input_img[ii][jj]);
					vsub(pixel_color, sc);												// 할당된 팔레트 색 - 원본 픽셀 색
					color_err = vlength(pixel_color);									// 색 차이의 크기

					vassign2(tmp, pos);
					tmp[0] -= (float)ii;		tmp[1] -= (float)jj;					// 슈퍼픽셀 위치 - 원본 픽셀 위치
					dist_err = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1]);						// 위치 차이의 크기

					err = color_err + slic_factor / range_ * dist_err;					// 색 & 위치 차이

					if (distance[ii][jj] < 0 || err < distance[ii][jj]) {				// 해당 픽셀에 할당된 슈퍼픽셀이 없거나 || 기존 할당된 슈퍼픽셀보다 차이가 적을 때
						distance[ii][jj] = err;
						vector2(region_map[ii][jj], i, j);								// 슈퍼픽셀 할당
					}

				}
			}
		}
	}

	for (int i = 0; i < input_w; i++) {
		for (int j = 0; j < input_h; j++) {

			vassign(sp, region_map[i][j]);
			idx = sp[0] + (sp[1] * output_w);

			if (region_map[i][j][0] == -1 && region_map[i][j][1] == -1) {				// 슈퍼픽셀이 할당되지 않은 픽셀이 있다면
				ti = (int)(i / (float)input_w*output_w);
				tj = (int)(j / (float)input_h*output_h);
				vector2(region_map[i][j], ti, tj);										// 위치에 따라서 슈퍼픽셀 할당
				idx = ti + (tj*output_w);
			}

		}
	}

	for (int i = 0; i < input_w; i++)
		free(distance[i]);
	free(distance);
	free(averaged_palette);
}

void Pix::Update_Superpixel_Means()
{

	V3DF **clr_sum;				// 각 슈퍼픽셀에 속하는 픽셀 색의 총합
	V2DF **pos_sum;				// 각 슈퍼픽셀에 속하는 픽셀 위치의 총합
	float **weights;

	V2DI sp;
	V3DF pclr;
	V2DF curr;

	int total_w, xx, yy;
	float w, wn;

	pos_sum = (V2DF**)malloc(output_w*sizeof(V2DF*));
	clr_sum = (V3DF**)malloc(output_w*sizeof(V3DF*));
	weights = (float**)malloc(output_w*sizeof(float*));
	for (int i = 0; i < output_w; i++) {
		pos_sum[i] = (V2DF *)malloc(output_h*sizeof(V3DF));
		clr_sum[i] = (V3DF *)malloc(output_h*sizeof(V3DF));
		weights[i] = (float *)malloc(output_h*sizeof(float));
		for (int j = 0; j < output_h; j++) {
			vector2(pos_sum[i][j], 0.0f, 0.0f);
			vector3(clr_sum[i][j], 0.0f, 0.0f, 0.0f);
			weights[i][j] = 0.0f;
		}
	}

	for (int i = 0; i < input_w; i++) {
		for (int j = 0; j < input_h; j++) {

			vector2(curr, (float)i, (float)j);								// 현재 픽셀의 위치
			vassign(sp, region_map[i][j]);									// 현재 픽셀이 속하는 슈퍼픽셀
			vassign(pclr, input_img[i][j]);									// 현재 픽셀의 색

			vadd(clr_sum[sp[0]][sp[1]], pclr);								// clr_sum += pclr
			vadd2(pos_sum[sp[0]][sp[1]], curr);								// pos_sum += curr

			weights[sp[0]][sp[1]] += 1.0f;									// 슈퍼픽셀에 속하는 픽셀 수만큼 weight 부여
			superpixel_weights[sp[0]][sp[1]] += input_weights[i][j];		// importance map 값 반영

		}
	}

	total_w = 0.0f;
	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			w = weights[i][j];
			if (w == 0) {													// weights == 0, 슈퍼픽셀에 속하는 픽셀이 없는 경우
				xx = i / (float)output_w * input_w;
				yy = j / (float)output_h * input_h;
				vassign(superpixel_color[i][j], input_img[xx][yy]);			// input_img의 색을 그대로 대표색으로 지정
			}
			else {
				wn = 1.0f / w;
				vscalar(clr_sum[i][j], wn);									// 색 평균
				pos_sum[i][j][0] *= wn;		pos_sum[i][j][1] *= wn;			// 위치 평균
				vassign(superpixel_color[i][j], clr_sum[i][j]);				// superpixel_color = clr_sum
				vassign2(superpixel_pos[i][j], pos_sum[i][j]);				// superpixel_pos = pos_sum;
				superpixel_weights[i][j] *= wn;								// w * (1/w) = 1
				total_w += superpixel_weights[i][j];						// superpixel_weights의 총합 (==> 슈퍼픽셀 갯수)
			}
		}
	}

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {
			superpixel_weights[i][j] /= total_w;							// 1 / w
		}
	}

	Smooth_Superpixel_Pos();												// lapacian을 이용하여 중심 스무딩
	Smooth_Superpixel_Clr();												// bilateral filter를 이용하여 대표색 스무딩

	for (int i = 0; i < output_w; i++) {
		free(pos_sum[i]);
		free(clr_sum[i]);
		free(weights[i]);
	}
	free(pos_sum);
	free(clr_sum);
	free(weights);
}

void Pix::Smooth_Superpixel_Pos()
{
	V2DF **new_superpixel_pos;												// 새로운 슈퍼픽셀의 위치
	V2DF sum, orig, nPos;													// 이웃한 슈퍼픽셀 위치의 합, 본인 위치, 새로운 위치
	float cnt;																// 이웃한 슈퍼픽셀의 수 ( 최대 4 )

	new_superpixel_pos = (V2DF**)malloc(output_w*sizeof(V2DF*));
	for (int i = 0; i < output_w; i++)
		new_superpixel_pos[i] = (V2DF *)malloc(output_h*sizeof(V2DF));

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			vzero2(sum);
			cnt = 0.0f;
			// 이웃한 슈퍼픽셀 위치의 합
			if (i > 0) {													// 좌
				vadd2(sum, superpixel_pos[i - 1][j]);
				cnt += 1.0f;
			}
			if (i < output_w - 1) {											// 우
				vadd2(sum, superpixel_pos[i + 1][j]);
				cnt += 1.0f;
			}
			if (j > 0) {													// 하
				vadd2(sum, superpixel_pos[i][j - 1]);
				cnt += 1.0f;
			}
			if (j < output_h - 1) {											// 상
				vadd2(sum, superpixel_pos[i][j + 1]);
				cnt += 1.0f;
			}

			sum[0] /= cnt;
			sum[1] /= cnt;

			//printf("%d %d)	%f %f\n", i, j, sum[0], sum[1]);

			vassign2(orig, superpixel_pos[i][j]);
			vzero2(nPos);
			//if (i == 0 || i == output_w - 1)													// 본인 위치가 x의 경계에 있을 땐 그대로 유지
			//	nPos[0] = superpixel_pos[i][j][0];												
			//else																				// 새로운 위치 ==> 본인 위치 * 0.6 + 평균위치 * 0.4
			nPos[0] = (1.0f - smooth_pos_factor)*orig[0] + smooth_pos_factor*sum[0];
			//if (j == 0 || j == output_h - 1)													// 본인 위치가 y의 경계에 있을 땐 그대로 유지
			//	nPos[1] = superpixel_pos[i][j][1];
			//else																				// 새로운 위치 ==> 본인 위치 * 0.6 + 평균위치 * 0.4
			nPos[1] = (1.0f - smooth_pos_factor)*orig[1] + smooth_pos_factor*sum[1];

			vassign2(new_superpixel_pos[i][j], nPos);
		}
	}

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++)
			vassign(superpixel_pos[i][j], new_superpixel_pos[i][j]);
	}

	for (int i = 0; i < output_w; i++)
		free(new_superpixel_pos[i]);
	free(new_superpixel_pos);
}

void Pix::Smooth_Superpixel_Clr()
{
	V3DF **new_superpixel_clr;												// 새로운 슈퍼픽셀의 색
	V3DF sum, sp_c, c_n, tmp;
	V2DI p, p2;
	int min_x, min_y, max_x, max_y;
	float weight, d_c, w_c, d_p, w_p, w_total;

	new_superpixel_clr = (V3DF**)malloc(output_w*sizeof(V3DF*));
	for (int i = 0; i < output_w; i++)
		new_superpixel_clr[i] = (V3DF *)malloc(output_h*sizeof(V3DF));

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			min_x = max2i(0, i - 1);										// 3X3 filter
			max_x = min2i(output_w - 1, i + 1);
			min_y = max2i(0, j - 1);
			max_y = min2i(output_h - 1, j + 1);

			vzero(sum);
			weight = 0.0f;

			vassign(sp_c, superpixel_color[i][j]);
			vector2(p, i, j);

			for (int ii = min_x; ii <= max_x; ii++) {
				for (int jj = min_y; jj <= max_y; jj++) {

					vector2(p2, ii, jj);
					vassign(c_n, superpixel_color[ii][jj]);
					vsub(tmp, sp_c, c_n);									// 본인-이웃 슈퍼픽셀의 색 차이
					d_c = vlength(tmp);										// 색 차이의 크기
					w_c = gaussian(d_c, sigma_color, 0.0f);					// 색 차이의 가우시안 
					d_p = pdist2(p, p2);									// 본인-이웃 슈퍼픽셀의 위치 차이
					w_p = gaussian(d_p, sigma_position, 0.0f);				// 위치 차이의 가우시안
					w_total = w_c * w_p;									// g(I|(x_i) - I(x)||) * g(x_i - x)

					weight += w_total;
					vscalar(c_n, w_total);
					vadd(sum, c_n);											// sum += c_n * w_total

				}
			}

			vscalar(sum, 1.0f / weight);									// normalize
			vassign(new_superpixel_clr[i][j], sum);
		}
	}

	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++)
			vassign(superpixel_color[i][j], new_superpixel_clr[i][j]);
	}

	for (int i = 0; i < output_w; i++)
		free(new_superpixel_clr[i]);
	free(new_superpixel_clr);
}

float Pix::GetMaxEigen(int palette_index, V3DF Evec)
{
	int idx;
	float prob_oc, len, sum = 0;
	float Eval;
	V3DF color_error;
	M3DF mat;
	matrix3(mat, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);


	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			idx = i + (output_w * j);
			//printf("%f %f %f\n", prob_co[palette_index][idx], prob_o, prob_c[palette_index]);
			prob_oc = prob_co[palette_index][idx] * prob_o / prob_c[palette_index];
			sum += prob_oc;

			//printf("%f %f %f\n", palette[palette_index][0] - superpixel_color[i][j][0], palette[palette_index][1] - superpixel_color[i][j][1], palette[palette_index][2] - superpixel_color[i][j][2]);
			vsub(color_error, palette[palette_index], superpixel_color[i][j]);

			vector3(color_error, abs(color_error[0]), abs(color_error[1]), abs(color_error[2]));
			//printf("%f		%f %f %f\n", prob_oc, color_error[0], color_error[1], color_error[2]);


			madd(mat, color_error[0] * color_error[0] * prob_oc, color_error[0] * color_error[1] * prob_oc, color_error[0] * color_error[2] * prob_oc,
				color_error[0] * color_error[1] * prob_oc, color_error[1] * color_error[1] * prob_oc, color_error[2] * color_error[1] * prob_oc,
				color_error[0] * color_error[2] * prob_oc, color_error[1] * color_error[2] * prob_oc, color_error[2] * color_error[2] * prob_oc);

		}
	}

	//for (int i = 0; i < 3; i++){
	//	for (int j = 0; j < 3; j++)
	//		printf("%f ", mat[i][j]);
	//	printf("\n");
	//}

	MatrixXd mat2(3, 3);
	mat2(0, 0) = mat[0][0];
	mat2(0, 1) = mat[0][1];
	mat2(0, 2) = mat[0][0];
	mat2(1, 0) = mat[1][0];
	mat2(1, 1) = mat[1][1];
	mat2(1, 2) = mat[1][0];
	mat2(2, 0) = mat[2][0];
	mat2(2, 1) = mat[2][1];
	mat2(2, 2) = mat[2][0];

	EigenSolver<MatrixXd> es(mat2);

	//cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl << endl;
	//cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;

	Eval = es.eigenvalues()[0].real();
	//printf("Eval : %f\n", Eval);
	vector3(Evec, (float)es.eigenvectors().col(0)[0].real(), (float)es.eigenvectors().col(0)[1].real(), (float)es.eigenvectors().col(0)[2].real());
	//printf("evec : %f %f %f\n", Evec[0], Evec[1], Evec[2]);


	len = vlength(Evec);
	if (len > 0)
		vscalar(Evec, 1.0f / len);
	if (Eval < 0)
		Eval *= -1.0f;

	return Eval;
}

void Pix::test_print()
{

	V3DF RGB;
	printf("palette size : %d\n", palette_size);
	printf("iteration : %d\n", iteration);

	for (int i = 0; i < palette_size; i++) {
		LABtoRGB(palette[i][0], palette[i][1], palette[i][2], &RGB[0], &RGB[1], &RGB[2]);
		vassign(palette[i], RGB);
		printf("[%d] palette : %f %f %f\n", i, palette[i][0], palette[i][1], palette[i][2]);
	}
}


void Pix::setOutputWH()
{
	int w, h;
	w = getOutputW();
	h = getOutputH();

	cout << "세팅 : " << w << h << endl;

}

void Pix::Iterate()
{
	float err_pal;
	V3DF RGB;

	//시뮬레이티드어닐링
	//피씨에이
	while (1){
		printf("T ==> %f\n", temperature);

		if (converged_flag)																// T값이 수렴했을 경우 반복 종료
			break;

		Update_Superpixel_Mapping();													// input pixel을 다시 superpixel에 할당
		Update_Superpixel_Means();

		Associate_Palette();

		err_pal = Refine_Palette();
		//printf("		err = %f\n", err_pal);
		if (err_pal < kPaletteErrorTolerance) {


			if (temperature <= kTF)														// T값이 수렴한 경우
				converged_flag = true;
			else
				temperature = max2f(temperature*kDT, kTF);								// T * 0.7 

			Expand_Palette();
		}

		//printf("		palette size : %d\n", palette_size);

		iteration++;
	}

	printf("		palette size : %d\n", palette_size);

	printf("palette size : %d\n", palette_size);
	printf("iteration : %d\n", iteration);

	for (int i = 0; i < palette_size; i++) {
		LABtoRGB(palette[i][0], palette[i][1], palette[i][2], &RGB[0], &RGB[1], &RGB[2]);
		vassign(RGB_palette[i], RGB);
		printf("[%d] palette : %f %f %f\n", i, RGB_palette[i][0] * 255.0f, RGB_palette[i][1] * 255.0f, RGB_palette[i][2] * 255.0f);
	}


	for (int i = 0; i < output_w; i++) {
		for (int j = 0; j < output_h; j++) {

			vassign(output_img[i][j], RGB_palette[palette_assign[i][j]]);

		}
	}
}

void Pix::draw_output()
{
	int i, j, idx_x, idx_y;
	V2DI sp;

	for (i = 0; i < input_w; i++) {
		for (j = 0; j < input_h; j++) {

			//vassign(sp, region_map[i][j]);
			//glColor3f(palette[palette_assign[sp[0]][sp[1]]][0], palette[palette_assign[sp[0]][sp[1]]][1], palette[palette_assign[sp[0]][sp[1]]][2]);

			sp[0] = (output_w * i) / input_w;
			sp[1] = (output_h * j) / input_h;

			glColor3fv(output_img[sp[0]][sp[1]]);
			glRecti(i, j, i + 1, j + 1);

		}
	}


	//palette출력을 위한 부분

	//for (int i = 0; i < sub_pair_size; i++) {

	//	glColor3fv(RGB_palette[i]);

	//	idx_x = (i % 4) * 50 + input_w;
	//	idx_y = (i / 4) * 50;
	//	glRecti(idx_x, idx_y, idx_x + 50, idx_y + 50);
	//}


}

#include <fstream>

void Pix::text_output(){
	ofstream outFile("output.txt");
	for (int j = 0; j < output_h; j++){
		for (int i = 0; i < output_w; i++){
			outFile << output_img[i][j][0] << "," << output_img[i][j][1] << "," << output_img[i][j][2] << "/";
		}
		outFile << endl;
	}
}

void Pix::draw_test()
{
	int i, j;
	V2DI sp;
	V3DF RGB;

	for (i = 0; i < input_w; i++) {
		for (j = 0; j < input_h; j++) {


			//sp[0] = (output_w * i) / input_w;
			//sp[1] = (output_h * j) / input_h;
			//
			//LABtoRGB(superpixel_color[sp[0]][sp[1]][0], superpixel_color[sp[0]][sp[1]][1], superpixel_color[sp[0]][sp[1]][2], &RGB[0], &RGB[1], &RGB[2]);
			//glColor3fv(RGB);

			LABtoRGB(superpixel_color[region_map[i][j][0]][region_map[i][j][1]][0]
				, superpixel_color[region_map[i][j][0]][region_map[i][j][1]][1]
				, superpixel_color[region_map[i][j][0]][region_map[i][j][1]][2]
				, &RGB[0], &RGB[1], &RGB[2]);
			glColor3fv(RGB);
			glRecti(i, j, i + 1, j + 1);
		}
	}

	//glColor3f(1.0f, 0.0f, 0.0f);
	//glPointSize(5.0f);
	//glBegin(GL_POINTS);
	//	glVertex3f(15.0f, 15.0f, 1.0f);
	//	glVertex3f(250.0f, 160.0f, 1.0f);
	//	glVertex3f(500.0f, 320.0f, 1.0f);
	//glEnd();
}


int Pix::getPaletteSize()
{
	return max_palette_size;
}

int Pix::getNumberOfBox()
{
	if (input_w < input_h) {
		//output_h = wh;
		return output_h;
	}
	else{
		//output_w = wh;
		return output_w;
	}
}


void Pix::draw_mini()
{
	for (int i = 0; i < output_w; i++)
	{
		for (int j = 0; j < output_h; j++)
		{
			glColor3f(output_img[i][j][0], output_img[i][j][1], output_img[i][j][2]);
			glRecti(i, j, i + 1, j + 1);
		}
	}

}




/////////////////////////////팔레트

void Pix::NearColor(){

	cout << "NearColor" << endl;
	V3DF ColorPalette[18] = {
		{ 0.854f, 0.854f, 0.854f }, { 1.0f, 1.0f, 1.0f }, { 0.862f, 0.152f, 0.086f },
		{ 0.996f, 0.611f, 0.184f }, { 1.0f, 0.929f, 0.003f }, { 0.588f, 0.788f, 0.192f },
		{ 0.082f, 0.082f, 1.0f }, { 0.086f, 0.176f, 0.450f }, { 0.4f, 0.031f, 0.807f },
		{ 0.741f, 0.937f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.996f, 0.776f, 0.819f },
		{ 0.329f, 0.180f, 0.090f }, { 0.662f, 0.376f, 0.090f }, { 1.0f, 0.886f, 0.772f },
		{ 0.172f, 0.698f, 0.172f }, { 0.8f, 0.949f, 0.329f }, { 0.521f, 0.047f, 0.556f } };

	int i, j, k;
	float min = 10000.0f;
	int mink;
	float temp;

	BPPXcolor = new int*[output_w];		//팔레트번호를 BP만한 배열에 할당
	for (int i = 0; i < output_w; i++){
		BPPXcolor[i] = new int[output_h];
	}

	for (i = 0; i < output_w; i++){
		for (j = 0; j < output_h; j++){
			min = 10000.0f;
			for (k = 0; k < 18; k++){
				temp = vlength(output_img[i][j], ColorPalette[k]);
				if (min>temp){
					min = temp;
					mink = k;
				}
			}
			vassign(output_NearPaletteImg[i][j], ColorPalette[mink]);
			BPPXcolor[i][j] = mink;
		}
	}



}

void Pix::draw_output_Palette()
{

	int i, j, idx_x, idx_y;
	V2DI sp;

	for (i = 0; i < input_w; i++) {
		for (j = 0; j < input_h; j++) {

			//vassign(sp, region_map[i][j]);
			//glColor3f(palette[palette_assign[sp[0]][sp[1]]][0], palette[palette_assign[sp[0]][sp[1]]][1], palette[palette_assign[sp[0]][sp[1]]][2]);

			sp[0] = (output_w * i) / input_w;
			sp[1] = (output_h * j) / input_h;

			glColor3fv(output_NearPaletteImg[sp[0]][sp[1]]);
			glRecti(i, j, i + 1, j + 1);

		}
	}
}


int Pix::getOutputW()
{
	return output_w;
}
int Pix::getOutputH()
{
	return output_h;
}
int Pix::getInputW()
{
	return input_w;
}
int Pix::getInputH()
{
	return input_h;
}


int Pix::getOrigOutputW()
{
	return orig_output_w;
}
int Pix::getOrigOutputH()
{
	return orig_output_h;
}


void Pix::setPixOutputWH()
{
	int w = getOutputW();
	int h = getOutputH();

	orig_output_w = w;
	orig_output_h = h;


	if (w % 8 != 0)
	{
		w = (int)(w / 8) * 8;
	}
	if (h % 8 != 0)
	{
		h = (int)(h / 8) * 8;
	}

	//if (w % 4 != 0)
	//{
	//	w = (int)(w / 4) * 4;
	//}
	//if (h % 4 != 0)
	//{
	//	h = (int)(h / 4) * 4;
	//}
	output_w = w;
	output_h = h;

	cout << output_w << " " << output_h << endl;

	V3DF **output_img_temp;


	output_img_temp = (V3DF **)malloc(output_w*sizeof(V3DF*));
	for (int i = 0; i < output_w; i++) {
		output_img_temp[i] = (V3DF *)malloc(output_h*sizeof(V3DF));
		for (int j = 0; j < output_h; j++){
			vector3(output_img_temp[i][j], 0.0f, 0.0f, 0.0f);
			output_img_temp[i][j][0] = output_img[i][j][0];
			output_img_temp[i][j][1] = output_img[i][j][1];
			output_img_temp[i][j][2] = output_img[i][j][2];
		}
	}

	output_img = output_img_temp;


}