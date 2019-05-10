#include "stdafx.h"
#include "FeatureMatcher.h"


namespace CompetitiveCode
{
	FeatureMatcher::FeatureMatcher()
	{
		this->processor = new comp_code();
		this->processor->FillGaborFilter();
	}

	FeatureMatcher::~FeatureMatcher()
	{
		if (this->processor != NULL)
		{
			delete this->processor;
			this->processor = NULL;
		}
	}


	double FeatureMatcher::Match(unsigned char* feature1, unsigned char* feature2)
	{
		return this->processor->BitMatching(feature1, feature2);
	}

	double FeatureMatcher::Match(Bitmap^ bitmap1, Bitmap^ bitmap2)
	{
		unsigned char* data1 = Utils::Bitmap2Data(bitmap1);
		unsigned char* data2 = Utils::Bitmap2Data(bitmap2);

		unsigned char* feature1 = new unsigned char[512];
		unsigned char* feature2 = new unsigned char[512];

		this->processor->FeatureExtraction(data1, feature1);
		this->processor->FeatureExtraction(data2, feature2);

		double d = Match(feature1, feature2);

		delete feature1;
		delete feature2;
		feature1 = NULL;
		feature2 = NULL;

		return d;
	}
}
