﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SudokuInterface
{
    public partial class ErrorMessage : Form
    {
        public ErrorMessage(string theMsg)
        {
            InitializeComponent();
            label1.Text = theMsg;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
