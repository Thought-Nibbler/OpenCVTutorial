using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using OpenCvClr;

namespace OpenCVTutorial
{
	public class IntegerToCvAdaptMethodConverter : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			if (value == null)
			{
				return -1;
			}

			CvAdaptMethod valueCvSmoothType = (CvAdaptMethod)value;

			switch (valueCvSmoothType)
			{
				case CvAdaptMethod.EQUIVALENT:
					return 0;
				case CvAdaptMethod.GAUSSIAN:
					return 1;
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
					return CvAdaptMethod.EQUIVALENT;
				case 1:
					return CvAdaptMethod.GAUSSIAN;
				default:
					return CvAdaptMethod.EQUIVALENT;
			}
		}
	}
}
