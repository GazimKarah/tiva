/*
 * Created by SharpDevelop.
 * User: bb
 * Date: 8.12.2020
 * Time: 18:22
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace deneme
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
			System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
			this.btnac = new System.Windows.Forms.Button();
			this.btnkapat = new System.Windows.Forms.Button();
			this.textcom = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.BAUDRATE = new System.Windows.Forms.Label();
			this.textBaudrate = new System.Windows.Forms.TextBox();
			this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
			this.label2 = new System.Windows.Forms.Label();
			this.textdatabit = new System.Windows.Forms.TextBox();
			this.textGonderilecekVeriler = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.btnGonder = new System.Windows.Forms.Button();
			this.label4 = new System.Windows.Forms.Label();
			this.textgelenveriler = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.textADCverisi = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.textBaslangicSaati = new System.Windows.Forms.TextBox();
			this.btnSaatGonder = new System.Windows.Forms.Button();
			this.btnLCD2cisatirisil = new System.Windows.Forms.Button();
			this.label7 = new System.Windows.Forms.Label();
			this.textBoxMCdengelenSaat = new System.Windows.Forms.TextBox();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
			this.button1 = new System.Windows.Forms.Button();
			this.listBox1 = new System.Windows.Forms.ListBox();
			((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
			this.SuspendLayout();
			// 
			// btnac
			// 
			this.btnac.Location = new System.Drawing.Point(302, 37);
			this.btnac.Margin = new System.Windows.Forms.Padding(2);
			this.btnac.Name = "btnac";
			this.btnac.Size = new System.Drawing.Size(68, 33);
			this.btnac.TabIndex = 0;
			this.btnac.Text = "Aç";
			this.btnac.UseVisualStyleBackColor = true;
			this.btnac.Click += new System.EventHandler(this.BtnacClick);
			// 
			// btnkapat
			// 
			this.btnkapat.Location = new System.Drawing.Point(302, 82);
			this.btnkapat.Margin = new System.Windows.Forms.Padding(2);
			this.btnkapat.Name = "btnkapat";
			this.btnkapat.Size = new System.Drawing.Size(68, 36);
			this.btnkapat.TabIndex = 1;
			this.btnkapat.Text = "kapat";
			this.btnkapat.UseVisualStyleBackColor = true;
			this.btnkapat.Click += new System.EventHandler(this.BtnkapatClick);
			// 
			// textcom
			// 
			this.textcom.Location = new System.Drawing.Point(112, 44);
			this.textcom.Margin = new System.Windows.Forms.Padding(2);
			this.textcom.Name = "textcom";
			this.textcom.Size = new System.Drawing.Size(76, 20);
			this.textcom.TabIndex = 2;
			this.textcom.Text = "COM4";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(41, 44);
			this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(66, 18);
			this.label1.TabIndex = 3;
			this.label1.Text = "com no";
			// 
			// BAUDRATE
			// 
			this.BAUDRATE.Location = new System.Drawing.Point(41, 81);
			this.BAUDRATE.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.BAUDRATE.Name = "BAUDRATE";
			this.BAUDRATE.Size = new System.Drawing.Size(66, 19);
			this.BAUDRATE.TabIndex = 4;
			this.BAUDRATE.Text = "Baudrate";
			// 
			// textBaudrate
			// 
			this.textBaudrate.Location = new System.Drawing.Point(112, 82);
			this.textBaudrate.Margin = new System.Windows.Forms.Padding(2);
			this.textBaudrate.Name = "textBaudrate";
			this.textBaudrate.Size = new System.Drawing.Size(76, 20);
			this.textBaudrate.TabIndex = 5;
			this.textBaudrate.Text = "115200";
			// 
			// serialPort1
			// 
			this.serialPort1.ReadBufferSize = 8192;
			this.serialPort1.WriteBufferSize = 8192;
			this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort1DataReceived);
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(41, 118);
			this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(75, 19);
			this.label2.TabIndex = 6;
			this.label2.Text = "databits";
			// 
			// textdatabit
			// 
			this.textdatabit.Location = new System.Drawing.Point(112, 115);
			this.textdatabit.Margin = new System.Windows.Forms.Padding(2);
			this.textdatabit.Name = "textdatabit";
			this.textdatabit.Size = new System.Drawing.Size(76, 20);
			this.textdatabit.TabIndex = 7;
			this.textdatabit.Text = "8";
			// 
			// textGonderilecekVeriler
			// 
			this.textGonderilecekVeriler.Location = new System.Drawing.Point(112, 165);
			this.textGonderilecekVeriler.Margin = new System.Windows.Forms.Padding(2);
			this.textGonderilecekVeriler.Multiline = true;
			this.textGonderilecekVeriler.Name = "textGonderilecekVeriler";
			this.textGonderilecekVeriler.Size = new System.Drawing.Size(152, 34);
			this.textGonderilecekVeriler.TabIndex = 8;
			this.textGonderilecekVeriler.Text = "lcd nin 2. satırında gözükecek";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(32, 167);
			this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(75, 33);
			this.label3.TabIndex = 9;
			this.label3.Text = "gönderilecek veri";
			// 
			// btnGonder
			// 
			this.btnGonder.Location = new System.Drawing.Point(294, 167);
			this.btnGonder.Margin = new System.Windows.Forms.Padding(2);
			this.btnGonder.Name = "btnGonder";
			this.btnGonder.Size = new System.Drawing.Size(92, 33);
			this.btnGonder.TabIndex = 10;
			this.btnGonder.Text = "mcYe Gönder";
			this.btnGonder.UseVisualStyleBackColor = true;
			this.btnGonder.Click += new System.EventHandler(this.BtnGonderClick);
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(32, 237);
			this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(75, 19);
			this.label4.TabIndex = 11;
			this.label4.Text = "gelenveri";
			// 
			// textgelenveriler
			// 
			this.textgelenveriler.BackColor = System.Drawing.SystemColors.MenuText;
			this.textgelenveriler.ForeColor = System.Drawing.SystemColors.Window;
			this.textgelenveriler.Location = new System.Drawing.Point(105, 228);
			this.textgelenveriler.Margin = new System.Windows.Forms.Padding(2);
			this.textgelenveriler.Multiline = true;
			this.textgelenveriler.Name = "textgelenveriler";
			this.textgelenveriler.Size = new System.Drawing.Size(158, 55);
			this.textgelenveriler.TabIndex = 12;
			this.textgelenveriler.Text = "Merhaba yazısı buarada";
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(32, 343);
			this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(75, 19);
			this.label5.TabIndex = 13;
			this.label5.Text = "adc VERİSİ";
			// 
			// textADCverisi
			// 
			this.textADCverisi.Location = new System.Drawing.Point(105, 340);
			this.textADCverisi.Margin = new System.Windows.Forms.Padding(2);
			this.textADCverisi.Name = "textADCverisi";
			this.textADCverisi.Size = new System.Drawing.Size(150, 20);
			this.textADCverisi.TabIndex = 14;
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(32, 403);
			this.label6.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(75, 19);
			this.label6.TabIndex = 15;
			this.label6.Text = "baslangıc saati";
			// 
			// textBaslangicSaati
			// 
			this.textBaslangicSaati.Location = new System.Drawing.Point(105, 401);
			this.textBaslangicSaati.Margin = new System.Windows.Forms.Padding(2);
			this.textBaslangicSaati.Name = "textBaslangicSaati";
			this.textBaslangicSaati.Size = new System.Drawing.Size(150, 20);
			this.textBaslangicSaati.TabIndex = 16;
			this.textBaslangicSaati.Text = "12:34:56";
			// 
			// btnSaatGonder
			// 
			this.btnSaatGonder.Location = new System.Drawing.Point(279, 401);
			this.btnSaatGonder.Margin = new System.Windows.Forms.Padding(2);
			this.btnSaatGonder.Name = "btnSaatGonder";
			this.btnSaatGonder.Size = new System.Drawing.Size(91, 21);
			this.btnSaatGonder.TabIndex = 17;
			this.btnSaatGonder.Text = "Saat Gönder";
			this.btnSaatGonder.UseVisualStyleBackColor = true;
			this.btnSaatGonder.Click += new System.EventHandler(this.BtnSaatGonderClick);
			// 
			// btnLCD2cisatirisil
			// 
			this.btnLCD2cisatirisil.Location = new System.Drawing.Point(279, 454);
			this.btnLCD2cisatirisil.Margin = new System.Windows.Forms.Padding(2);
			this.btnLCD2cisatirisil.Name = "btnLCD2cisatirisil";
			this.btnLCD2cisatirisil.Size = new System.Drawing.Size(91, 43);
			this.btnLCD2cisatirisil.TabIndex = 18;
			this.btnLCD2cisatirisil.Text = "LCD satır 2 Sil";
			this.btnLCD2cisatirisil.UseVisualStyleBackColor = true;
			this.btnLCD2cisatirisil.Click += new System.EventHandler(this.BtnLCD2cisatirisilClick);
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(32, 454);
			this.label7.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(51, 19);
			this.label7.TabIndex = 19;
			this.label7.Text = "lcd";
			// 
			// textBoxMCdengelenSaat
			// 
			this.textBoxMCdengelenSaat.Location = new System.Drawing.Point(105, 455);
			this.textBoxMCdengelenSaat.Margin = new System.Windows.Forms.Padding(2);
			this.textBoxMCdengelenSaat.Name = "textBoxMCdengelenSaat";
			this.textBoxMCdengelenSaat.Size = new System.Drawing.Size(144, 20);
			this.textBoxMCdengelenSaat.TabIndex = 20;
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(105, 287);
			this.textBox1.Margin = new System.Windows.Forms.Padding(2);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(222, 20);
			this.textBox1.TabIndex = 21;
			// 
			// chart1
			// 
			chartArea3.Name = "ChartArea1";
			this.chart1.ChartAreas.Add(chartArea3);
			legend3.Name = "Legend1";
			this.chart1.Legends.Add(legend3);
			this.chart1.Location = new System.Drawing.Point(427, 48);
			this.chart1.Name = "chart1";
			series3.ChartArea = "ChartArea1";
			series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
			series3.Legend = "Legend1";
			series3.Name = "bbseri";
			this.chart1.Series.Add(series3);
			this.chart1.Size = new System.Drawing.Size(640, 425);
			this.chart1.TabIndex = 22;
			this.chart1.Text = "chart1";
			this.chart1.Click += new System.EventHandler(this.Chart1Click);
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(587, 496);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(124, 34);
			this.button1.TabIndex = 23;
			this.button1.Text = "button1";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.Button1Click);
			// 
			// listBox1
			// 
			this.listBox1.FormattingEnabled = true;
			this.listBox1.Location = new System.Drawing.Point(1250, 50);
			this.listBox1.Name = "listBox1";
			this.listBox1.Size = new System.Drawing.Size(120, 420);
			this.listBox1.TabIndex = 24;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1502, 542);
			this.Controls.Add(this.listBox1);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.chart1);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.textBoxMCdengelenSaat);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.btnLCD2cisatirisil);
			this.Controls.Add(this.btnSaatGonder);
			this.Controls.Add(this.textBaslangicSaati);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.textADCverisi);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.textgelenveriler);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.btnGonder);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.textGonderilecekVeriler);
			this.Controls.Add(this.textdatabit);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textBaudrate);
			this.Controls.Add(this.BAUDRATE);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.textcom);
			this.Controls.Add(this.btnkapat);
			this.Controls.Add(this.btnac);
			this.Margin = new System.Windows.Forms.Padding(2);
			this.Name = "MainForm";
			this.Text = "deneme";
			((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.ListBox listBox1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.TextBox textBoxMCdengelenSaat;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Button btnLCD2cisatirisil;
		private System.Windows.Forms.Button btnSaatGonder;
		private System.Windows.Forms.TextBox textBaslangicSaati;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox textADCverisi;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox textgelenveriler;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Button btnGonder;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox textGonderilecekVeriler;
		private System.Windows.Forms.TextBox textdatabit;
		private System.Windows.Forms.Label label2;
		private System.IO.Ports.SerialPort serialPort1;
		private System.Windows.Forms.TextBox textBaudrate;
		private System.Windows.Forms.Label BAUDRATE;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textcom;
		private System.Windows.Forms.Button btnkapat;
		private System.Windows.Forms.Button btnac;
	}
}
