using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace CAN_LED_PC_Interface
{
    public partial class CAN_LED : Form
    {
        public CAN_LED()
        {
            InitializeComponent();
            led_cube_cmd_box.SelectedIndex = 0;
        }

        private void COM_cbox_DropDown(object sender, EventArgs e)
        {
            COM_cbox.Items.Clear();
            string[] available_ports = SerialPort.GetPortNames();
            Array.Sort(available_ports);
            int index = 0;
            while(index <= available_ports.GetUpperBound(0))
            {
                COM_cbox.Items.Add(available_ports[index]);
                index++;
            }
        }

        private void ser_connect_butt_Click(object sender, EventArgs e)
        {
            // if com port is not open try to connect
            if (ser_connect_butt.Text == "Connect")
            {
                // set com port to number attempt to connect and catch expection if it fails
                try
                {
                    ComPort.PortName = Convert.ToString(COM_cbox.Text);
                    ComPort.Open();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    return;
                }
            }
            // else if already connect, disconnect it
            else if(ser_connect_butt.Text == "Disconnect")
            {
                try
                {
                    ComPort.Close();
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    return;
                }
            }            
        }

        delegate void SerialInputCallback(string text);

        private void SerialInput(string text)
        {
            this.serial_output_box.Text += text;
            this.serial_output_box.Text += '\n';
        }

        private void ComPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string incoming_data = ComPort.ReadLine();
            this.BeginInvoke(new SerialInputCallback(SerialInput), new object[] { incoming_data });
        }

        private void send_button_Click(object sender, EventArgs e)
        {
            try
            {
                ComPort.WriteLine("Hello World");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
        }

        private void connected_timer_Tick(object sender, EventArgs e)
        {
            if (ComPort.IsOpen)
            {
                ser_connect_butt.Text = "Disconnect";
                com_status_label.Text = "Connected";
                com_status_label.BackColor = Color.Green;
            }
            else
            {
                ser_connect_butt.Text = "Connect";
                com_status_label.Text = "Disconnected";
                com_status_label.BackColor = Color.Red;
            }
        }

        private void led_cube_cmd_box_SelectionChangeCommitted(object sender, EventArgs e)
        {
            // update arg1 and arg2 drop down boxes based on command choice
            switch (led_cube_cmd_box.Text)
            {
                case "LOAD":
                    {
                        led_cube_arg1_num_box.Visible = false;
                        led_cube_arg2_num_box.Visible = false;
                        led_cube_arg1_box.Visible = false;                        
                        led_cube_arg2_box.Visible = false;
                        led_cube_arg1_label.Text = "";
                        led_cube_arg2_label.Text = "";
                    }
                    break;
                case "DELAY":
                    {
                        led_cube_arg1_box.Visible = false;                        
                        led_cube_arg2_box.Visible = false;
                        led_cube_arg1_num_box.Visible = true;
                        led_cube_arg1_num_box.Value = 0;
                        led_cube_arg2_num_box.Visible = false;
                        led_cube_arg1_label.Text = "Time [ms]";
                        led_cube_arg2_label.Text = "";
                    }
                    break;
                case "ROTATE":
                    {
                        led_cube_arg1_num_box.Visible = false;
                        led_cube_arg2_num_box.Visible = false;
                        led_cube_arg1_box.Items.Clear();
                        led_cube_arg1_label.Text = "Axis";
                        led_cube_arg1_box.Visible = true;
                        led_cube_arg2_box.Items.Clear();
                        led_cube_arg2_label.Text = "Direction";
                        led_cube_arg2_box.Visible = true;
                        

                        led_cube_arg1_box.Items.Add("X-Axis");
                        led_cube_arg1_box.Items.Add("Y-Axis");
                        led_cube_arg1_box.Items.Add("Z-Axis");
                        led_cube_arg2_box.Items.Add("Positive");
                        led_cube_arg2_box.Items.Add("Negative");

                        led_cube_arg1_box.SelectedIndex = 0;
                        led_cube_arg2_box.SelectedIndex = 0;
                    }
                    break;
                case "LOOP":
                    {
                        led_cube_arg1_box.Visible = false;
                        led_cube_arg2_box.Visible = false;
                        led_cube_arg1_num_box.Visible = true;
                        led_cube_arg1_num_box.Value = 0;
                        led_cube_arg2_num_box.Visible = true;
                        led_cube_arg2_num_box.Value = 0;
                        led_cube_arg1_label.Text = "Instructions";
                        led_cube_arg2_label.Text = "Loops";
                    }
                    break;
                case "MIRROR":
                    {
                        led_cube_arg1_num_box.Visible = false;
                        led_cube_arg2_num_box.Visible = false;
                        led_cube_arg1_box.Items.Clear();
                        led_cube_arg1_label.Text = "Plane";
                        led_cube_arg1_box.Visible = true;
                        led_cube_arg2_label.Text = "";
                        led_cube_arg2_box.Visible = false;

                        led_cube_arg1_box.Items.Add("YZ Plane");
                        led_cube_arg1_box.Items.Add("ZX Plane");
                        led_cube_arg1_box.Items.Add("XY Plane");

                        led_cube_arg1_box.SelectedIndex = 0;
                    }
                    break;
                case "TRANSLATE":
                    {
                        led_cube_arg1_num_box.Visible = false;
                        led_cube_arg2_num_box.Visible = false;
                        led_cube_arg1_box.Items.Clear();
                        led_cube_arg1_label.Text = "Axis";
                        led_cube_arg1_box.Visible = true;
                        led_cube_arg2_box.Items.Clear();
                        led_cube_arg2_label.Text = "Direction";
                        led_cube_arg2_box.Visible = true;
                        
                        led_cube_arg1_box.Items.Add("X-Axis");
                        led_cube_arg1_box.Items.Add("Y-Axis");
                        led_cube_arg1_box.Items.Add("Z-Axis");

                        led_cube_arg2_box.Items.Add("Positive");
                        led_cube_arg2_box.Items.Add("Negative");

                        led_cube_arg1_box.SelectedIndex = 0;
                        led_cube_arg2_box.SelectedIndex = 0;
                    }
                    break;
                case "TRANSLATE CLEAR":
                    {
                        led_cube_arg1_num_box.Visible = false;
                        led_cube_arg2_num_box.Visible = false;                        
                        led_cube_arg1_box.Visible = false;                        
                        led_cube_arg2_box.Visible = false;
                        led_cube_arg1_label.Text = "";
                        led_cube_arg2_label.Text = "";
                    }
                    break;
            }
        }

        private void led_cube_activate_butt_Click(object sender, EventArgs e)
        {
            if(led_cube_activate_butt.Text == "Activate")
            {
                // send activate command
                try
                {
                    ComPort.WriteLine("7");
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    return;
                }
                
                led_cube_activate_butt.Text = "Deactivate";
            }
            else if(led_cube_activate_butt.Text == "Deactivate")
            {
                // send deactivate command
                try
                {
                    ComPort.WriteLine("8");
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    return;
                }

                led_cube_activate_butt.Text = "Activate";
            }
        }

        private void led_cube_write_butt_Click(object sender, EventArgs e)
        {
            if (led_cube_write_butt.Text == "Start Write")
            {
                // send start write command
                try
                {
                    ComPort.WriteLine("5");
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    return;
                }
                
                led_cube_write_butt.Text = "Stop Write";
            }
            else if (led_cube_write_butt.Text == "Stop Write")
            {
                // send stop write command
                try
                {
                    ComPort.WriteLine("6");                    
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    return;
                }
                
                led_cube_write_butt.Text = "Start Write";
            }
        }

        private void led_cube_send_butt_Click(object sender, EventArgs e)
        {
            // convert the tick boxes to a pattern of LEDs
            UInt16[] checkbox_decoder = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
            UInt16[] cube_buffer = { 0, 0, 0 };
            int index;
            for(index = 0; index < 9; index++)
            {
                if (layer0_chbox.GetItemChecked(index))
                {
                    cube_buffer[0] |= (UInt16)(1 << checkbox_decoder[index]);
                }
                if (layer1_chbox.GetItemChecked(index))
                {
                    cube_buffer[1] |= (UInt16)(1 << checkbox_decoder[index]);
                }
                if (layer2_chbox.GetItemChecked(index))
                {
                    cube_buffer[2] |= (UInt16)(1 << checkbox_decoder[index]);
                }
            }

            string output_string = "";
                        
            switch (led_cube_cmd_box.Text)
            {
                case "LOAD":
                    {
                        output_string = "0,";
                        for(index = 0; index < 3; index++)
                        {
                            output_string += Convert.ToString(cube_buffer[index]);
                            if(index != 2) { output_string += ','; }
                        }                            
                    }
                    break;
                case "DELAY":
                    {
                        output_string = "10," + Convert.ToString(led_cube_arg1_num_box.Value);
                    }
                    break;
                case "ROTATE":
                    {
                        output_string = "1,";
                        output_string += Convert.ToString(led_cube_arg1_box.SelectedIndex) + ',' ;
                        output_string += Convert.ToString(led_cube_arg2_box.SelectedIndex);
                    }
                    break;
                case "LOOP":
                    {
                        output_string = "10,";
                        output_string += Convert.ToString(led_cube_arg1_num_box.Value) + ',';
                        output_string += Convert.ToString(led_cube_arg2_num_box.Value);
                    }
                    break;
                case "MIRROR":
                    {
                        output_string = "2,";
                        output_string += Convert.ToString(led_cube_arg1_box.SelectedIndex);
                    }
                    break;
                case "TRANSLATE":
                    {
                        output_string = "3,";
                        output_string += Convert.ToString(led_cube_arg1_box.SelectedIndex) + ',';
                        output_string += Convert.ToString(led_cube_arg2_box.SelectedIndex) + ',';
                        for (index = 0; index < 3; index++)
                        {
                            output_string += Convert.ToString(cube_buffer[index]);
                            if (index != 2) { output_string += ','; }
                        }
                    }
                    break;
                case "TRANSLATE CLEAR":
                    {
                        output_string = "4";
                    }
                    break;
            }
            try
            {
                ComPort.WriteLine(output_string);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
