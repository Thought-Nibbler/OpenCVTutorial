using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using OpenCvClr;

namespace OpenCVTutorial
{
	public class IntegerToCvSmoothTypeConverter : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			if (value == null)
			{
				return -1;
			}

			CvSmoothType valueCvSmoothType = (CvSmoothType)value;

			switch (valueCvSmoothType)
			{
				case CvSmoothType.BLUR:
					return 0;
				case CvSmoothType.BLUR_NO_SCALE:
					return 1;
				case CvSmoothType.MEDIAN:
					return 2;
				case CvSmoothType.GAUSSIAN:
					return 3;
				case CvSmoothType.BILATERAL:
					return 4;
				default:
					return -1;
			}
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			int valueInteger = (int)value;

			switch (valueInteger)
			{
				case 0:
					return CvSmoothType.BLUR;
				case 1:
					return CvSmoothType.BLUR_NO_SCALE;
				case 2:
					return CvSmoothType.MEDIAN;
				case 3:
					return CvSmoothType.GAUSSIAN;
				case 4:
					return CvSmoothType.BILATERAL;
				default:
					return CvSmoothType.BLUR;
			}
		}
	}
}
