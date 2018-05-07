//----------------------
#ifndef _PIX_H_
#define _PIX_H_
//----------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <math.h>
#include <Eigen/Dense>
#include <string.h>

#include "conv_clr.h"
#include "vmg_math.h"

using Eigen::MatrixXd;
using Eigen::MatrixXcd;
using Eigen::EigenSolver;
using Eigen::VectorXcd;

const float kDT = .7f;
const float kTF = 1.0f;
const float kSubclusterPertubation = .8f;
const float kPaletteErrorTolerance = 1.0f;
const float kT0SafteyFactor = 1.1f;


class Pix {


	int output_w, output_h, input_w, input_h, max_palette_size;				// input, output의 크기
	int orig_output_w, orig_output_h;
	int range_;																// 각 슈퍼픽셀에 포함되는 픽셀의 수 (weighting factor)
	V3DF **input_img, **output_img;											// input, output 이미지 //output_img가 픽셀레이션 결과영상..?
	V3DF **output_NearPaletteImg;

	int **palette_assign;													// 각 슈퍼픽셀에 할당된 팔레트 index 저장
	float **input_weights, **superpixel_weights;							// importance map 값

	V2DF **superpixel_pos;													// 각 슈퍼픽셀의 중심
	V3DF **superpixel_color;												// 각 슈퍼픽셀의 색
	V2DI **region_map;														// 각 픽셀이 어떤 슈퍼픽셀에 속하는지 저장
	//V2DI *region_list;

	int prob_c_size;
	int prob_co_size;
	int prob_oc_size;
	int palette_size;


	V3DF *palette;
	V3DF *RGB_palette;
	float **prob_oc;																// P ( output pixel | palette color )
	float **prob_co;																// P ( c_k | p_i )
	float *prob_c;																	// P ( c_k )
	float prob_o;																	// P ( p_i )

	V2DI *sub_superpixel_pairs;
	int sub_pair_size;

	bool *locked_colors;
	int **pixel_constraints;
	int *constraints_size;

	float slic_factor;
	float smooth_pos_factor;
	float temperature;
	float sigma_color, sigma_position;
	bool converged_flag, palette_maxed_flag;


public:

	int iteration;


	void setOutputWH();

	void create(V3DF **cim, int iw, int ih, int resol);
	void initialize();
	void Iterate();

	float GetMaxEigen(int palette_index, V3DF Evec);

	// 입력 영상의 픽셀을 각 슈퍼픽셀에 매핑
	void Update_Superpixel_Mapping();
	// sub superpixel간의 평균색으로 이루어진 palette 생성										
	void GetAveragedPalette(V3DF *avg);

	// 각 슈퍼픽셀의 중심과 대표색을 업데이트
	void Update_Superpixel_Means();
	// laplacian smoothing을 이용하여 중심 위치 스무딩
	void Smooth_Superpixel_Pos();
	// bilateral filter를 이용하여 대표색 스무딩
	void Smooth_Superpixel_Clr();

	// 슈퍼픽셀에 팔레트의 색을 할당
	void Associate_Palette();

	// 슈퍼픽셀의 색을 반영하여 팔레트의 색 재정의
	float Refine_Palette();

	// 팔레트의 색이 분할해야 될 경우 SplitColor()를 불러 분할
	// 만약 최대 팔레트 사이즈에 도달한 경우, flag를 true로 변경하고 Condense_Palette()를 부름
	void Expand_Palette();
	//
	void splitColor(int pair_idx);
	// 팔레트의 sub superpixel을 지우고 하나의 슈퍼픽셀로 각 색을 나타냄
	void Condense_Palette();

	void test_print();

	void draw_test();
	void draw_output();
	void text_output();

	void draw_mini();

	void saveBitmap();

	// bmp로 저장할 때 이름에 필요한 정보를 얻어오기 위함
	int getPaletteSize();
	int getNumberOfBox();

	//픽셀의 색깔을 정해진 팔레트 색상으로 변경함

	//V3DF ColorPalette[18];
	int** BPPXcolor;
	void NearColor();
	void draw_output_Palette();

	int getOutputW();
	int getOutputH();
	void setPixOutputWH();

	int getOrigOutputW();
	int getOrigOutputH();

	int getInputW();
	int getInputH();
};

#endif