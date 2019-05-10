// 这是主 DLL 文件。

#include "stdafx.h"
#include "FeatureExtractor.h"

namespace CompetitiveCode
{
	
	FeatureExtractor::FeatureExtractor()
	{
		this->processor = new comp_code();
		this->processor->FillGaborFilter();
	}

	FeatureExtractor::~FeatureExtractor()
	{
		if (this->processor != NULL)
		{
			delete this->processor;
			this->processor = NULL;
		}
	}

	void FeatureExtractor::FillFilters()
	{
		//this->processor->FillGaborFilter();
	}


	void FeatureExtractor::ReleaseFilters()
	{

	}


	unsigned char* FeatureExtractor::Extract(Bitmap^ bitmap)
	{
		unsigned char* data = Utils::Bitmap2Data(bitmap);
		unsigned char* feature = new unsigned char[512];

		this->processor->FeatureExtraction(data, feature); // 在特征提取里面直接计算Mask了，作为最终特征的一个bit plane

		return feature;
	}

	
}