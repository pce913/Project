//	dir.h

//----------------------
#ifndef _DIR_H_
#define _DIR_H_
//----------------------

#include "Image.h"
#include "conv_clr.h"
#include "common_func.h"

#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define PI 3.141592653589793238462643383279 
#define POSITIVE	1
#define NEGATIVE	0

class FlowPath{
public:
	int sn;	// s 방향 개수
	V3DF *Alpha;
	int tn;	// t 방향 개수
	V3DF *Beta;
	V3DF *AlphaMax;	// Alpha -> BetaMax로 옮긴 위치들

	bool is_silhouette;	// silhouette 인지
	float importance;	// 얼만큼 중요한 stream 인지

	// for vectorization
	V3DF BBox[2];
	float skltn, cl;
	float length;
	float nlength;	// normalized length
	//	curvature 계산에 필요한 자료구조
	float tcurv;	//	threshold curvature: negative 방향과 positive 방향으로 tolerable한 curvature 설정
	float *curv;	//	모든 pixel에서 계산한 curvature
	V2DI *crange;	//	negative 방향으로 tolerable한 curvature를 가진 pixel의 index ~ positive 방향으로의 index
	int selected_segment;	// selected index; 이 index를 기준으로 +,- 방향 crange[selected_segment][] 결정

	FlowPath(){
		sn = tn = 0;
		Alpha = NULL;
		Beta = NULL;
		AlphaMax = NULL;
		is_silhouette = false;	importance = 0.0f;

		skltn = cl = length = nlength = 0.0f;
		tcurv = 0;	curv = NULL;	crange = NULL;	selected_segment = 0;
	}
	~FlowPath(){
		if (sn>0)	delete[] Alpha;
		if (tn>0)	delete[] Beta;
		if (!AlphaMax)	delete[] AlphaMax;
		if (curv)	delete[] curv;
		if (crange)	delete[] crange;
	}
	void Init(){
		if (!Alpha)	delete[] Alpha;
		if (!Beta)	delete[] Beta;
		if (!AlphaMax)	delete[] AlphaMax;
		Alpha = NULL;		Beta = NULL;	AlphaMax = NULL;
		sn = tn = 0;
		is_silhouette = false;	importance = 0.0f;

		skltn = cl = length = nlength = 0.0f;
		tcurv = 0;
		if (curv)	delete[] curv;	curv = NULL;
		if (crange)	delete[] crange;	crange = NULL;
		selected_segment = 0;
	}
	void InitShallow(){
		sn = tn = 0;
		is_silhouette = false;	importance = 0.0f;
		skltn = cl = length = nlength = 0.0f;
		tcurv = 0;	selected_segment = 0;
	}
	void get_length(){
		int i;
		this->length = 0.0f;

		for (i = 0; i < this->sn - 1; i++)
			this->length += pdist(this->Alpha[i], this->Alpha[i + 1]);
	}
	void Copy(FlowPath *p){
		Init();

		int i;
		sn = p->sn;
		if (sn>0){
			Alpha = new V3DF[sn];
			for (i = 0; i<sn; i++)	vcopy(Alpha[i], p->Alpha[i]);
		}

		tn = p->tn;
		if (tn>0){
			Beta = new V3DF[tn];
			for (i = 0; i<tn; i++)	vcopy(Beta[i], p->Beta[i]);
		}
	}
};


class DistInfo{
public:
	int f_idx;		// 픽셀과 가장 가까운 flow의 index
	int p_idx;		// flow의 몇 번째 point인지
	float arc;		// arclength. flow에서 어느 위치와 가까운 지

	int dist;		// 픽셀~flow 사이 거리
	float dist_arc;	// dist / max dist (0 - 1)
	V3DF direction;	// flow의 방향( p[p_idx+1] - p[p_idx-1] )

	DistInfo(){
		f_idx = -1;
		p_idx = -1;
		arc = -1.0f;
		dist = INFINITY;
		dist_arc = INFINITY;
		vzero(direction);
	}
	~DistInfo(){}
	void Init(){
		f_idx = -1;
		p_idx = -1;
		arc = -1.0f;
		dist = INFINITY;
		dist_arc = INFINITY;
		vzero(direction);
	}
	void Set(int f_idx_, int p_idx_, float arc_, int dist_, V3DF direction_){
		f_idx = f_idx_;	p_idx = p_idx_; arc = arc_;	dist = dist_;
		vcopy(direction, direction_);
	}
	void Set_Dist_arc(float maxdist){
		if (dist == INFINITY)	dist_arc = 1.0f;
		else					dist_arc = dist / maxdist;
	}
};

