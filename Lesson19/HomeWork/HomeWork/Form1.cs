using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HomeWork
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void fontToolStripMenuItem_Click(object sender, EventArgs e)
        {            
            Control btn = contextMenuStrip1.SourceControl;
            if(btn != null)
            {
                FontDialog dlg = new FontDialog();
                dlg.Font = btn.Font;
                if(dlg.ShowDialog() == DialogResult.OK)
                {
                    btn.Font = dlg.Font;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;
            lblResult.Text = btn.Text;
        }
    }
}
