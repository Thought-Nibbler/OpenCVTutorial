// ����� ���C�� DLL �t�@�C���ł��B

#include "stdafx.h"

#include "CvImgProc.h"
using namespace msclr::interop;

namespace OpenCvClr 
{
	OpenCvClr::CvImage^ CvImgProc::Threshold(CvImage^ inputImage, int threshold)
	{
		// �O���[�X�P�[���摜
		IplImage *grayImage = NULL;
		// ��l�摜
		IplImage *binImage = NULL;
		// �o�͉摜
		CvImage^ retImage = nullptr;
		
		try
		{
			// ���ԉ摜�i�O���[�X�P�[���摜�j�̗̈�m��
			grayImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (grayImage == NULL)
			{
				throw gcnew Exception("�O���[�X�P�[���摜�̗̈�m�ۂɎ��s���܂����B");
			}

			// ���ԉ摜�i�O���[�X�P�[���摜�j�̍쐬
			cvCvtColor(inputImage->Image, grayImage, CV_BGR2GRAY);

			// ���ԉ摜�i��l�摜�j�̗̈�m��
			binImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (binImage == NULL)
			{
				throw gcnew Exception("���ԓ�l�摜�̗̈�m�ۂɎ��s���܂����B");
			}

			// ���ԉ摜�i��l�摜�j�̍쐬
			cvThreshold(grayImage, binImage, threshold, 255, CV_THRESH_BINARY);

			// ���ԉ摜�i�O���[�X�P�[���摜�j�͕s�v�Ȃ̂ŏ�������
			cvReleaseImage(&grayImage);
			grayImage = NULL;

			// �o�͉摜�̈�̊m��
			retImage = gcnew CvImage(inputImage->Image->width, inputImage->Image->height);

			// ��f�l�̐ݒ�
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
		// �O���[�X�P�[���摜
		IplImage *grayImage = NULL;
		// ��l�摜
		IplImage *binImage = NULL;
		// �o�͉摜
		CvImage^ retImage = nullptr;
		
		try
		{
			// ���ԉ摜�i�O���[�X�P�[���摜�j�̗̈�m��
			grayImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (grayImage == NULL)
			{
				throw gcnew Exception("�O���[�X�P�[���摜�̗̈�m�ۂɎ��s���܂����B");
			}

			// ���ԉ摜�i�O���[�X�P�[���摜�j�̍쐬
			cvCvtColor(inputImage->Image, grayImage, CV_BGR2GRAY);

			// ���ԉ摜�i��l�摜�j�̗̈�m��
			binImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 1);
			if (binImage == NULL)
			{
				throw gcnew Exception("���ԓ�l�摜�̗̈�m�ۂɎ��s���܂����B");
			}

			// ���ԉ摜�i��l�摜�j�̍쐬
			cvAdaptiveThreshold(grayImage, binImage, 255, (int)adaptiveMethod, CV_THRESH_BINARY, blockSize, param);

			// ���ԉ摜�i�O���[�X�P�[���摜�j�͕s�v�Ȃ̂ŏ�������
			cvReleaseImage(&grayImage);
			grayImage = NULL;

			// �o�͉摜�̈�̊m��
			retImage = gcnew CvImage(inputImage->Image->width, inputImage->Image->height);

			// ��f�l�̐ݒ�
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
		// �������摜
		IplImage *smoothImage = NULL;
		// �o�͉摜
		CvImage^ retImage = nullptr;
		
		try
		{
			// ���ԉ摜�i�������摜�j�̗̈�m��
			smoothImage = cvCreateImage(cvSize(inputImage->Image->width, inputImage->Image->height), IPL_DEPTH_8U, 3);
			if (smoothImage == NULL)
			{
				throw gcnew Exception("�������摜�̗̈�m�ۂɎ��s���܂����B");
			}

			// ���ԉ摜�i�������摜�j�̍쐬
			cvSmooth(inputImage->Image, smoothImage, (int)smoothType, filterX, filterY, sigma1, sigma2);

			// �o�͉摜�̈�̊m��
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