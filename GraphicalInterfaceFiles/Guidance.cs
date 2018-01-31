using System;
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
    public partial class Guidance : Form
    {
        public static bool [] dontShow = { false, false, false };

        private int myMsgId;

        public Guidance(string theMessage, int theMsgId)
        {
            InitializeComponent();
            label1.Text = theMessage;
            myMsgId = theMsgId;
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            if (dontShowCheckBox.Checked == true)
            {
                dontShow[myMsgId] = true;
            }
            Close();
        }
    }
}
