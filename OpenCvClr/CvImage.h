#pragma once

#include <msclr/marshal_cppstd.h>
#include "opencv2/opencv.hpp"

using namespace System;
using namespace System::Drawing;


namespace OpenCvClr
{
	/// <summary>
	/// C#側で処理対象となる画像オブジェクト
	/// </summary>
	public ref class CvImage
	{
	private:
		/// <summary>
		/// 処理結果画像データの保持領域
		/// </summary>
		uchar *ImageData;

		/// <summary>
		/// 処理結果画像データの保持領域（IntPtr）
		/// </summary>
		System::IntPtr ImageDataPtr;

		/// <summary>
		/// 処理結果画像データのオブジェクト
		/// </summary>
		System::Drawing::Bitmap^ ImageBitmap;

		/// <summary>
		/// メンバ初期化（コンストラクタで呼び出される）
		/// </summary>
		void Initialize();

	public:
		/// <summary>
		/// 画像の幅
		/// </summary>
		int width;

		/// <summary>
		/// 画像の高さ
		/// </summary>
		int height;

		/// <summary>
		/// 処理対象の画像
		/// </summary>
		IplImage *Image;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="width">作成画像幅</param>
		/// <param name="height">作成画像高さ</param>
		CvImage(int width, int height);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="filename">入力ファイル名</param>
		CvImage(String ^filename);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~CvImage();

		/// <summary>
		/// 画素設定
		/// </summary>
		/// <param name="position">画素位置</param>
		/// <param name="color">設定する色</param>
		void CvSet(CvPoint position, CvScalar color);

		/// <summary>
		/// Bitmapの取得
		/// </summary>
		System::Drawing::Bitmap^ GetImageBmp();
	}; 
}

