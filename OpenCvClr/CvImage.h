#pragma once

#include <msclr/marshal_cppstd.h>
#include "opencv2/opencv.hpp"

using namespace System;
using namespace System::Drawing;


namespace OpenCvClr
{
	/// <summary>
	/// C#���ŏ����ΏۂƂȂ�摜�I�u�W�F�N�g
	/// </summary>
	public ref class CvImage
	{
	private:
		/// <summary>
		/// �������ʉ摜�f�[�^�̕ێ��̈�
		/// </summary>
		uchar *ImageData;

		/// <summary>
		/// �������ʉ摜�f�[�^�̕ێ��̈�iIntPtr�j
		/// </summary>
		System::IntPtr ImageDataPtr;

		/// <summary>
		/// �������ʉ摜�f�[�^�̃I�u�W�F�N�g
		/// </summary>
		System::Drawing::Bitmap^ ImageBitmap;

		/// <summary>
		/// �����o�������i�R���X�g���N�^�ŌĂяo�����j
		/// </summary>
		void Initialize();

	public:
		/// <summary>
		/// �摜�̕�
		/// </summary>
		int width;

		/// <summary>
		/// �摜�̍���
		/// </summary>
		int height;

		/// <summary>
		/// �����Ώۂ̉摜
		/// </summary>
		IplImage *Image;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="width">�쐬�摜��</param>
		/// <param name="height">�쐬�摜����</param>
		CvImage(int width, int height);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="filename">���̓t�@�C����</param>
		CvImage(String ^filename);

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~CvImage();

		/// <summary>
		/// ��f�ݒ�
		/// </summary>
		/// <param name="position">��f�ʒu</param>
		/// <param name="color">�ݒ肷��F</param>
		void CvSet(CvPoint position, CvScalar color);

		/// <summary>
		/// Bitmap�̎擾
		/// </summary>
		System::Drawing::Bitmap^ GetImageBmp();
	}; 
}

