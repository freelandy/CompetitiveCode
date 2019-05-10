// ������ DLL �ļ���

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

		this->processor->FeatureExtraction(data, feature); // ��������ȡ����ֱ�Ӽ���Mask�ˣ���Ϊ����������һ��bit plane

		return feature;
	}

	
}