class DistInfoSet{
public:
	DistInfo dinfo[3];	// 0: 가장가까운 flow, 1: 다음으로 가까운 CL, 다음으로 가까운 CL

	DistInfoSet(){}
	~DistInfoSet(){}
	void Copy(int dest, int src){
		dinfo[dest] = dinfo[src];
	}
	void Set(int idx, int f_idx_, int p_idx_, float arc_, int dist_, V3DF direction_){
		dinfo[idx].Set(f_idx_, p_idx_, arc_, dist_, direction_);
	}
	void Set(int idx, DistInfo dinfo_){
		dinfo[idx] = dinfo_;
		vcopy(dinfo[idx].direction, dinfo_.direction);
	}
	void Init(){
		dinfo[0].Init();	dinfo[1].Init();	dinfo[2].Init();
	}
};

class SeedInfo{
public:
	int sid;				//seed id(0~)
	float dist;				// distance from seed
	float dist_arc;			// dist / max dist (0 - 1)
	float dist_by_seed_grad;		// dist_arc / gradient+1

	V3DF dir;		// seed로 부터 전파되어온 방향
	float BetaMaxGradMag;	// seed로 부터 전파되어온 gradient 크기 (0~1)
	// [임시] 단, gradient 방향에서 최대 크기를 저장함[
	int sx, sy;		// 전파되어온 seed 좌표
	bool isseed;
	bool isoutside;	// imCL 중 바깥에 있는 것인가

	SeedInfo(){
		sid = -1.0f;
		dist = 9999999;
		dist_arc = 1.0f;
		dist_by_seed_grad = 1.0f;
		BetaMaxGradMag = 0.0f;
		sx = sy = 0.0f;
		isseed = false;
		isoutside = false;
	}
	void Init(){
		sid = -1.0f;
		dist = 9999999;
		dist_arc = 1.0f;
		dist_by_seed_grad = 1.0f;
		BetaMaxGradMag = 0.0f;
		sx = sy = 0.0f;
		isseed = false;
		isoutside = false;
	}
	void Set(int sid_, float d, V3DF dir_,
		float grad_, int sx_, int sy_){
		sid = sid_;	dist = d;	vcopy(dir, dir_);	BetaMaxGradMag = grad_;
		sx = sx_;	sy = sy_;
	}
	void Update(int new_sid, int new_dist){
		if (new_dist<dist){
			dist = new_dist;
			sid = new_sid;
		}
	}
};

class Direction : public Image{   // Image class를 상속한다는 의미
	float grad_thr;
	float cl_tanh_he_thr;
	int cl_itr;
	int n_quant;

	V3DF **etf;
	V3DF **grad;
	V3DF **tangent;
	float **oldim;	//반복위해
	float **imCL;

	FlowPath **fpath;
	int threshold_S, threshold_T;	// (홀수!) S,T 거리(pixel 거리)(50정도)	==> sigma로 대체하는 게 맞는 듯.
	float SigmaM, SigmaC, P;
	// for vectorization
	int nVPath;
	int n_qlist;	// The # of final Streams
	FlowPath **vpath;
	int **skltn;
	bool StreamsExisting;		// Stream이 존재 하는지
	V3DI *qlist;
	V3DI *rlist;	//sorted qlist(vectorized flow의 시작점, vectorized flow는 Streams[rlist[i][0]][rlist[i][1]]에 있음)

	DistInfoSet **dmap;
	float **amap;

	SeedInfo **dmap_fdir;	// fidr을 전파시키는 용도 & feature로부터 거리, seed 정보 저장. multi role
	float maxdist;
	float **qtdir;	// quantized tdir
	float **tang_b;	// quantized dir 의 하한값 (-1.0 : 없음)
	float **tang_t;	// quantized dir 의 상한값 (-1.0 : 없음)
	float **wei_b;	// tang_b에 적용되는 weight. tone dir = wei_b*tang_b + (1-wei_b)*tang_t

	float **diffAng;	// 이웃들이 각도 차이 나는 곳
	float **diffGrad;	// diffAng의 gradient

