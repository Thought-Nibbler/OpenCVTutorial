using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using OpenCvClr;

namespace OpenCVTutorial
{
	/// <summary>
	/// MainWindow.xaml の相互作用ロジック
	/// </summary>
	public partial class MainWindow : Window
	{
		/// <summary>
		/// コンストラクタ
		/// </summary>
		public MainWindow()
		{
			InitializeComponent();
		}

		/// <summary>
		/// [実行]ボタンが押された時の処理
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void Button_Click(object sender, RoutedEventArgs e)
		{
			try
			{
				System.Diagnostics.Debug.WriteLine(this.tcContents.SelectedIndex.ToString());

				switch (this.tcContents.SelectedIndex)
				{
					case 0:// TOP
						return;
					case 1:// 画像ファイルの読み込み
						this.LoadImageFile();
						return;
					case 4:// 二値化
						this.CreateBinaryImage();
						break;
					case 5:// 平滑化
						this.CreateSmoothImage();
						return;
					default:
						MessageBox.Show("未実装");
						return;
				}
			}
			catch (Exception ex)
			{
				System.Diagnostics.Debug.WriteLine(ex.Message);
			}
		}

		/// <summary>
		/// 画像ファイルの読み込み
		/// </summary>
		private void LoadImageFile()
		{
			try
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Filter = "Image Files (*.bmp, *.jpg)|*.bmp;*.jpg|All Files (*.*)|*.*"; ;
				ofd.InitialDirectory = @"C:\Users\Public\Pictures\Sample Pictures\";
				ofd.ShowDialog();

				CvImage orgImage = new CvImage(ofd.FileName);

				using (MemoryStream stream = new MemoryStream())
				{
					Bitmap bitmap = orgImage.GetImageBmp();

					if (bitmap == null)
					{
						MessageBox.Show("bitmap null.");
						return;
					}

					bitmap.Save(stream, ImageFormat.Bmp);

					// BitmapImageの作成（キャッシュを切る）
					BitmapImage bmpImage = new BitmapImage();
					bmpImage.BeginInit();
					bmpImage.CacheOption = BitmapCacheOption.OnLoad;
					bmpImage.CreateOptions = BitmapCreateOptions.None;
					bmpImage.StreamSource = stream;
					bmpImage.EndInit();
					bmpImage.Freeze();

					this.Image001.Source = bmpImage;

					bmpImage = null;
				}
			}
			catch (Exception ex)
			{
				throw ex;
			}
		}

		/// <summary>
		/// 二値化
		/// </summary>
		private void CreateBinaryImage()
		{
			try
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Filter = "Image Files (*.bmp, *.jpg)|*.bmp;*.jpg|All Files (*.*)|*.*"; ;
				ofd.InitialDirectory = @"C:\Users\Public\Pictures\Sample Pictures\";
				ofd.ShowDialog();

				CvImage orgImage = new CvImage(ofd.FileName);

				CvImage binImage = CvImgProc.CvThreshold(orgImage, 128);

				using (MemoryStream stream = new MemoryStream())
				{
					Bitmap bitmap = binImage.GetImageBmp();

					if (bitmap == null)
					{
						MessageBox.Show("bitmap null.");
						return;
					}

					bitmap.Save(stream, ImageFormat.Bmp);

					// BitmapImageの作成（キャッシュを切る）
					BitmapImage bmpImage = new BitmapImage();
					bmpImage.BeginInit();
					bmpImage.CacheOption = BitmapCacheOption.OnLoad;
					bmpImage.CreateOptions = BitmapCreateOptions.None;
					bmpImage.StreamSource = stream;
					bmpImage.EndInit();
					bmpImage.Freeze();

					this.Image004.Source = bmpImage;

					bmpImage = null;
				}
			}
			catch (Exception ex)
			{
				throw ex;
			}
		}

		/// <summary>
		/// 平滑化
		/// </summary>
		private void CreateSmoothImage()
		{
			try
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Filter = "Image Files (*.bmp, *.jpg)|*.bmp;*.jpg|All Files (*.*)|*.*"; ;
				ofd.InitialDirectory = @"C:\Users\Public\Pictures\Sample Pictures\";
				ofd.ShowDialog();

				CvImage orgImage = new CvImage(ofd.FileName);

				CvImage smoothImage = CvImgProc.CvSmooth(orgImage);

				using (MemoryStream stream = new MemoryStream())
				{
					Bitmap bitmap = smoothImage.GetImageBmp();

					if (bitmap == null)
					{
						MessageBox.Show("bitmap null.");
						return;
					}

					bitmap.Save(stream, ImageFormat.Bmp);

					// BitmapImageの作成（キャッシュを切る）
					BitmapImage bmpImage = new BitmapImage();
					bmpImage.BeginInit();
					bmpImage.CacheOption = BitmapCacheOption.OnLoad;
					bmpImage.CreateOptions = BitmapCreateOptions.None;
					bmpImage.StreamSource = stream;
					bmpImage.EndInit();
					bmpImage.Freeze();

					this.Image005.Source = bmpImage;

					bmpImage = null;
				}
			}
			catch (Exception ex)
			{
				throw ex;
			}
		}

	}
}
