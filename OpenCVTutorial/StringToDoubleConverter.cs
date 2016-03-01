using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace OpenCVTutorial
{
	public class StringToDoubleConverter : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			if (value == null)
			{
				return "";
			}

			double valueInteger = (double)value;

			return valueInteger.ToString();
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			string valueStr = value as string;

			if (valueStr == null)
			{
				return 0.0;
			}

			double work;

			if (double.TryParse(valueStr, out work))
			{
				return work;
			}

			return 0.0;
		}
	}
}
