// FeatureExtractor.h

#pragma once

#include "utils.h"
#include "comp_code.h"

using namespace System;
using namespace System::Drawing;

#define PI 3.1415927

namespace CompetitiveCode 
{

	public ref class FeatureExtractor
	{
	private:
		comp_code* processor = NULL;

	public:
		FeatureExtractor();
		~FeatureExtractor();

	public:
		void FillFilters();
		void ReleaseFilters();
		unsigned char* Extract(Bitmap^ bitmap);
	};
}
