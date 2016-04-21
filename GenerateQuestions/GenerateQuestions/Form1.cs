using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GenerateQuestions
{
    public partial class Form1 : Form
    {
        Random rand = new Random();
        int[] n = new int[3];
        int max = 18;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            generate();
            label1.Text = n[0].ToString();
            label2.Text = n[1].ToString();
            label3.Text = n[2].ToString();
        }

        private void generate()
        {
            do
            {
                for(int i=0; i<n.Length; i++)
                {
                    n[i] = rand.Next(max)+1;
                }
            } while (n[0] == n[1] && n[1] == n[2]);
        }

        private void optionsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 dlg = new Form2(max);
            dlg.MaxNumber = max;
            if(dlg.ShowDialog() == DialogResult.OK)
            {
                max = dlg.MaxNumber;
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