	// direction
	V3DF **fdir;
	V3DF **fdirFortdir;	// 얇은거
	V3DF **tdir;

	void NewMem(){
		int i;
		etf = new V3DF *[MAX_X];
		grad = new V3DF *[MAX_X];
		tangent = new V3DF *[MAX_X];
		res_dir = new V3DF *[MAX_X];
		imCL = new float *[MAX_X];
		for (i = 0; i<MAX_X; i++){
			etf[i] = new V3DF[MAX_Y];
			grad[i] = new V3DF[MAX_Y];
			tangent[i] = new V3DF[MAX_Y];
			res_dir[i] = new V3DF[MAX_Y];
			imCL[i] = new float[MAX_Y];
		}
	}
	void GetGrad();
	void GetGradient(int MaskSize, float **img, float **ang);
	void GetTangent();
	void GetETF(int nbhd = 5);
	void GetAvg(V3DF **flow);
	void GetAvg(float **flow);

	void preprocessVpath();
	void SetFlowPath();	// 모든 픽셀에서 S(etf), T(gradient) 방향 경로 계산
	//--\\||//--\\||//--\\||//--\\||//--\\||//--\\||/||//
	//<--------------------------------------------------->|//
	//|	Method Name:
	//|	==========
	//|					*	SetFlowAtPoint	*
	//<--------------------------------------------------->|//
	//|	Description:
	//|	==========
	//|	점 (px,py)에서 flow 따라 간 점의 위치(-S ~ +S)
	//|	
	//|	input
	//|		(px,py): 시작 점
	//|		aP,aN: +S, -S 방향 점의 개수
	//|		alpha: +S, -S 방향 점
	//|
	//|	output
	//|		aP,aN
	//|		alpha
	//<--------------------------------------------------->|//
	//--\\||//--\\||//--\\||//--\\||//--\\||//--\\||/||//
	void SetFlowAtPointS(int px, int py, int *nPoints, V3DF *Alpha);
	void SetFlowAtPointT(int px, int py, int *nPoints, V3DF *Beta);					// gradient 방향의 선분 찾기
	//--\\||//--\\||//--\\||//--\\||//--\\||//--\\||/||//
	//<--------------------------------------------------->|//
	//|	Method Name:
	//|	==========
	//|					*	GetETFAtPoint	*
	//<--------------------------------------------------->|//
	//|	Description:
	//|	==========
	//|	점 (px,py)에서 etf를 계산하여 리턴한다.
	//|	보간법 이용 'Lagrangian multiplier'
	//|	
	//|	input
	//|		(px,py): float
	//|		resETF: 해당 위치에서의 etf
	//|
	//|	output
	//|		resETF
	//<--------------------------------------------------->|//
	//--\\||//--\\||//--\\||//--\\||//--\\||//--\\||/||//
	void GetETFAtPoint(float px, float py, V3DF resETF);
	void GetETFAtPoint(float px, float py, V3DF resETF, V3DF preDir);
	void SetCoherentLine();

	// for vectorization
	void SetVectorPath();		// PushStream() (교수님 주신 코드에서 함수명)
	void VectorizeVectorPath();	// load_CL()
	void SetFlowAtPointS4Vectorization(int px, int py, int *nPoints, V3DF *Alpha);	// flow 따르다가 coherent line이 아니면 멈춘다
	int n_slist;	V3DI *slist;
	int n_plist;	V3DI *plist;
	void build_skltn();
	void compute_center_line();
	void compute_center_line(int px, int py);
	void build_center_line1();
	int max_stream(int px, int py);
	void build_center_line2();
	int close_stream(int nbhd_idx, int **nbhd_board, int px, int py, int qx, int qy, int dist);
	void sort_length();
	//	curvature 계산하는 함수	
	void compute_curv(int x, int y);
	void curv_line();
	//	curvature 계산하는 함수	

	void SetUniDir();
	// for alpha map
	void DmapFor3Files();	// build_distmap()
	// for alpha map
	void DmapFor3Files(int idx, DistInfoSet **dmap, DistInfo **tdmap);
	void DoAmap(DistInfoSet **dmap);		// ComputeAlpha()
	void DoFdir(DistInfoSet **dmap);


