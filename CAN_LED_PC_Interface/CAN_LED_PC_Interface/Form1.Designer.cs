namespace CAN_LED_PC_Interface
{
    partial class CAN_LED
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CAN_LED));
            this.ComPort = new System.IO.Ports.SerialPort(this.components);
            this.COM_cbox = new System.Windows.Forms.ComboBox();
            this.ser_connect_butt = new System.Windows.Forms.Button();
            this.com_status_label = new System.Windows.Forms.Label();
            this.serial_output_box = new System.Windows.Forms.RichTextBox();
            this.send_button = new System.Windows.Forms.Button();
            this.connected_timer = new System.Windows.Forms.Timer(this.components);
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.led_cube_tab = new System.Windows.Forms.TabPage();
            this.led_cube_arg2_label = new System.Windows.Forms.Label();
            this.led_cube_arg1_label = new System.Windows.Forms.Label();
            this.led_cube_cmd_label = new System.Windows.Forms.Label();
            this.led_cube_arg2_num_box = new System.Windows.Forms.NumericUpDown();
            this.led_cube_arg1_num_box = new System.Windows.Forms.NumericUpDown();
            this.led_cube_send_butt = new System.Windows.Forms.Button();
            this.led_cube_write_butt = new System.Windows.Forms.Button();
            this.led_cube_activate_butt = new System.Windows.Forms.Button();
            this.led_cube_arg2_box = new System.Windows.Forms.ComboBox();
            this.led_cube_arg1_box = new System.Windows.Forms.ComboBox();
            this.layer_box = new System.Windows.Forms.TabControl();
            this.layer0_tab = new System.Windows.Forms.TabPage();
            this.layer0_chbox = new System.Windows.Forms.CheckedListBox();
            this.layer1_tab = new System.Windows.Forms.TabPage();
            this.layer1_chbox = new System.Windows.Forms.CheckedListBox();
            this.layer2_tab = new System.Windows.Forms.TabPage();
            this.layer2_chbox = new System.Windows.Forms.CheckedListBox();
            this.led_cube_cmd_box = new System.Windows.Forms.ComboBox();
            this.rgb_led_tab = new System.Windows.Forms.TabPage();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.led_cube_tab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.led_cube_arg2_num_box)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.led_cube_arg1_num_box)).BeginInit();
            this.layer_box.SuspendLayout();
            this.layer0_tab.SuspendLayout();
            this.layer1_tab.SuspendLayout();
            this.layer2_tab.SuspendLayout();
            this.SuspendLayout();
            // 
            // ComPort
            // 
            this.ComPort.ReadTimeout = 100;
            this.ComPort.WriteTimeout = 100;
            this.ComPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.ComPort_DataReceived);
            // 
            // COM_cbox
            // 
            this.COM_cbox.FormattingEnabled = true;
            this.COM_cbox.Location = new System.Drawing.Point(66, 12);
            this.COM_cbox.Name = "COM_cbox";
            this.COM_cbox.Size = new System.Drawing.Size(121, 21);
            this.COM_cbox.TabIndex = 0;
            this.COM_cbox.DropDown += new System.EventHandler(this.COM_cbox_DropDown);
            // 
            // ser_connect_butt
            // 
            this.ser_connect_butt.Location = new System.Drawing.Point(194, 12);
            this.ser_connect_butt.Name = "ser_connect_butt";
            this.ser_connect_butt.Size = new System.Drawing.Size(75, 23);
            this.ser_connect_butt.TabIndex = 1;
            this.ser_connect_butt.Text = "Connect";
            this.ser_connect_butt.UseVisualStyleBackColor = true;
            this.ser_connect_butt.Click += new System.EventHandler(this.ser_connect_butt_Click);
            // 
            // com_status_label
            // 
            this.com_status_label.AutoSize = true;
            this.com_status_label.BackColor = System.Drawing.Color.Red;
            this.com_status_label.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.com_status_label.Location = new System.Drawing.Point(317, 17);
            this.com_status_label.Name = "com_status_label";
            this.com_status_label.Size = new System.Drawing.Size(75, 15);
            this.com_status_label.TabIndex = 2;
            this.com_status_label.Text = "Disconnected";
            // 
            // serial_output_box
            // 
            this.serial_output_box.Location = new System.Drawing.Point(12, 219);
            this.serial_output_box.Name = "serial_output_box";
            this.serial_output_box.Size = new System.Drawing.Size(507, 87);
            this.serial_output_box.TabIndex = 3;
            this.serial_output_box.Text = "";
            // 
            // send_button
            // 
            this.send_button.Location = new System.Drawing.Point(427, 12);
            this.send_button.Name = "send_button";
            this.send_button.Size = new System.Drawing.Size(92, 37);
            this.send_button.TabIndex = 4;
            this.send_button.Text = "Send";
            this.send_button.UseVisualStyleBackColor = true;
            this.send_button.Click += new System.EventHandler(this.send_button_Click);
            // 
            // connected_timer
            // 
            this.connected_timer.Enabled = true;
            this.connected_timer.Tick += new System.EventHandler(this.connected_timer_Tick);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.led_cube_tab);
            this.tabControl1.Controls.Add(this.rgb_led_tab);
            this.tabControl1.Location = new System.Drawing.Point(12, 48);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(511, 146);
            this.tabControl1.TabIndex = 5;
            // 
            // led_cube_tab
            // 
            this.led_cube_tab.Controls.Add(this.led_cube_arg2_label);
            this.led_cube_tab.Controls.Add(this.led_cube_arg1_label);
            this.led_cube_tab.Controls.Add(this.led_cube_cmd_label);
            this.led_cube_tab.Controls.Add(this.led_cube_arg2_num_box);
            this.led_cube_tab.Controls.Add(this.led_cube_arg1_num_box);
            this.led_cube_tab.Controls.Add(this.led_cube_send_butt);
            this.led_cube_tab.Controls.Add(this.led_cube_write_butt);
            this.led_cube_tab.Controls.Add(this.led_cube_activate_butt);
            this.led_cube_tab.Controls.Add(this.led_cube_arg2_box);
            this.led_cube_tab.Controls.Add(this.led_cube_arg1_box);
            this.led_cube_tab.Controls.Add(this.layer_box);
            this.led_cube_tab.Controls.Add(this.led_cube_cmd_box);
            this.led_cube_tab.Location = new System.Drawing.Point(4, 22);
            this.led_cube_tab.Name = "led_cube_tab";
            this.led_cube_tab.Padding = new System.Windows.Forms.Padding(3);
            this.led_cube_tab.Size = new System.Drawing.Size(503, 120);
            this.led_cube_tab.TabIndex = 0;
            this.led_cube_tab.Text = "LED Cube";
            this.led_cube_tab.UseVisualStyleBackColor = true;
            // 
            // led_cube_arg2_label
            // 
            this.led_cube_arg2_label.AutoSize = true;
            this.led_cube_arg2_label.Location = new System.Drawing.Point(25, 80);
            this.led_cube_arg2_label.MinimumSize = new System.Drawing.Size(61, 0);
            this.led_cube_arg2_label.Name = "led_cube_arg2_label";
            this.led_cube_arg2_label.Size = new System.Drawing.Size(61, 13);
            this.led_cube_arg2_label.TabIndex = 11;
            this.led_cube_arg2_label.Text = "Arg2";
            this.led_cube_arg2_label.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // led_cube_arg1_label
            // 
            this.led_cube_arg1_label.AutoSize = true;
            this.led_cube_arg1_label.Location = new System.Drawing.Point(25, 49);
            this.led_cube_arg1_label.MinimumSize = new System.Drawing.Size(61, 0);
            this.led_cube_arg1_label.Name = "led_cube_arg1_label";
            this.led_cube_arg1_label.Size = new System.Drawing.Size(61, 13);
            this.led_cube_arg1_label.TabIndex = 10;
            this.led_cube_arg1_label.Text = "Arg1";
            this.led_cube_arg1_label.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // led_cube_cmd_label
            // 
            this.led_cube_cmd_label.AutoSize = true;
            this.led_cube_cmd_label.Location = new System.Drawing.Point(33, 19);
            this.led_cube_cmd_label.Name = "led_cube_cmd_label";
            this.led_cube_cmd_label.Size = new System.Drawing.Size(54, 13);
            this.led_cube_cmd_label.TabIndex = 9;
            this.led_cube_cmd_label.Text = "Command";
            this.led_cube_cmd_label.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // led_cube_arg2_num_box
            // 
            this.led_cube_arg2_num_box.Location = new System.Drawing.Point(93, 78);
            this.led_cube_arg2_num_box.Name = "led_cube_arg2_num_box";
            this.led_cube_arg2_num_box.Size = new System.Drawing.Size(120, 20);
            this.led_cube_arg2_num_box.TabIndex = 8;
            this.led_cube_arg2_num_box.Visible = false;
            // 
            // led_cube_arg1_num_box
            // 
            this.led_cube_arg1_num_box.Location = new System.Drawing.Point(93, 47);
            this.led_cube_arg1_num_box.Name = "led_cube_arg1_num_box";
            this.led_cube_arg1_num_box.Size = new System.Drawing.Size(120, 20);
            this.led_cube_arg1_num_box.TabIndex = 6;
            this.led_cube_arg1_num_box.Visible = false;
            // 
            // led_cube_send_butt
            // 
            this.led_cube_send_butt.Location = new System.Drawing.Point(380, 78);
            this.led_cube_send_butt.Name = "led_cube_send_butt";
            this.led_cube_send_butt.Size = new System.Drawing.Size(75, 23);
            this.led_cube_send_butt.TabIndex = 7;
            this.led_cube_send_butt.Text = "Send";
            this.led_cube_send_butt.UseVisualStyleBackColor = true;
            this.led_cube_send_butt.Click += new System.EventHandler(this.led_cube_send_butt_Click);
            // 
            // led_cube_write_butt
            // 
            this.led_cube_write_butt.Location = new System.Drawing.Point(380, 47);
            this.led_cube_write_butt.Name = "led_cube_write_butt";
            this.led_cube_write_butt.Size = new System.Drawing.Size(75, 23);
            this.led_cube_write_butt.TabIndex = 6;
            this.led_cube_write_butt.Text = "Start Write";
            this.led_cube_write_butt.UseVisualStyleBackColor = true;
            this.led_cube_write_butt.Click += new System.EventHandler(this.led_cube_write_butt_Click);
            // 
            // led_cube_activate_butt
            // 
            this.led_cube_activate_butt.Location = new System.Drawing.Point(380, 16);
            this.led_cube_activate_butt.Name = "led_cube_activate_butt";
            this.led_cube_activate_butt.Size = new System.Drawing.Size(75, 23);
            this.led_cube_activate_butt.TabIndex = 5;
            this.led_cube_activate_butt.Text = "Activate";
            this.led_cube_activate_butt.UseVisualStyleBackColor = true;
            this.led_cube_activate_butt.Click += new System.EventHandler(this.led_cube_activate_butt_Click);
            // 
            // led_cube_arg2_box
            // 
            this.led_cube_arg2_box.FormattingEnabled = true;
            this.led_cube_arg2_box.Location = new System.Drawing.Point(92, 78);
            this.led_cube_arg2_box.Name = "led_cube_arg2_box";
            this.led_cube_arg2_box.Size = new System.Drawing.Size(121, 21);
            this.led_cube_arg2_box.TabIndex = 4;
            // 
            // led_cube_arg1_box
            // 
            this.led_cube_arg1_box.FormattingEnabled = true;
            this.led_cube_arg1_box.Location = new System.Drawing.Point(92, 47);
            this.led_cube_arg1_box.Name = "led_cube_arg1_box";
            this.led_cube_arg1_box.Size = new System.Drawing.Size(121, 21);
            this.led_cube_arg1_box.TabIndex = 3;
            // 
            // layer_box
            // 
            this.layer_box.Controls.Add(this.layer0_tab);
            this.layer_box.Controls.Add(this.layer1_tab);
            this.layer_box.Controls.Add(this.layer2_tab);
            this.layer_box.Location = new System.Drawing.Point(229, 16);
            this.layer_box.Name = "layer_box";
            this.layer_box.Padding = new System.Drawing.Point(3, 3);
            this.layer_box.SelectedIndex = 0;
            this.layer_box.Size = new System.Drawing.Size(123, 84);
            this.layer_box.TabIndex = 2;
            // 
            // layer0_tab
            // 
            this.layer0_tab.Controls.Add(this.layer0_chbox);
            this.layer0_tab.Location = new System.Drawing.Point(4, 22);
            this.layer0_tab.Name = "layer0_tab";
            this.layer0_tab.Padding = new System.Windows.Forms.Padding(3);
            this.layer0_tab.Size = new System.Drawing.Size(115, 58);
            this.layer0_tab.TabIndex = 0;
            this.layer0_tab.Text = "0";
            this.layer0_tab.UseVisualStyleBackColor = true;
            // 
            // layer0_chbox
            // 
            this.layer0_chbox.CheckOnClick = true;
            this.layer0_chbox.ColumnWidth = 30;
            this.layer0_chbox.FormattingEnabled = true;
            this.layer0_chbox.Items.AddRange(new object[] {
            "6",
            "3",
            "0",
            "7",
            "4",
            "1",
            "8",
            "5",
            "2"});
            this.layer0_chbox.Location = new System.Drawing.Point(6, 6);
            this.layer0_chbox.MultiColumn = true;
            this.layer0_chbox.Name = "layer0_chbox";
            this.layer0_chbox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.layer0_chbox.Size = new System.Drawing.Size(100, 49);
            this.layer0_chbox.TabIndex = 1;
            // 
            // layer1_tab
            // 
            this.layer1_tab.Controls.Add(this.layer1_chbox);
            this.layer1_tab.Location = new System.Drawing.Point(4, 22);
            this.layer1_tab.Name = "layer1_tab";
            this.layer1_tab.Padding = new System.Windows.Forms.Padding(3);
            this.layer1_tab.Size = new System.Drawing.Size(115, 58);
            this.layer1_tab.TabIndex = 1;
            this.layer1_tab.Text = "1";
            this.layer1_tab.UseVisualStyleBackColor = true;
            // 
            // layer1_chbox
            // 
            this.layer1_chbox.CheckOnClick = true;
            this.layer1_chbox.ColumnWidth = 30;
            this.layer1_chbox.FormattingEnabled = true;
            this.layer1_chbox.Items.AddRange(new object[] {
            "6",
            "3",
            "0",
            "7",
            "4",
            "1",
            "8",
            "5",
            "2"});
            this.layer1_chbox.Location = new System.Drawing.Point(7, 5);
            this.layer1_chbox.MultiColumn = true;
            this.layer1_chbox.Name = "layer1_chbox";
            this.layer1_chbox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.layer1_chbox.Size = new System.Drawing.Size(100, 49);
            this.layer1_chbox.TabIndex = 2;
            // 
            // layer2_tab
            // 
            this.layer2_tab.Controls.Add(this.layer2_chbox);
            this.layer2_tab.Location = new System.Drawing.Point(4, 22);
            this.layer2_tab.Name = "layer2_tab";
            this.layer2_tab.Padding = new System.Windows.Forms.Padding(3);
            this.layer2_tab.Size = new System.Drawing.Size(115, 58);
            this.layer2_tab.TabIndex = 2;
            this.layer2_tab.Text = "2";
            this.layer2_tab.UseVisualStyleBackColor = true;
            // 
            // layer2_chbox
            // 
            this.layer2_chbox.CheckOnClick = true;
            this.layer2_chbox.ColumnWidth = 30;
            this.layer2_chbox.FormattingEnabled = true;
            this.layer2_chbox.Items.AddRange(new object[] {
            "6",
            "3",
            "0",
            "7",
            "4",
            "1",
            "8",
            "5",
            "2"});
            this.layer2_chbox.Location = new System.Drawing.Point(7, 5);
            this.layer2_chbox.MultiColumn = true;
            this.layer2_chbox.Name = "layer2_chbox";
            this.layer2_chbox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.layer2_chbox.Size = new System.Drawing.Size(100, 49);
            this.layer2_chbox.TabIndex = 3;
            // 
            // led_cube_cmd_box
            // 
            this.led_cube_cmd_box.FormattingEnabled = true;
            this.led_cube_cmd_box.Items.AddRange(new object[] {
            "LOAD",
            "ROTATE",
            "MIRROR",
            "TRANSLATE",
            "TRANSLATE CLEAR",
            "LOOP",
            "DELAY"});
            this.led_cube_cmd_box.Location = new System.Drawing.Point(93, 16);
            this.led_cube_cmd_box.Name = "led_cube_cmd_box";
            this.led_cube_cmd_box.Size = new System.Drawing.Size(121, 21);
            this.led_cube_cmd_box.TabIndex = 0;
            this.led_cube_cmd_box.SelectedIndexChanged += new System.EventHandler(this.led_cube_cmd_box_SelectionChangeCommitted);
            this.led_cube_cmd_box.DropDownClosed += new System.EventHandler(this.led_cube_cmd_box_SelectionChangeCommitted);
            // 
            // rgb_led_tab
            // 
            this.rgb_led_tab.Location = new System.Drawing.Point(4, 22);
            this.rgb_led_tab.Name = "rgb_led_tab";
            this.rgb_led_tab.Padding = new System.Windows.Forms.Padding(3);
            this.rgb_led_tab.Size = new System.Drawing.Size(503, 120);
            this.rgb_led_tab.TabIndex = 1;
            this.rgb_led_tab.Text = "RGB LED Strip";
            this.rgb_led_tab.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 203);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Serial Output";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "COM Port";
            // 
            // CAN_LED
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(535, 318);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.send_button);
            this.Controls.Add(this.serial_output_box);
            this.Controls.Add(this.com_status_label);
            this.Controls.Add(this.ser_connect_butt);
            this.Controls.Add(this.COM_cbox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "CAN_LED";
            this.Text = "CAN LED PC Interface";
            this.tabControl1.ResumeLayout(false);
            this.led_cube_tab.ResumeLayout(false);
            this.led_cube_tab.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.led_cube_arg2_num_box)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.led_cube_arg1_num_box)).EndInit();
            this.layer_box.ResumeLayout(false);
            this.layer0_tab.ResumeLayout(false);
            this.layer1_tab.ResumeLayout(false);
            this.layer2_tab.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort ComPort;
        private System.Windows.Forms.ComboBox COM_cbox;
        private System.Windows.Forms.Button ser_connect_butt;
        private System.Windows.Forms.Label com_status_label;
        private System.Windows.Forms.RichTextBox serial_output_box;
        private System.Windows.Forms.Button send_button;
        private System.Windows.Forms.Timer connected_timer;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage led_cube_tab;
        private System.Windows.Forms.TabPage rgb_led_tab;
        private System.Windows.Forms.ComboBox led_cube_cmd_box;
        private System.Windows.Forms.CheckedListBox layer0_chbox;
        private System.Windows.Forms.TabControl layer_box;
        private System.Windows.Forms.TabPage layer0_tab;
        private System.Windows.Forms.TabPage layer1_tab;
        private System.Windows.Forms.CheckedListBox layer1_chbox;
        private System.Windows.Forms.TabPage layer2_tab;
        private System.Windows.Forms.CheckedListBox layer2_chbox;
        private System.Windows.Forms.Button led_cube_send_butt;
        private System.Windows.Forms.Button led_cube_write_butt;
        private System.Windows.Forms.Button led_cube_activate_butt;
        private System.Windows.Forms.ComboBox led_cube_arg2_box;
        private System.Windows.Forms.ComboBox led_cube_arg1_box;
        private System.Windows.Forms.NumericUpDown led_cube_arg1_num_box;
        private System.Windows.Forms.NumericUpDown led_cube_arg2_num_box;
        private System.Windows.Forms.Label led_cube_arg2_label;
        private System.Windows.Forms.Label led_cube_arg1_label;
        private System.Windows.Forms.Label led_cube_cmd_label;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

