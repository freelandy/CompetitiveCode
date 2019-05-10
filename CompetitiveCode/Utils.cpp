#include "stdafx.h"
#include "Utils.h"

namespace CompetitiveCode
{
	Utils::Utils()
	{
	}

	unsigned char* Utils::Bitmap2Data(Bitmap^ bmp)
	{
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
		BitmapData^ bmpData = bmp->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat);
		unsigned char* pData = (unsigned char*)bmpData->Scan0.ToPointer();

		bmp->UnlockBits(bmpData);

		return pData;
	}

	Bitmap^ Utils::Data2Bitmap(int width, int height, unsigned char* data)
	{
		System::Drawing::Bitmap^ bmp = gcnew Bitmap(width,height,
													width,
													System::Drawing::Imaging::PixelFormat::Format8bppIndexed,
													(System::IntPtr)data);

		return bmp;
	}

	
}