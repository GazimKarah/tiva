/*
 * Created by SharpDevelop.
 * User: bb
 * Date: 8.12.2020
 * Time: 18:22
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace deneme
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class MainForm : Form
	{
		string gelenveri=string.Empty;
		int sayici=0;
		public MainForm()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
		}
		
		void BtnacClick(object sender, EventArgs e)
		{
			if (!serialPort1.IsOpen){
				serialPort1.PortName=textcom.Text;
				serialPort1.BaudRate=Convert.ToInt32(textBaudrate.Text);
				serialPort1.DataBits=Convert.ToInt32(textdatabit.Text);
				serialPort1.Open();
			}
		}
		
		void BtnkapatClick(object sender, EventArgs e)
		{
			if(serialPort1.IsOpen){
				serialPort1.Close();
			}
		}
		
		void BtnGonderClick(object sender, EventArgs e)
		{
			serialPort1.Write(textGonderilecekVeriler.Text);
		}
		
		void SerialPort1DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
		{
			gelenveri=serialPort1.ReadLine();
			this.Invoke(new EventHandler(DisplayText));
		}
		
		private void DisplayText(object sender, EventArgs e){
			textgelenveriler.Text=gelenveri;
			
			if (gelenveri[0]=='['){
				// [12:34:56
				textBoxMCdengelenSaat.Text=gelenveri.Substring(1,8);
			}
			else if (gelenveri[0]=='('){
				// [12:34:56
				textADCverisi.Text=gelenveri.Substring(1,4);
			}
			else if (gelenveri[0]=='{'){
				textBox1.Text=gelenveri.Substring(1,gelenveri.Length-2);
			}
			else if (gelenveri[0]=='*'){
				sayici++;
				chart1.Series["bbseri"].Points.AddXY(sayici,(Convert.ToDouble(gelenveri.Substring(1,4))-1000)/1000);
				listBox1.Items.Add(( (Convert.ToDouble(gelenveri.Substring(1,4))-1000)/1000).ToString());
				if (sayici==100){
					sayici=0;
				}
			}
		}
		
		void BtnSaatGonderClick(object sender, EventArgs e)
		{
			serialPort1.Write("%"+textBaslangicSaati.Text+"/");
		}
		
		void BtnLCD2cisatirisilClick(object sender, EventArgs e)
		{
			
		}
		
		void Chart1Click(object sender, EventArgs e)
		{
			
		}
		
		void Button1Click(object sender, EventArgs e)
		{
			float[] dizi = new float[100];
			Random rastgele = new Random();
		   for (int i = 0; i <100; i++)
		   {
		   		dizi[i] = (float)(rastgele.Next(10,100))/100;;
			   	listBox1.Items.Add(dizi[i].ToString());
		   }	
			
		   for (int i = 0; i <100; i++)
		   {
		   	chart1.Series["bbseri"].Points.AddXY(i,dizi[i]);
		   }						   
		}
	}
}
