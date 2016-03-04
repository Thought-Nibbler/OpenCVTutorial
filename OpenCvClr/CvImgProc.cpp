// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "CvImgProc.h"
using namespace msclr::interop;

namespace OpenCvClr 
{
	OpenCvClr::CvImage^ CvImgProc::Threshold(CvImage^ inputImage, int threshold)
	{
		// グレースケール画像
		IplImage *grayImage = NULL;
		// 二値画像
		IplImage *binImage = NULL;
		// 出力画像
		CvImage^ retImage = nullptr;
		
		try
		{
			// 中間画像（グレースケール画像）の領域確保
			grayImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (grayImage == NULL)
			{
				throw gcnew Exception("グレースケール画像の領域確保に失敗しました。");
			}

			// 中間画像（グレースケール画像）の作成
			cvCvtColor(inputImage->Image, grayImage, CV_BGR2GRAY);

			// 中間画像（二値画像）の領域確保
			binImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (binImage == NULL)
			{
				throw gcnew Exception("中間二値画像の領域確保に失敗しました。");
			}

			// 中間画像（二値画像）の作成
			cvThreshold(grayImage, binImage, threshold, 255, CV_THRESH_BINARY);

			// 中間画像（グレースケール画像）は不要なので消去する
			cvReleaseImage(&grayImage);
			grayImage = NULL;

			// 出力画像領域の確保
			retImage = gcnew CvImage(inputImage->Image->width, inputImage->Image->height);

			// 画素値の設定
			for (int y = 0; y < retImage->height; y++)
			{
				for (int x = 0; x < retImage->width; x++)
				{
					uchar px = (uchar) binImage->imageData[(y * binImage->widthStep) + x];

					retImage->CvSet(cvPoint(x, y), CV_RGB(px, px, px));
				}
			}

			return retImage;
		}
		catch (Exception^ ex)
		{
			throw ex;
		}
		finally
		{
			if (grayImage != NULL)
			{
				cvReleaseImage(&grayImage);
			}
			if (binImage != NULL)
			{
				cvReleaseImage(&binImage);
			}
		}
	}
	
	OpenCvClr::CvImage^ CvImgProc::AdaptiveThresdhold(CvImage^ inputImage, CvAdaptMethod adaptiveMethod, int blockSize, double param)
	{
		// グレースケール画像
		IplImage *grayImage = NULL;
		// 二値画像
		IplImage *binImage = NULL;
		// 出力画像
		CvImage^ retImage = nullptr;
		
		try
		{
			// 中間画像（グレースケール画像）の領域確保
			grayImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (grayImage == NULL)
			{
				throw gcnew Exception("グレースケール画像の領域確保に失敗しました。");
			}

			// 中間画像（グレースケール画像）の作成
			cvCvtColor(inputImage->Image, grayImage, CV_BGR2GRAY);

			// 中間画像（二値画像）の領域確保
			binImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (binImage == NULL)
			{
				throw gcnew Exception("中間二値画像の領域確保に失敗しました。");
			}

			// 中間画像（二値画像）の作成
			cvAdaptiveThreshold(grayImage, binImage, 255, (int)adaptiveMethod, CV_THRESH_BINARY, blockSize, param);

			// 中間画像（グレースケール画像）は不要なので消去する
			cvReleaseImage(&grayImage);
			grayImage = NULL;

			// 出力画像領域の確保
			retImage = gcnew CvImage(inputImage->Image->width, inputImage->Image->height);

			// 画素値の設定
			for (int y = 0; y < retImage->height; y++)
			{
				for (int x = 0; x < retImage->width; x++)
				{
					uchar px = (uchar) binImage->imageData[(y * binImage->widthStep) + x];

					retImage->CvSet(cvPoint(x, y), CV_RGB(px, px, px));
				}
			}

			return retImage;
		}
		catch (Exception^ ex)
		{
			throw ex;
		}
		finally
		{
			if (grayImage != NULL)
			{
				cvReleaseImage(&grayImage);
			}
			if (binImage != NULL)
			{
				cvReleaseImage(&binImage);
			}
		}
	}

	OpenCvClr::CvImage^ CvImgProc::Smooth(CvImage^ inputImage, CvSmoothType smoothType, int filterX, int filterY, double sigma1, double sigma2)
	{
		// 平滑化画像
		IplImage *smoothImage = NULL;
		// 出力画像
		CvImage^ retImage = nullptr;
		
		try
		{
			// 中間画像（平滑化画像）の領域確保
			smoothImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 3);
			if (smoothImage == NULL)
			{
				throw gcnew Exception("平滑化画像の領域確保に失敗しました。");
			}

			// 中間画像（平滑化画像）の作成
			cvSmooth(inputImage->Image, smoothImage, (int)smoothType, filterX, filterY, sigma1, sigma2);

			// 出力画像領域の確保
			retImage = gcnew CvImage(smoothImage);

			return retImage;
		}
		catch (Exception^ ex)
		{
			throw ex;
		}
		finally
		{
			if (smoothImage != NULL)
			{
				cvReleaseImage(&smoothImage);
			}
		}
	}
}