	void DoTdirOption();
	void NewDir();
	void DoDmap(SeedInfo **dmap, V3DF **InSeeds, V3DF **OutDir);
	void DoTdirQ(int **quantization_n/*나눌 등분 수*/, V3DF **idir/*Quantize에 참조할 방향*/, float **odir);
	void CorrectTdir(int **quantization_n, float **idir);	// 급격히 변하는 곳의 방향 수정

	void Set_res_dir();

public:
	V3DF **res_dir;	// 최종 방향 저장되는 곳

	Direction(){
		etf = grad = tangent = NULL;
		oldim = imCL = NULL;
		fpath = NULL;
		vpath = NULL;
		skltn = NULL;
		StreamsExisting = true;
		qlist = rlist = NULL;
		dmap = NULL;
		amap = NULL;

		dmap_fdir = NULL;
		qtdir = NULL;
		tang_b = tang_t = wei_b = NULL;
		diffAng = diffGrad = NULL;

		fdir = fdirFortdir = tdir = NULL;

		threshold_S = 21;	//11; 21;
		threshold_T = 11;	//5; 11;
		SigmaM = 7.0f;	//default:3.0	// line coherence
		SigmaC = 1.0f;	//default:1.0	// line width
		P = 0.99f;
		n_qlist = 0;

		res_dir = NULL;
	}
	~Direction(){
		int i;
		if (etf){
			for (i = 0; i<MAX_X; i++)	delete[] etf[i];	delete etf;
		}
		if (grad){
			for (i = 0; i<MAX_X; i++)	delete[] grad[i];	delete grad;
		}
		if (tangent){
			for (i = 0; i<MAX_X; i++)	delete[] tangent[i];	delete tangent;
		}
		if (oldim){
			for (i = 0; i<MAX_X; i++)	delete[] oldim[i];	delete oldim;
		}
		if (imCL){
			for (i = 0; i<MAX_X; i++)	delete[] imCL[i];	delete imCL;
		}
		if (fpath){
			for (i = 0; i<MAX_X; i++)	delete[] fpath[i];	delete fpath;
		}
		if (vpath){
			for (i = 0; i<MAX_X; i++)	delete[] vpath[i];	delete vpath;
		}
		if (skltn){
			for (i = 0; i<MAX_X; i++)	delete[] skltn[i];	delete skltn;
		}
		delete[] qlist;	delete[] rlist;
		if (dmap){
			for (i = 0; i<MAX_X; i++)	delete[] dmap[i];	delete dmap;
		}
		if (amap){
			for (i = 0; i<MAX_X; i++)	delete[] amap[i];	delete amap;
		}
		if (dmap_fdir){
			for (i = 0; i<MAX_X; i++)	delete[] dmap_fdir[i];	delete dmap_fdir;
		}
		if (qtdir){
			for (i = 0; i<MAX_X; i++)	delete[] qtdir[i];	delete qtdir;
		}
		if (tang_b){
			for (i = 0; i<MAX_X; i++)	delete[] tang_b[i];	delete tang_b;
		}
		if (tang_t){
			for (i = 0; i<MAX_X; i++)	delete[] tang_t[i];	delete tang_t;
		}
		if (wei_b){
			for (i = 0; i<MAX_X; i++)	delete[] wei_b[i];	delete wei_b;
		}
		if (diffAng){
			for (i = 0; i<MAX_X; i++)	delete[] diffAng[i];	delete diffAng;
		}
		if (diffGrad){
			for (i = 0; i<MAX_X; i++)	delete[] diffGrad[i];	delete diffGrad;
		}

		if (fdir){
			for (i = 0; i<MAX_X; i++)	delete[] fdir[i];	delete fdir;
		}
		if (fdirFortdir){
			for (i = 0; i<MAX_X; i++)	delete[] fdirFortdir[i];	delete fdirFortdir;
		}
		if (tdir){
			for (i = 0; i<MAX_X; i++)	delete[] tdir[i];	delete tdir;
		}

		if (res_dir){
			for (i = 0; i<MAX_X; i++)	delete[] res_dir[i];	delete res_dir;
		}
	}
	void GetDir(int dir_n_quantize = 20,	// 작을 수록 방향을 quantization
		float grad_thr_ = 0.0f,				// 이하인 gradient 는 무시
		float cl_tanh_he_thr_ = 0.998f, int cl_itr_ = 3);	// coherent line 관련

	void Draw(V3DF **vct, V3DF clr);
	void Draw_clr(V3DF **vct);
};
//------------------
#endif
//------------------