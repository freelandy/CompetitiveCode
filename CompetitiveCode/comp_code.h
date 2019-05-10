#pragma once

#include "math.h"

#define PI 3.1415927

namespace CompetitiveCode
{
	public class comp_code
	{
	private:
		// 滤波器大小
		static const int g_iFilterSize = 35;
		static const int g_iHalfFilterSize = g_iFilterSize / 2;

		// 滤波方向
		static const int g_iOrientation = 6;

		// 滤波起始方向
		static const int g_OriStart = 0;

		// 滤波器的具体数值内容
		double g_pfFilter[g_iOrientation][g_iFilterSize *g_iFilterSize] = {0};

		static const int g_iMaskThreshold = 50;

		// Plane的数目
		static const int g_iPlaneNum = g_iOrientation / 2 + 1;

		// 特征编码的大小
		static const int g_iFeatureSize = (g_iPlaneNum) * 128;

		static const int DISPLACE = 4;

		const int g_piShiftStart[2 * DISPLACE + 1] = { 0, 0, 0, 0, 0, 1, 2, 3, 4 };		// 移位时的开始位置
		const int g_piShiftEnd[2 * DISPLACE + 1] = { 28,29,30,31,32,32,32,32,32 };	// 移位时的结束位置

		const double g_sigma = 4.6;
		const double g_delta = 2.6;

		const int g_BitCounterArray[256] = {	// 根据一个字节的值判断有几个1
			0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8 };


	public:
		void FillGaborFilterAngle(double fSigma, double f2Delta, double fAngle, double* pFilter);
		void FillGaborFilter();
		void FeatureExtraction(unsigned char* pbyImage, unsigned char* pbyFeature);
		float BitMatching(unsigned char* pbyFeature1, unsigned char* pbyFeature2);
		void MaskGenerate(unsigned char* pbyImage, unsigned long* Mask);
	};
}






