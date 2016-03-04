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
		static OpenCvClr::CvImage^ Threshold(CvImage^ inputImage, int threshold);

		/// <summary>
		/// �K���^�������l�ɂ���l�摜�̍쐬
		/// </summary>
		/// <param name="position">���͉摜</param>
		/// <param name="adaptiveMethod">�K�����\�b�h�i�d�݂Â��j</param>
		/// <param name="blockSize">�u���b�N�T�C�Y</param>
		/// <param name="param">�萔�i���肵���������l����������l�j</param>
		static OpenCvClr::CvImage^ AdaptiveThresdhold(CvImage^ inputImage, CvAdaptMethod adaptiveMethod, int blockSize, double param);

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="position">���͉摜</param>
		/// <param name="smoothType">�������̎��</param>
		/// <param name="filterX">�t�B���^�T�C�Y�i���������j</param>
		/// <param name="filterY">�t�B���^�T�C�Y�i���������j</param>
		/// <param name="sigma1">�V�O�}�l�P</param>
		/// <param name="sigma2">�V�O�}�l�Q</param>
		static OpenCvClr::CvImage^ Smooth(CvImage^ inputImage, CvSmoothType smoothType, int filterX, int filterY, double sigma1, double sigma2);
	};
}
