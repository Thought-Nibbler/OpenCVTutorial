// OpenCvClr.h

#pragma once
#include <msclr/marshal_cppstd.h>
#include "opencv2/opencv.hpp"
#include "CvImage.h"

using namespace System;
using namespace System::Drawing;

namespace OpenCvClr 
{
	/// <summary>
	/// OpenCV�ɂ��摜�������[�e�B���e�B
	/// </summary>
	public ref class CvImgProc
	{
	private:
	public:
		/// <summary>
		/// �������l�ɂ���l�摜�̍쐬
		/// </summary>
		/// <param name="position">���͉摜</param>
		/// <param name="threshold">�������l�i0-255�j</param>
		static OpenCvClr::CvImage^ CvThreshold(CvImage^ inputImage, int threshold);

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="position">���͉摜</param>
		static OpenCvClr::CvImage^ CvSmooth(CvImage^ inputImage);
	};
}
