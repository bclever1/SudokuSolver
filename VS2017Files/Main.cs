using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;


namespace SudokuInterface
{
    public partial class Main : Form
    {
        const int boardSize = 9;

        int[,] myUserBoard;
        int[,] myWorkingBoard;
        

        TextBox[,] myTextBoxes;
        TextBox[,] myResultsDisplay;

        System.Timers.Timer aTimer;

        public Main()
        {
            InitializeComponent();

            try
            {
                myUserBoard = new int[70, 10];
                myWorkingBoard = new int[70, 10];
                myResultsDisplay = new TextBox[70, 10];
                myTextBoxes = new TextBox[70, 10];

                myTextBoxes[1, 1] = textBox1;
                myTextBoxes[1, 2] = textBox2;
                myTextBoxes[1, 3] = textBox3;
                myTextBoxes[1, 4] = textBox4;
                myTextBoxes[1, 5] = textBox5;
                myTextBoxes[1, 6] = textBox6;
                myTextBoxes[1, 7] = textBox7;
                myTextBoxes[1, 8] = textBox8;
                myTextBoxes[1, 9] = textBox9;

                myTextBoxes[2, 1] = textBox10;
                myTextBoxes[2, 2] = textBox11;
                myTextBoxes[2, 3] = textBox12;
                myTextBoxes[2, 4] = textBox13;
                myTextBoxes[2, 5] = textBox14;
                myTextBoxes[2, 6] = textBox15;
                myTextBoxes[2, 7] = textBox16;
                myTextBoxes[2, 8] = textBox17;
                myTextBoxes[2, 9] = textBox18;

                myTextBoxes[3, 1] = textBox19;
                myTextBoxes[3, 2] = textBox20;
                myTextBoxes[3, 3] = textBox21;
                myTextBoxes[3, 4] = textBox22;
                myTextBoxes[3, 5] = textBox23;
                myTextBoxes[3, 6] = textBox24;
                myTextBoxes[3, 7] = textBox25;
                myTextBoxes[3, 8] = textBox26;
                myTextBoxes[3, 9] = textBox27;

                myTextBoxes[4, 1] = textBox28;
                myTextBoxes[4, 2] = textBox29;
                myTextBoxes[4, 3] = textBox30;
                myTextBoxes[4, 4] = textBox31;
                myTextBoxes[4, 5] = textBox32;
                myTextBoxes[4, 6] = textBox33;
                myTextBoxes[4, 7] = textBox34;
                myTextBoxes[4, 8] = textBox35;
                myTextBoxes[4, 9] = textBox36;

                myTextBoxes[5, 1] = textBox37;
                myTextBoxes[5, 2] = textBox38;
                myTextBoxes[5, 3] = textBox39;
                myTextBoxes[5, 4] = textBox40;
                myTextBoxes[5, 5] = textBox41;
                myTextBoxes[5, 6] = textBox42;
                myTextBoxes[5, 7] = textBox43;
                myTextBoxes[5, 8] = textBox44;
                myTextBoxes[5, 9] = textBox45;

                myTextBoxes[6, 1] = textBox46;
                myTextBoxes[6, 2] = textBox47;
                myTextBoxes[6, 3] = textBox48;
                myTextBoxes[6, 4] = textBox49;
                myTextBoxes[6, 5] = textBox50;
                myTextBoxes[6, 6] = textBox51;
                myTextBoxes[6, 7] = textBox52;
                myTextBoxes[6, 8] = textBox53;
                myTextBoxes[6, 9] = textBox54;

                myTextBoxes[7, 1] = textBox55;
                myTextBoxes[7, 2] = textBox56;
                myTextBoxes[7, 3] = textBox57;
                myTextBoxes[7, 4] = textBox58;
                myTextBoxes[7, 5] = textBox59;
                myTextBoxes[7, 6] = textBox60;
                myTextBoxes[7, 7] = textBox61;
                myTextBoxes[7, 8] = textBox62;
                myTextBoxes[7, 9] = textBox63;

                myTextBoxes[8, 1] = textBox64;
                myTextBoxes[8, 2] = textBox65;
                myTextBoxes[8, 3] = textBox66;
                myTextBoxes[8, 4] = textBox67;
                myTextBoxes[8, 5] = textBox68;
                myTextBoxes[8, 6] = textBox69;
                myTextBoxes[8, 7] = textBox70;
                myTextBoxes[8, 8] = textBox71;
                myTextBoxes[8, 9] = textBox72;

                myTextBoxes[9, 1] = textBox73;
                myTextBoxes[9, 2] = textBox74;
                myTextBoxes[9, 3] = textBox75;
                myTextBoxes[9, 4] = textBox76;
                myTextBoxes[9, 5] = textBox77;
                myTextBoxes[9, 6] = textBox78;
                myTextBoxes[9, 7] = textBox79;
                myTextBoxes[9, 8] = textBox80;
                myTextBoxes[9, 9] = textBox81;

                myResultsDisplay[1, 1] = textBox162;
                myResultsDisplay[1, 2] = textBox161;
                myResultsDisplay[1, 3] = textBox160;
                myResultsDisplay[1, 4] = textBox159;
                myResultsDisplay[1, 5] = textBox158;
                myResultsDisplay[1, 6] = textBox157;
                myResultsDisplay[1, 7] = textBox156;
                myResultsDisplay[1, 8] = textBox155;
                myResultsDisplay[1, 9] = textBox154;

                myResultsDisplay[2, 1] = textBox153;
                myResultsDisplay[2, 2] = textBox152;
                myResultsDisplay[2, 3] = textBox151;
                myResultsDisplay[2, 4] = textBox150;
                myResultsDisplay[2, 5] = textBox149;
                myResultsDisplay[2, 6] = textBox148;
                myResultsDisplay[2, 7] = textBox147;
                myResultsDisplay[2, 8] = textBox146;
                myResultsDisplay[2, 9] = textBox145;

                myResultsDisplay[3, 1] = textBox144;
                myResultsDisplay[3, 2] = textBox143;
                myResultsDisplay[3, 3] = textBox142;
                myResultsDisplay[3, 4] = textBox141;
                myResultsDisplay[3, 5] = textBox140;
                myResultsDisplay[3, 6] = textBox139;
                myResultsDisplay[3, 7] = textBox138;
                myResultsDisplay[3, 8] = textBox137;
                myResultsDisplay[3, 9] = textBox136;

                myResultsDisplay[4, 1] = textBox135;
                myResultsDisplay[4, 2] = textBox134;
                myResultsDisplay[4, 3] = textBox133;
                myResultsDisplay[4, 4] = textBox132;
                myResultsDisplay[4, 5] = textBox131;
                myResultsDisplay[4, 6] = textBox130;
                myResultsDisplay[4, 7] = textBox129;
                myResultsDisplay[4, 8] = textBox128;
                myResultsDisplay[4, 9] = textBox127;

                myResultsDisplay[5, 1] = textBox126;
                myResultsDisplay[5, 2] = textBox125;
                myResultsDisplay[5, 3] = textBox124;
                myResultsDisplay[5, 4] = textBox123;
                myResultsDisplay[5, 5] = textBox122;
                myResultsDisplay[5, 6] = textBox121;
                myResultsDisplay[5, 7] = textBox120;
                myResultsDisplay[5, 8] = textBox119;
                myResultsDisplay[5, 9] = textBox118;

                myResultsDisplay[6, 1] = textBox117;
                myResultsDisplay[6, 2] = textBox116;
                myResultsDisplay[6, 3] = textBox115;
                myResultsDisplay[6, 4] = textBox114;
                myResultsDisplay[6, 5] = textBox113;
                myResultsDisplay[6, 6] = textBox112;
                myResultsDisplay[6, 7] = textBox111;
                myResultsDisplay[6, 8] = textBox110;
                myResultsDisplay[6, 9] = textBox109;

                myResultsDisplay[7, 1] = textBox108;
                myResultsDisplay[7, 2] = textBox107;
                myResultsDisplay[7, 3] = textBox106;
                myResultsDisplay[7, 4] = textBox105;
                myResultsDisplay[7, 5] = textBox104;
                myResultsDisplay[7, 6] = textBox103;
                myResultsDisplay[7, 7] = textBox102;
                myResultsDisplay[7, 8] = textBox101;
                myResultsDisplay[7, 9] = textBox100;

                myResultsDisplay[8, 1] = textBox99;
                myResultsDisplay[8, 2] = textBox98;
                myResultsDisplay[8, 3] = textBox97;
                myResultsDisplay[8, 4] = textBox96;
                myResultsDisplay[8, 5] = textBox95;
                myResultsDisplay[8, 6] = textBox94;
                myResultsDisplay[8, 7] = textBox93;
                myResultsDisplay[8, 8] = textBox92;
                myResultsDisplay[8, 9] = textBox91;

                myResultsDisplay[9, 1] = textBox90;
                myResultsDisplay[9, 2] = textBox89;
                myResultsDisplay[9, 3] = textBox88;
                myResultsDisplay[9, 4] = textBox87;
                myResultsDisplay[9, 5] = textBox86;
                myResultsDisplay[9, 6] = textBox85;
                myResultsDisplay[9, 7] = textBox84;
                myResultsDisplay[9, 8] = textBox83;
                myResultsDisplay[9, 9] = textBox82;

            }
            catch (Exception e)
            {

            }
        }

