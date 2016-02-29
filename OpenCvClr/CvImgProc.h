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
	/// OpenCVによる画像処理ユーティリティ
	/// </summary>
	public ref class CvImgProc
	{
	private:
	public:
		/// <summary>
		/// しきい値による二値画像の作成
		/// </summary>
		/// <param name="position">入力画像</param>
		/// <param name="threshold">しきい値（0-255）</param>
		static OpenCvClr::CvImage^ CvThreshold(CvImage^ inputImage, int threshold);

		/// <summary>
		/// 平滑化
		/// </summary>
		/// <param name="position">入力画像</param>
		static OpenCvClr::CvImage^ CvSmooth(CvImage^ inputImage);
	};
}
