using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
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
	public partial class MainWindow : Window, INotifyPropertyChanged
	{
		#region 共通プロパティ
		/// <summary>
		/// 画像ファイルパス
		/// </summary>
		private string FileName = null; 
		#endregion

		#region 二値化に関するプロパティ
		/// <summary>
		/// 二値化のしきい値
		/// </summary>
		public int Threshold
		{
			get
			{
				return this._Threshold;
			}
			set
			{
				this._Threshold = value;
				this.NotifyPropertyChanged("Threshold");
				this.CreateBinaryImage();
			}
		}
		private int _Threshold = 128; 
		#endregion

		#region 平滑化に関するプロパティ
		/// <summary>
		/// 平滑化に関するプロパティの定義
		/// </summary>
		public class SmoothPropertyClass
		{
			/// <summary>
			/// 平滑化の種類
			/// </summary>
			public CvSmoothType SmoothType { get; set; }

			/// <summary>
			/// フィルタサイズ（水平方向）
			/// </summary>
			public int FilterX { get; set; }

			/// <summary>
			/// フィルタサイズ（垂直方向）
			/// </summary>
			public int FilterY { get; set; }

			/// <summary>
			/// シグマ値１
			/// </summary>
			public double Sigma1 { get; set; }

			/// <summary>
			/// シグマ値２
			/// </summary>
			public double Sigma2 { get; set; }
		}

		/// <summary>
		/// 平滑化に関するプロパティオブジェクト
		/// </summary>
		public SmoothPropertyClass SmoothProperty { get; set; }
		#endregion


		#region コンストラクタ
		/// <summary>
		/// コンストラクタ
		/// </summary>
		public MainWindow()
		{
			try
			{
				InitializeComponent();

				this.DataContext = this;

				#region 平滑化に関するプロパティの初期化
				this.SmoothProperty            = new SmoothPropertyClass();
				this.SmoothProperty.SmoothType = CvSmoothType.GAUSSIAN;
				this.SmoothProperty.FilterX    = 3;
				this.SmoothProperty.FilterY    = 3;
				this.SmoothProperty.Sigma1     = 0.0;
				this.SmoothProperty.Sigma2     = 0.0;
				#endregion
			}
			catch (Exception ex)
			{
				System.Diagnostics.Debug.WriteLine(ex.Message);
			}
		} 
		#endregion

		#region タブ共通処理
		/// <summary>
		/// タブの切り替えが行われた時の処理 => 内部画像ファイルパスをリセットする
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void tcContents_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			// TODO: [平滑化タブ]内の[平滑化の種類]コンボボックス切替時にも入ってしまう
			this.FileName = null;
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
		/// ダイアログを開いて画像ファイルを選択する
		/// </summary>
		/// <returns>選択した画像のフルパス</returns>
		private string SelectImageFile()
		{
			try
			{
				OpenFileDialog ofd = new OpenFileDialog();
				ofd.Filter = "Image Files (*.bmp, *.jpg)|*.bmp;*.jpg|All Files (*.*)|*.*"; ;
				ofd.InitialDirectory = @"C:\Users\Public\Pictures\Sample Pictures\";
				bool result = (bool)ofd.ShowDialog();

				if (result)
				{
					return ofd.FileName;
				}
				else
				{
					throw new Exception("ファイルが選択されませんでした。");
				}
			}
			catch (Exception ex)
			{
				throw ex;
			}
		} 
		#endregion

		#region [画像ファイルの読み込み]タブ
		/// <summary>
		/// 画像ファイルの読み込み
		/// </summary>
		private void LoadImageFile()
		{
			try
			{
				if (this.FileName == null)
				{
					this.FileName = this.SelectImageFile();
				}

				using (CvImage orgImage = new CvImage(this.FileName))
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
		#endregion

		#region [二値化]タブ
		/// <summary>
		/// 二値化
		/// </summary>
		private void CreateBinaryImage()
		{
			try
			{
				if (this.FileName == null)
				{
					this.FileName = this.SelectImageFile();
				}

				using (CvImage orgImage = new CvImage(this.FileName))
				using (CvImage binImage = CvImgProc.Threshold(orgImage, this.Threshold))
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
			finally
			{
				GC.Collect();
			}
		} 
		#endregion

		#region [平滑化]タブ
		/// <summary>
		/// 平滑化
		/// </summary>
		private void CreateSmoothImage()
		{
			try
			{
				if (this.FileName == null)
				{
					this.FileName = this.SelectImageFile();
				}

				CvSmoothType smoothType = this.SmoothProperty.SmoothType;
				int          filterX    = this.SmoothProperty.FilterX;
				int          filterY    = this.SmoothProperty.FilterY;
				double       sigma1     = this.SmoothProperty.Sigma1;
				double       sigma2     = this.SmoothProperty.Sigma2;

				using (CvImage orgImage = new CvImage(this.FileName))
				using (CvImage smoothImage = CvImgProc.Smooth(orgImage, smoothType, filterX, filterY, sigma1, sigma2))
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

		/// <summary>
		/// [平滑化]タブ内の[更新]ボタンを押した時の処理
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void btnSmoothReload_Click(object sender, RoutedEventArgs e)
		{
			try
			{
				this.CreateSmoothImage();
			}
			catch (Exception ex)
			{
				throw ex;
			}
		}
		#endregion

		#region INotifyPropertyChanged の実装
		/// <summary>
		/// プロパティの変更イベント
		/// </summary>
		public event PropertyChangedEventHandler PropertyChanged;

		/// <summary>
		/// プロパティの変更を通知するメソッド
		/// </summary>
		/// <param name="propertyName"></param>
		private void NotifyPropertyChanged([CallerMemberName] String propertyName = "")
		{
			try
			{
				if (PropertyChanged != null)
				{
					PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
				}
			}
			catch (Exception ex)
			{
				throw ex;
			}
		}
		#endregion
	}
}