        private void DebugSetup()
        {
            
            myTextBoxes[1, 1].Text = string.Empty;
            myTextBoxes[1, 2].Text = 8.ToString();
            myTextBoxes[1, 3].Text = string.Empty;
            myTextBoxes[1, 4].Text = string.Empty;
            myTextBoxes[1, 5].Text = string.Empty;
            myTextBoxes[1, 6].Text = string.Empty;
            myTextBoxes[1, 7].Text = 7.ToString();
            myTextBoxes[1, 8].Text = string.Empty;
            myTextBoxes[1, 9].Text = string.Empty;

            myTextBoxes[2, 1].Text = 2.ToString();
            myTextBoxes[2, 2].Text = string.Empty;
            myTextBoxes[2, 3].Text = 7.ToString();
            myTextBoxes[2, 4].Text = string.Empty;
            myTextBoxes[2, 5].Text = 6.ToString();
            myTextBoxes[2, 6].Text = string.Empty;
            myTextBoxes[2, 7].Text = 4.ToString();
            myTextBoxes[2, 8].Text = string.Empty;
            myTextBoxes[2, 9].Text = string.Empty;

            myTextBoxes[3, 1].Text = string.Empty;
            myTextBoxes[3, 2].Text = string.Empty;
            myTextBoxes[3, 3].Text = 5.ToString();
            myTextBoxes[3, 4].Text = string.Empty;
            myTextBoxes[3, 5].Text = string.Empty;
            myTextBoxes[3, 6].Text = string.Empty;
            myTextBoxes[3, 7].Text = string.Empty;
            myTextBoxes[3, 8].Text = 9.ToString();
            myTextBoxes[3, 9].Text = 2.ToString();

            myTextBoxes[4, 1].Text = 6.ToString();
            myTextBoxes[4, 2].Text = string.Empty;
            myTextBoxes[4, 3].Text = 1.ToString();
            myTextBoxes[4, 4].Text = string.Empty;
            myTextBoxes[4, 5].Text = string.Empty;
            myTextBoxes[4, 6].Text = 8.ToString();
            myTextBoxes[4, 7].Text = 9.ToString();
            myTextBoxes[4, 8].Text = string.Empty;
            myTextBoxes[4, 9].Text = 5.ToString();

            myTextBoxes[5, 1].Text = 7.ToString();
            myTextBoxes[5, 2].Text = 9.ToString();
            myTextBoxes[5, 3].Text = string.Empty;
            myTextBoxes[5, 4].Text = 5.ToString();
            myTextBoxes[5, 5].Text = string.Empty;
            myTextBoxes[5, 6].Text = string.Empty;
            myTextBoxes[5, 7].Text = 2.ToString();
            myTextBoxes[5, 8].Text = string.Empty;
            myTextBoxes[5, 9].Text = 1.ToString();

            myTextBoxes[6, 1].Text = string.Empty;
            myTextBoxes[6, 2].Text = string.Empty;
            myTextBoxes[6, 3].Text = string.Empty;
            myTextBoxes[6, 4].Text = string.Empty;
            myTextBoxes[6, 5].Text = string.Empty;
            myTextBoxes[6, 6].Text = 7.ToString();
            myTextBoxes[6, 7].Text = string.Empty;
            myTextBoxes[6, 8].Text = 8.ToString();
            myTextBoxes[6, 9].Text = string.Empty;

            myTextBoxes[7, 1].Text = string.Empty;
            myTextBoxes[7, 2].Text = string.Empty;
            myTextBoxes[7, 3].Text = 6.ToString();
            myTextBoxes[7, 4].Text = 2.ToString();
            myTextBoxes[7, 5].Text = 8.ToString();
            myTextBoxes[7, 6].Text = string.Empty;
            myTextBoxes[7, 7].Text = string.Empty;
            myTextBoxes[7, 8].Text = string.Empty;
            myTextBoxes[7, 9].Text = string.Empty;

            myTextBoxes[8, 1].Text = string.Empty;
            myTextBoxes[8, 2].Text = string.Empty;
            myTextBoxes[8, 3].Text = string.Empty;
            myTextBoxes[8, 4].Text = string.Empty;
            myTextBoxes[8, 5].Text = string.Empty;
            myTextBoxes[8, 6].Text = string.Empty;
            myTextBoxes[8, 7].Text = string.Empty;
            myTextBoxes[8, 8].Text = string.Empty;
            myTextBoxes[8, 9].Text = string.Empty;

            myTextBoxes[9, 1].Text = 5.ToString();
            myTextBoxes[9, 2].Text = string.Empty;
            myTextBoxes[9, 3].Text = string.Empty;
            myTextBoxes[9, 4].Text = string.Empty;
            myTextBoxes[9, 5].Text = 9.ToString();
            myTextBoxes[9, 6].Text = string.Empty;
            myTextBoxes[9, 7].Text = string.Empty;
            myTextBoxes[9, 8].Text = string.Empty;
            myTextBoxes[9, 9].Text = string.Empty;


#if false


            myTextBoxes[1, 1].Text = string.Empty;
            myTextBoxes[1, 2].Text = 6.ToString();
            myTextBoxes[1, 3].Text = string.Empty;
            myTextBoxes[1, 4].Text = 3.ToString();
            myTextBoxes[1, 5].Text = 8.ToString();
            myTextBoxes[1, 6].Text = 5.ToString();
            myTextBoxes[1, 7].Text = 2.ToString();
            myTextBoxes[1, 8].Text = 1.ToString();
            myTextBoxes[1, 9].Text = string.Empty;

            myTextBoxes[2, 1].Text = string.Empty;
            myTextBoxes[2, 2].Text = 2.ToString();
            myTextBoxes[2, 3].Text = string.Empty;
            myTextBoxes[2, 4].Text = string.Empty;
            myTextBoxes[2, 5].Text = 4.ToString();
            myTextBoxes[2, 6].Text = 1.ToString();
            myTextBoxes[2, 7].Text = 9.ToString();
            myTextBoxes[2, 8].Text = string.Empty;
            myTextBoxes[2, 9].Text = string.Empty;

            myTextBoxes[3, 1].Text = 3.ToString();
            myTextBoxes[3, 2].Text = 1.ToString();
            myTextBoxes[3, 3].Text = 4.ToString();
            myTextBoxes[3, 4].Text = 9.ToString();
            myTextBoxes[3, 5].Text = 2.ToString();
            myTextBoxes[3, 6].Text = string.Empty;
            myTextBoxes[3, 7].Text = 8.ToString();
            myTextBoxes[3, 8].Text = string.Empty;
            myTextBoxes[3, 9].Text = 7.ToString();

            myTextBoxes[4, 1].Text = 4.ToString();
            myTextBoxes[4, 2].Text = 9.ToString();
            myTextBoxes[4, 3].Text = 2.ToString();
            myTextBoxes[4, 4].Text = 8.ToString();
            myTextBoxes[4, 5].Text = string.Empty;
            myTextBoxes[4, 6].Text = 3.ToString();
            myTextBoxes[4, 7].Text = 1.ToString();
            myTextBoxes[4, 8].Text = 7.ToString();
            myTextBoxes[4, 9].Text = 5.ToString();

            myTextBoxes[5, 1].Text = string.Empty;
            myTextBoxes[5, 2].Text = 8.ToString();
            myTextBoxes[5, 3].Text = 6.ToString();
            myTextBoxes[5, 4].Text = string.Empty;
            myTextBoxes[5, 5].Text = 1.ToString();
            myTextBoxes[5, 6].Text = string.Empty;
            myTextBoxes[5, 7].Text = 3.ToString();
            myTextBoxes[5, 8].Text = string.Empty;
            myTextBoxes[5, 9].Text = string.Empty;

            myTextBoxes[6, 1].Text = string.Empty;
            myTextBoxes[6, 2].Text = 3.ToString();
            myTextBoxes[6, 3].Text = 7.ToString();
            myTextBoxes[6, 4].Text = 2.ToString();
            myTextBoxes[6, 5].Text = 5.ToString();
            myTextBoxes[6, 6].Text = string.Empty;
            myTextBoxes[6, 7].Text = 4.ToString();
            myTextBoxes[6, 8].Text = 6.ToString();
            myTextBoxes[6, 9].Text = string.Empty;

            myTextBoxes[7, 1].Text = 6.ToString();
            myTextBoxes[7, 2].Text = string.Empty;
            myTextBoxes[7, 3].Text = string.Empty;
            myTextBoxes[7, 4].Text = 5.ToString();
            myTextBoxes[7, 5].Text = 9.ToString();
            myTextBoxes[7, 6].Text = string.Empty;
            myTextBoxes[7, 7].Text = 7.ToString();
            myTextBoxes[7, 8].Text = 2.ToString();
            myTextBoxes[7, 9].Text = string.Empty;

            myTextBoxes[8, 1].Text = string.Empty;
            myTextBoxes[8, 2].Text = string.Empty;
            myTextBoxes[8, 3].Text = 3.ToString();
            myTextBoxes[8, 4].Text = 1.ToString();
            myTextBoxes[8, 5].Text = 7.ToString();
            myTextBoxes[8, 6].Text = string.Empty;
            myTextBoxes[8, 7].Text = 6.ToString();
            myTextBoxes[8, 8].Text = string.Empty;
            myTextBoxes[8, 9].Text = 9.ToString();

            myTextBoxes[9, 1].Text = string.Empty;
            myTextBoxes[9, 2].Text = string.Empty;
            myTextBoxes[9, 3].Text = 8.ToString();
            myTextBoxes[9, 4].Text = string.Empty;
            myTextBoxes[9, 5].Text = string.Empty;
            myTextBoxes[9, 6].Text = string.Empty;
            myTextBoxes[9, 7].Text = 5.ToString();
            myTextBoxes[9, 8].Text = 4.ToString();
            myTextBoxes[9, 9].Text = string.Empty;
#endif

        }

