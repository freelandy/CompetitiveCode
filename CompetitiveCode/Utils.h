#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

namespace CompetitiveCode
{
	public ref class Utils
	{
	public:
		Utils();

	public:
		static unsigned char* Bitmap2Data(Bitmap^ bmp);
		static Bitmap^ Data2Bitmap(int width, int height, unsigned char* data);
	};
}

