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
		bool boolsaatmi=false;
		int saathane=0;
		
		int intBuffer;
		
		char c;
		
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
				serialPort1.DiscardInBuffer();
				serialPort1.DiscardOutBuffer();
				serialPort1.DtrEnable = true;				
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
			//c=(char)serialPort1.ReadChar();
			//gelenveri=serialPort1.ReadExisting();
			//this.Invoke(new EventHandler(islemyap));	
			gelenveri=serialPort1.ReadLine();
			this.Invoke(new EventHandler(bbyap));
		}
		
		private void bbyap(object sender, EventArgs e){
			textgelenveriler.Text=gelenveri;
			if (gelenveri[0]=='[')// saat geldi
			{
				textgelensaat.Text=gelenveri.Substring(1,8);
			}
			else if(gelenveri[0]=='(') //adc
			{
				textADCverisi.Text=gelenveri.Substring(1,4);
			}
			else if(gelenveri[0]=='{') //keyfi
			{
				listBox1.Items.Add(gelenveri.Substring(1,gelenveri.Length-2));
			}		
		}
		
		private void islemyap(object sender, EventArgs e){
			textgelenveriler.Text=textgelenveriler.Text+c.ToString();
		}
		
		private void DisplayText(object sender, EventArgs e){
			textgelenveriler.Text=textgelenveriler.Text+gelenveri;
			
		}
	
		void adcyaz(){
			textADCverisi.Text=textgelenveriler.Text.Substring(textgelenveriler.Text.Length-1-4,4);
		}
	
		void keyfimesaj(){
			char ci='x';
			int no=2;
			while(ci!='{'){
				ci=textgelenveriler.Text[textgelenveriler.Text.Length-no];
				no++;
			}
			textBox1.Text=textgelenveriler.Text.Substring(
				textgelenveriler.Text.Length-no+2,
				textgelenveriler.Text.Length-1-(textgelenveriler.Text.Length-no+2));
		}
		
		private void SaatGosterSeriden(){
			textgelensaat.Text=gelenveri;
			//textgelensaat.Text=gelenveri.Length.ToString();
		}		
		
		void BtnSaatGonderClick(object sender, EventArgs e)
		{
			serialPort1.Write("%"+textBaslangicSaati.Text+"/");
		}
		
		void BtnLCD2cisatirisilClick(object sender, EventArgs e)
		{
			
		}
	}
}
