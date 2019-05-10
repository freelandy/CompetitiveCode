#include "Stdafx.h"
#include "comp_code.h"


namespace CompetitiveCode
{

	/*

	*/
	void comp_code::FillGaborFilterAngle(double fSigma, double f2Delta, double fAngle, double* pFilter)
	{
		const double _2ln2 = sqrt(2 * log(2));
		double fK = _2ln2 * (f2Delta + 1) / (f2Delta - 1);
		double fW0 = fK / fSigma;
		double fFactor1 = -fW0 / (sqrt(2 * PI) * fK);
		double fFactor2 = -(fW0*fW0) / (8 * fK*fK);
		double fSin = sin(fAngle);
		double fCos = cos(fAngle);

		double fTemp;
		double x, y, x1, y1;

		double fSum = 0;
		int i, j;

		for (i = 0; i < g_iFilterSize; i++)
		{
			x = i - g_iHalfFilterSize;

			for (j = 0; j < g_iFilterSize; j++)
			{
				y = j - g_iHalfFilterSize;
				x1 = x*fCos + y*fSin;
				y1 = y*fCos - x*fSin;
				fTemp = fFactor1 * exp(fFactor2*(4 * x1*x1 + y1*y1));

				pFilter[i*g_iFilterSize + j] = 1 * fTemp * cos(fW0*x*fCos + fW0*y*fSin);

				fSum += pFilter[i*g_iFilterSize + j];
			}
		}


		double fMean = fSum / g_iFilterSize / g_iFilterSize;

		for (i = 0; i < g_iFilterSize; i++)
		{
			for (j = 0; j < g_iFilterSize; j++)
			{
				pFilter[i*g_iFilterSize + j] -= fMean;
			}
		}
	}


	/*

	*/
	void comp_code::FillGaborFilter()
	{
		double fAngle;
		int i;

		for (i = 0; i < g_iOrientation; i++)
		{
			fAngle = PI*i / g_iOrientation + PI*g_OriStart / 180;
			FillGaborFilterAngle(g_sigma, g_delta, fAngle, g_pfFilter[i]);
		}
	}


	//**************************************************************************************

	// Use six Gabor filters to generate Competitive Coding

	//*************************************************************************************
	void comp_code::FeatureExtraction(unsigned char* pbyImage, unsigned char* pbyFeature)
	{
		int step = 3;
		double A[6] = { 0,0,0,0,0,0 };
		double AMin[6] = { 0,0,0,0,0,0 };
		int filtersize = g_iFilterSize;
		int halffilter = filtersize / 2;
		double Max, Temp;
		int ix = 0;
		int iy = 0, indexMax, i, j, x, y, k;
		int imageSize = 128;

		unsigned long int me = 1;
		unsigned long int mc = 0;


		int T1, T2, T3, T4;
		for (i = 1; i <= 31; i++)
		{
			me = me << 1;
		}

		mc = me;

		unsigned long* Bit0 = (unsigned long*)(pbyFeature + 128 * 0);
		unsigned long* Bit1 = (unsigned long*)(pbyFeature + 128 * 1);
		unsigned long* Bit2 = (unsigned long*)(pbyFeature + 128 * 2);
		unsigned long* Bit3 = (unsigned long*)(pbyFeature + 128 * 3);

		MaskGenerate(pbyImage, Bit3);

		for (i = halffilter; i < imageSize - halffilter; i = i + step)
		{
			me = mc;
			iy = 0;

			Bit0[ix] = 0;
			Bit1[ix] = 0;
			Bit2[ix] = 0;

			for (j = halffilter; j < imageSize - halffilter; j = j + step)
			{
				A[0] = 0;
				A[1] = 0;
				A[2] = 0;
				A[3] = 0;
				A[4] = 0;
				A[5] = 0;


				for (x = -halffilter; x <= halffilter; x++)
				{
					T3 = i + x;
					T4 = (x + halffilter)*filtersize + halffilter;

					for (y = -halffilter; y <= halffilter; y++)
					{
						T1 = j + y;
						T2 = T4 + y;

						A[0] += pbyImage[T3 * 128 + T1] * g_pfFilter[0][T2];
						A[1] += pbyImage[T3 * 128 + T1] * g_pfFilter[1][T2];
						A[2] += pbyImage[T3 * 128 + T1] * g_pfFilter[2][T2];
						A[3] += pbyImage[T3 * 128 + T1] * g_pfFilter[3][T2];
						A[4] += pbyImage[T3 * 128 + T1] * g_pfFilter[4][T2];
						A[5] += pbyImage[T3 * 128 + T1] * g_pfFilter[5][T2];
					}
				}


				Max = A[0];
				indexMax = 0;

				for (k = 1; k < g_iOrientation; k++)
				{
					Temp = A[k];

					if (Temp > Max)
					{
						Max = Temp;
						indexMax = k;
					}
				}


				switch (indexMax)
				{
				case 1:
					Bit0[ix] = Bit0[ix] | me;
					break;

				case 2:
					Bit1[ix] = Bit1[ix] | me;
					Bit0[ix] = Bit0[ix] | me;
					break;

				case 3:
					Bit2[ix] = Bit2[ix] | me;
					Bit1[ix] = Bit1[ix] | me;
					Bit0[ix] = Bit0[ix] | me;
					break;

				case 4:
					Bit2[ix] = Bit2[ix] | me;
					Bit1[ix] = Bit1[ix] | me;
					break;

				case 5:
					Bit2[ix] = Bit2[ix] | me;
					break;

				default:
					break;
				}

				me = me >> 1;
				iy++;
			}
			ix++;
		}
	}



