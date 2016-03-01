#pragma once
#include <msclr/marshal_cppstd.h>
#include "opencv2/opencv.hpp"
#include "CvDefinitions.h"
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
		static OpenCvClr::CvImage^ Threshold(CvImage^ inputImage, int threshold);

		/// <summary>
		/// 平滑化
		/// </summary>
		/// <param name="position">入力画像</param>
		/// <param name="smoothType">平滑化の種類</param>
		/// <param name="filterX">フィルタサイズ（水平方向）</param>
		/// <param name="filterY">フィルタサイズ（垂直方向）</param>
		/// <param name="sigma1">シグマ値１</param>
		/// <param name="sigma2">シグマ値２</param>
		static OpenCvClr::CvImage^ Smooth(CvImage^ inputImage, CvSmoothType smoothType, int filterX, int filterY, double sigma1, double sigma2);
	};
}
