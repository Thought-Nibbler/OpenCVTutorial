#include "stdafx.h"
#include "CvImage.h"
using namespace msclr::interop;


namespace OpenCvClr
{
	void CvImage::Initialize()
	{
		this->Image = NULL;
		this->ImageData = NULL;
		this->ImageBitmap = nullptr;
	}

	CvImage::CvImage(int width, int height)
	{
		this->Initialize();

		// 入力画像の読み込み
		this->Image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
		if (this->Image == NULL)
		{
			return;
		}

		// サイズの取得
		this->width = this->Image->width;
		this->height = this->Image->height;

		// Bitmap 作成用ピクセルデータ領域の確保
		this->ImageData = new uchar[this->Image->widthStep * this->Image->height];
		this->ImageDataPtr = IntPtr(this->ImageData);
	}

	CvImage::CvImage(String^ filename)
	{
		this->Initialize();

		// 入力ファイル名をC文字列に変換したもの
		std::string cppstdStrFileName = marshal_as<std::string>(filename);
		const char *cStrFileName      = cppstdStrFileName.c_str();

		// 入力画像の読み込み
		this->Image = cvLoadImage(cStrFileName);
		if (this->Image == NULL)
		{
			return;
		}

		// サイズの取得
		this->width = this->Image->width;
		this->height = this->Image->height;

		// Bitmap 作成用ピクセルデータ領域の確保
		this->ImageData = new uchar[this->Image->widthStep * this->Image->height];
		this->ImageDataPtr = IntPtr(this->ImageData);
	}

	CvImage::CvImage(IplImage *image)
	{
		this->Initialize();

		// 入力画像の読み込み
		this->Image = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 3);
		if (this->Image == NULL)
		{
			return;
		}

		// データコピー
		memcpy(this->Image->imageData, image->imageData, (image->widthStep * image->height));

		// サイズの取得
		this->width = this->Image->width;
		this->height = this->Image->height;

		// Bitmap 作成用ピクセルデータ領域の確保
		this->ImageData = new uchar[this->Image->widthStep * this->Image->height];
		this->ImageDataPtr = IntPtr(this->ImageData);
	}

	CvImage::~CvImage()
	{
		if (this->Image != NULL)
		{
			pin_ptr<IplImage *> p = &(this->Image);
			cvReleaseImage(p);
			this->Image = NULL;
		}

		if (this->ImageData != NULL)
		{
			delete (this->ImageData);
			this->ImageData = NULL;
		}
		
		if (this->ImageBitmap != nullptr)
		{
			delete (this->ImageBitmap);
		}
	}

	System::Drawing::Bitmap^ CvImage::GetImageBmp()
	{
		if (this->Image == NULL)
		{
			return nullptr;
		}

		// 結果ビットマップの作成
		memcpy(this->ImageDataPtr.ToPointer(), this->Image->imageData, this->Image->widthStep * this->Image->height);

		return gcnew System::Drawing::Bitmap(
			this->Image->width, 
			this->Image->height, 
			this->Image->widthStep,  
			System::Drawing::Imaging::PixelFormat::Format24bppRgb, 
			this->ImageDataPtr
		);;
	}

	void CvImage::CvSet(CvPoint position, CvScalar color)
	{
		cvSet2D(this->Image, position.y, position.x, color);
	}
}