#pragma once

#include "math.h"

#define PI 3.1415927

namespace CompetitiveCode
{
	public class comp_code
	{
	private:
		// �˲�����С
		static const int g_iFilterSize = 35;
		static const int g_iHalfFilterSize = g_iFilterSize / 2;

		// �˲�����
		static const int g_iOrientation = 6;

		// �˲���ʼ����
		static const int g_OriStart = 0;

		// �˲����ľ�����ֵ����
		double g_pfFilter[g_iOrientation][g_iFilterSize *g_iFilterSize] = {0};

		static const int g_iMaskThreshold = 50;

		// Plane����Ŀ
		static const int g_iPlaneNum = g_iOrientation / 2 + 1;

		// ��������Ĵ�С
		static const int g_iFeatureSize = (g_iPlaneNum) * 128;

		static const int DISPLACE = 4;

		const int g_piShiftStart[2 * DISPLACE + 1] = { 0, 0, 0, 0, 0, 1, 2, 3, 4 };		// ��λʱ�Ŀ�ʼλ��
		const int g_piShiftEnd[2 * DISPLACE + 1] = { 28,29,30,31,32,32,32,32,32 };	// ��λʱ�Ľ���λ��

		const double g_sigma = 4.6;
		const double g_delta = 2.6;

		const int g_BitCounterArray[256] = {	// ����һ���ֽڵ�ֵ�ж��м���1
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