	float comp_code::BitMatching(unsigned char* pbyFeature1, unsigned char* pbyFeature2)
	{
		unsigned long Plane[g_iPlaneNum];
		int count = 0, Total = 0;
		int i;
		float Tmin;
		int startx = 0, endx = 0, shiftx, shifty, index, Nshifty;

		unsigned int Me2 = 1;
		unsigned long Me = 255, Mask;

		bool result = true;
		int iFeaturePlaneNum = g_iOrientation / 2;;
		float minScore = (float)iFeaturePlaneNum;
		int iMask;

		unsigned long* BitPlane_0S[g_iPlaneNum];
		unsigned long* BitPlane_MS = (unsigned long*)(pbyFeature1 + 128 * iFeaturePlaneNum);
		unsigned long* BitPlane_0D[g_iPlaneNum];
		unsigned long* BitPlane_MD = (unsigned long*)(pbyFeature2 + 128 * iFeaturePlaneNum);

		for (iMask = 0; iMask < iFeaturePlaneNum; iMask++)
		{
			BitPlane_0S[iMask] = (unsigned long*)(pbyFeature1 + 128 * iMask);
			BitPlane_0D[iMask] = (unsigned long*)(pbyFeature2 + 128 * iMask);
		}

		for (shiftx = -DISPLACE; shiftx <= DISPLACE; shiftx++)
		{
			for (shifty = -DISPLACE; shifty <= DISPLACE; shifty++)
			{
				Total = 0;
				count = 0;

				for (i = g_piShiftStart[shiftx + DISPLACE]; i < g_piShiftEnd[shiftx + DISPLACE]; i++)
				{
					index = i - shiftx;
					if (shifty >= 0)
					{
						for (iMask = 0; iMask < iFeaturePlaneNum; iMask++)
						{
							Plane[iMask] = (BitPlane_0S[iMask][i] ^ (BitPlane_0D[iMask][index] >> shifty));
						}

						Mask = BitPlane_MS[i] & (BitPlane_MD[index] >> shifty);
					}
					else
					{
						Nshifty = shifty*-1;
						for (iMask = 0; iMask < iFeaturePlaneNum; iMask++)
						{
							Plane[iMask] = (BitPlane_0S[iMask][i] ^ (BitPlane_0D[iMask][index] << Nshifty));
						}
						Mask = BitPlane_MS[i] & (BitPlane_MD[index] << Nshifty);
					}

					Total = Total + g_BitCounterArray[Mask&Me] + g_BitCounterArray[(Mask >> 8)&Me] + g_BitCounterArray[(Mask >> 16)&Me] + g_BitCounterArray[(Mask >> 24)&Me];
					for (iMask = 0; iMask < iFeaturePlaneNum; iMask++)
					{
						count = count + g_BitCounterArray[Plane[iMask] & Me&Mask] + g_BitCounterArray[(Plane[iMask] >> 8)&Me&(Mask >> 8)] + g_BitCounterArray[(Plane[iMask] >> 16)&Me&(Mask >> 16)] + g_BitCounterArray[(Plane[iMask] >> 24)&Me&(Mask >> 24)];
					}
				}

				Tmin = (float)(count) / (float)Total;
				if (Tmin < minScore)
				{
					minScore = Tmin;
				}

			} // end shifty		   

		} // end shiftx 

		return minScore / iFeaturePlaneNum;
	}


	/*

	*/
	void comp_code::MaskGenerate(unsigned char* pbyImage, unsigned long* Mask)
	{
		int ij, j, x, y, ix, iy;
		unsigned long OneBit = (unsigned long)1 << 31;
		unsigned long OneGenerator = OneBit;

		int backcount = 0;
		ix = 0;
		iy = 0;

		for (ij = 17; ij < 128 - 17; ij = ij + 3)
		{
			OneGenerator = OneBit;
			Mask[ix] = 0;
			iy = 0;

			for (j = 17; j < 128 - 17; j = j + 3)
			{
				backcount = 0;
				for (x = -17; x <= 16; x++)
				{
					for (y = -17; y <= 16; y++)
					{
						if (pbyImage[(ij + x) * 128 + (j + y)] < g_iMaskThreshold)
						{
							backcount++;
						}
					}
				}

				if (backcount < 60)
				{
					Mask[ix] |= OneGenerator;
				}

				OneGenerator >>= 1;
			}

			ix++;
		}
	}
}