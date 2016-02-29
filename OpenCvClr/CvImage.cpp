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

		// ���͉摜�̓ǂݍ���
		this->Image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
		if (this->Image == NULL)
		{
			return;
		}

		// �T�C�Y�̎擾
		this->width = this->Image->width;
		this->height = this->Image->height;

		// Bitmap �쐬�p�s�N�Z���f�[�^�̈�̊m��
		this->ImageData = new uchar[this->Image->widthStep * this->Image->height];
		this->ImageDataPtr = IntPtr(this->ImageData);
	}

	CvImage::CvImage(String^ filename)
	{
		this->Initialize();

		// ���̓t�@�C������C������ɕϊ���������
		std::string cppstdStrFileName = marshal_as<std::string>(filename);
		const char *cStrFileName      = cppstdStrFileName.c_str();

		// ���͉摜�̓ǂݍ���
		this->Image = cvLoadImage(cStrFileName);
		if (this->Image == NULL)
		{
			return;
		}

		// �T�C�Y�̎擾
		this->width = this->Image->width;
		this->height = this->Image->height;

		// Bitmap �쐬�p�s�N�Z���f�[�^�̈�̊m��
		this->ImageData = new uchar[this->Image->widthStep * this->Image->height];
		this->ImageDataPtr = IntPtr(this->ImageData);
	}

	CvImage::CvImage(IplImage *image)
	{
		this->Initialize();

		// ���͉摜�̓ǂݍ���
		this->Image = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 3);
		if (this->Image == NULL)
		{
			return;
		}

		// �f�[�^�R�s�[
		memcpy(this->Image->imageData, image->imageData, (image->widthStep * image->height));

		// �T�C�Y�̎擾
		this->width = this->Image->width;
		this->height = this->Image->height;

		// Bitmap �쐬�p�s�N�Z���f�[�^�̈�̊m��
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

		// ���ʃr�b�g�}�b�v�̍쐬
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