using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace OpenCVTutorial
{
	public class StringToIntegerConverter : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			if (value == null)
			{
				return "";
			}

			int valueInteger = (int)value;

			return valueInteger.ToString();
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			string valueStr = value as string;

			if (valueStr == null)
			{
				return 0;
			}

			int work;

			if (int.TryParse(valueStr, out work))
			{
				return work;
			}

			return 0;
		}
	}
}
