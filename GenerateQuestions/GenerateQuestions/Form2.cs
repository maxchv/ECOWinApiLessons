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
    public partial class Form2 : Form
    {
        public int MaxNumber { get; set; }
        public Form2(int init)
        {
            InitializeComponent();
            MaxNumber = init;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            textBox1.Text = MaxNumber.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int n = 0;
            int.TryParse(textBox1.Text, out n);
            MaxNumber = n;
            DialogResult = DialogResult.OK;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
