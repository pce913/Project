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


	int output_w, output_h, input_w, input_h, max_palette_size;				// input, output�� ũ��
	int orig_output_w, orig_output_h;
	int range_;																// �� �����ȼ��� ���ԵǴ� �ȼ��� �� (weighting factor)
	V3DF **input_img, **output_img;											// input, output �̹��� //output_img�� �ȼ����̼� �������..?
	V3DF **output_NearPaletteImg;

	int **palette_assign;													// �� �����ȼ��� �Ҵ�� �ȷ�Ʈ index ����
	float **input_weights, **superpixel_weights;							// importance map ��

	V2DF **superpixel_pos;													// �� �����ȼ��� �߽�
	V3DF **superpixel_color;												// �� �����ȼ��� ��
	V2DI **region_map;														// �� �ȼ��� � �����ȼ��� ���ϴ��� ����
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

	// �Է� ������ �ȼ��� �� �����ȼ��� ����
	void Update_Superpixel_Mapping();
	// sub superpixel���� ��ջ����� �̷���� palette ����										
	void GetAveragedPalette(V3DF *avg);

	// �� �����ȼ��� �߽ɰ� ��ǥ���� ������Ʈ
	void Update_Superpixel_Means();
	// laplacian smoothing�� �̿��Ͽ� �߽� ��ġ ������
	void Smooth_Superpixel_Pos();
	// bilateral filter�� �̿��Ͽ� ��ǥ�� ������
	void Smooth_Superpixel_Clr();

	// �����ȼ��� �ȷ�Ʈ�� ���� �Ҵ�
	void Associate_Palette();

	// �����ȼ��� ���� �ݿ��Ͽ� �ȷ�Ʈ�� �� ������
	float Refine_Palette();

	// �ȷ�Ʈ�� ���� �����ؾ� �� ��� SplitColor()�� �ҷ� ����
	// ���� �ִ� �ȷ�Ʈ ����� ������ ���, flag�� true�� �����ϰ� Condense_Palette()�� �θ�
	void Expand_Palette();
	//
	void splitColor(int pair_idx);
	// �ȷ�Ʈ�� sub superpixel�� ����� �ϳ��� �����ȼ��� �� ���� ��Ÿ��
	void Condense_Palette();

	void test_print();

	void draw_test();
	void draw_output();
	void text_output();

	void draw_mini();

	void saveBitmap();

	// bmp�� ������ �� �̸��� �ʿ��� ������ ������ ����
	int getPaletteSize();
	int getNumberOfBox();

	//�ȼ��� ������ ������ �ȷ�Ʈ �������� ������

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