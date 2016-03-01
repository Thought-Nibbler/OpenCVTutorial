#pragma once

namespace OpenCvClr 
{
	public enum class CvSmoothType : int
	{
		BLUR          = CV_BLUR,
		BLUR_NO_SCALE = CV_BLUR_NO_SCALE,
		MEDIAN        = CV_MEDIAN,
		GAUSSIAN      = CV_GAUSSIAN,
		BILATERAL     = CV_BILATERAL
	};
}
