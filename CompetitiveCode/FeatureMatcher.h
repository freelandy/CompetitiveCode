#pragma once
// FeatureMatcher.h

#pragma once

#include "FeatureExtractor.h"
#include "comp_code.h"

using namespace System;
using namespace System::Drawing;

namespace CompetitiveCode {

	public ref class FeatureMatcher
	{
	private:
		comp_code* processor = NULL;

	public:
		FeatureMatcher();
		~FeatureMatcher();

	public:
		double Match(unsigned char* data1, unsigned char* data2);
		double Match(Bitmap^ bitmap1, Bitmap^ bitmap2);
	};
}