        private void textBox11_TextChanged(object sender, EventArgs e)
        {

        }

        private int getValue(ref TextBox tb)
        {
            if (tb.Text == string.Empty) return 0;
            return Int32.Parse(tb.Text);
        }

        private void solveButton_Click(object sender, EventArgs e)
        {
            SudokuLibApi.Reset();

            // Initialize based on the user input
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9;++j)
                {
                    myUserBoard[i, j] = getValue(ref myTextBoxes[i,j]);
                    myWorkingBoard[i, j] = myUserBoard[i, j];

                    if (!(0 <= myUserBoard[i,j] && myUserBoard[i,j] <= 9))
                    {
                        string s = "Square ( " + i.ToString() + ", " + j.ToString() + " ) has an illegal value.";
                        ErrorMessage em = new ErrorMessage(s);
                        em.ShowDialog();
                        return;
                    }
                }
            }

            // Convert the user input to a byte array to send to the Sudoku 
            byte[] myBytes = new byte[81];

            int byteIdx = 0;
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    myBytes[byteIdx] = Convert.ToByte(myWorkingBoard[i, j]);
                    ++byteIdx;
                }
            }

            // Call the Sudoko API to initialize the board
            SudokuLibApi.Initialize(myBytes);
            SudokuLibApi.Solve();

            ResetResultsBoard();
            DisplayResultsBoard();
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            SudokuLibApi.Reset();

            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    myTextBoxes[i,j].Text = string.Empty;
                    myResultsDisplay[i, j].Text = string.Empty;
                }
            }

            label1.Text = "Manual entry... 0 for empty boxes.";
            manualInputBox.Text = string.Empty;
        }

        private void ResetResultsBoard()
        {
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    myResultsDisplay[i, j].Text = string.Empty;
                }
            }
        }

        private void DisplayResultsBoard()
        {
            IntPtr theCurrentBoard = SudokuLibApi.GetCurrentBoard();
            byte[] bytes = new byte[810];
            Marshal.Copy(theCurrentBoard, bytes, 0, 810);

            int rowIdx = 1;
            int colIdx = 1;

            for (int i = 0; i < 810; ++i)
            {
                if (bytes[i] == 0)
                {
                    ++colIdx;
                    if (colIdx > 9)
                    {
                        colIdx = 1;
                        ++rowIdx;
                        if (rowIdx > 9)
                        {
                            break;
                        }
                    }
                    ++i;
                }

                myResultsDisplay[rowIdx, colIdx].Text += bytes[i].ToString();
            }
        }

        private void defaultButton_Click(object sender, EventArgs e)
        {
            DebugSetup();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SudokuLibApi.EnableGuessing();
        }

        private void disableGuessing_Click(object sender, EventArgs e)
        {
            SudokuLibApi.DisableGuessing();
        }

        private void manualInputBox_TextChanged(object sender, EventArgs e)
        {
            string[] s = manualInputBox.Text.Split(' ');
            int col = 1, row = 1;
            foreach (string userEntry in s)
            {
                if (row > 9 || col > 9)
                {
                    label1.Text = "81 entries only please!";
                }
                else
                {
                    label1.Text = s.Length + " entries specified";
                    myTextBoxes[row, col].Text = userEntry;
                    ++col;
                    if (col > 9)
                    {
                        ++row;
                        col = 1;
                    }
                }
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            Close();
        }
    }
}
