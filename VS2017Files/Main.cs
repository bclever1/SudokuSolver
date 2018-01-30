using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;


namespace SudokuInterface
{
    public partial class Main : Form
    {
        public TextBox[,] myInputBoxes;
        TextBox[,] myResultsDisplay;

        SolverFSM mySolverFSM;

        Thread myAPIServiceThread;
        Thread myFSMThread;

        public Main()
        {
            InitializeComponent();

            try
            {
                numGuesses.Text = "0";
                lowestScoreLabel.Text = "0";
                surrenderCountLabel.Text = "0";
                invalidCountLabel.Text = "0";

                enableGuessingButton.Enabled = false;
                disableGuessing.Enabled = false;

                mySolverFSM = new SolverFSM(this);

                // Start the threads
                // This thread communicates with the solver engine in the DLL
                myAPIServiceThread = new Thread(() => StartAPIServices());
                myAPIServiceThread.IsBackground = true;
                myAPIServiceThread.Start();

                // This thread runs the display FSM by getting results from the server engine.
                myFSMThread = new Thread(() => mySolverFSM.Run());
                myFSMThread.IsBackground = true;
                myFSMThread.Start();
            }
            catch (Exception e1)
            {
                ErrorMessage em = new ErrorMessage(e1.Message);
                em.ShowDialog();
            }

            try
            {
                myResultsDisplay = new TextBox[10, 10];
                myInputBoxes = new TextBox[10, 10];

                myInputBoxes[1, 1] = textBox1;
                myInputBoxes[1, 2] = textBox2;
                myInputBoxes[1, 3] = textBox3;
                myInputBoxes[1, 4] = textBox4;
                myInputBoxes[1, 5] = textBox5;
                myInputBoxes[1, 6] = textBox6;
                myInputBoxes[1, 7] = textBox7;
                myInputBoxes[1, 8] = textBox8;
                myInputBoxes[1, 9] = textBox9;

                myInputBoxes[2, 1] = textBox10;
                myInputBoxes[2, 2] = textBox11;
                myInputBoxes[2, 3] = textBox12;
                myInputBoxes[2, 4] = textBox13;
                myInputBoxes[2, 5] = textBox14;
                myInputBoxes[2, 6] = textBox15;
                myInputBoxes[2, 7] = textBox16;
                myInputBoxes[2, 8] = textBox17;
                myInputBoxes[2, 9] = textBox18;

                myInputBoxes[3, 1] = textBox19;
                myInputBoxes[3, 2] = textBox20;
                myInputBoxes[3, 3] = textBox21;
                myInputBoxes[3, 4] = textBox22;
                myInputBoxes[3, 5] = textBox23;
                myInputBoxes[3, 6] = textBox24;
                myInputBoxes[3, 7] = textBox25;
                myInputBoxes[3, 8] = textBox26;
                myInputBoxes[3, 9] = textBox27;

                myInputBoxes[4, 1] = textBox28;
                myInputBoxes[4, 2] = textBox29;
                myInputBoxes[4, 3] = textBox30;
                myInputBoxes[4, 4] = textBox31;
                myInputBoxes[4, 5] = textBox32;
                myInputBoxes[4, 6] = textBox33;
                myInputBoxes[4, 7] = textBox34;
                myInputBoxes[4, 8] = textBox35;
                myInputBoxes[4, 9] = textBox36;

                myInputBoxes[5, 1] = textBox37;
                myInputBoxes[5, 2] = textBox38;
                myInputBoxes[5, 3] = textBox39;
                myInputBoxes[5, 4] = textBox40;
                myInputBoxes[5, 5] = textBox41;
                myInputBoxes[5, 6] = textBox42;
                myInputBoxes[5, 7] = textBox43;
                myInputBoxes[5, 8] = textBox44;
                myInputBoxes[5, 9] = textBox45;

                myInputBoxes[6, 1] = textBox46;
                myInputBoxes[6, 2] = textBox47;
                myInputBoxes[6, 3] = textBox48;
                myInputBoxes[6, 4] = textBox49;
                myInputBoxes[6, 5] = textBox50;
                myInputBoxes[6, 6] = textBox51;
                myInputBoxes[6, 7] = textBox52;
                myInputBoxes[6, 8] = textBox53;
                myInputBoxes[6, 9] = textBox54;

                myInputBoxes[7, 1] = textBox55;
                myInputBoxes[7, 2] = textBox56;
                myInputBoxes[7, 3] = textBox57;
                myInputBoxes[7, 4] = textBox58;
                myInputBoxes[7, 5] = textBox59;
                myInputBoxes[7, 6] = textBox60;
                myInputBoxes[7, 7] = textBox61;
                myInputBoxes[7, 8] = textBox62;
                myInputBoxes[7, 9] = textBox63;

                myInputBoxes[8, 1] = textBox64;
                myInputBoxes[8, 2] = textBox65;
                myInputBoxes[8, 3] = textBox66;
                myInputBoxes[8, 4] = textBox67;
                myInputBoxes[8, 5] = textBox68;
                myInputBoxes[8, 6] = textBox69;
                myInputBoxes[8, 7] = textBox70;
                myInputBoxes[8, 8] = textBox71;
                myInputBoxes[8, 9] = textBox72;

                myInputBoxes[9, 1] = textBox73;
                myInputBoxes[9, 2] = textBox74;
                myInputBoxes[9, 3] = textBox75;
                myInputBoxes[9, 4] = textBox76;
                myInputBoxes[9, 5] = textBox77;
                myInputBoxes[9, 6] = textBox78;
                myInputBoxes[9, 7] = textBox79;
                myInputBoxes[9, 8] = textBox80;
                myInputBoxes[9, 9] = textBox81;

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

        //==================================================
        // Start communicating with the solver engine.
        private void StartAPIServices()
        {
            while (true)
            {
                APIMonitor.Instance.Run();
                Thread.Sleep(100);
            }
        }

        //==================================================
        // Convert textbox data into int
        private int getValue(ref TextBox tb)
        {
            if (tb.Text == string.Empty)
            {
                return 0;
            }

            return Int32.Parse(tb.Text);
        }

        //==================================================
        // Process solve button click
        private void solveButton_Click(object sender, EventArgs e)
        {
            // Validate the board input, if it's good tickle the solver FSM.
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    try
                    {
                        if (!(0 <= Int32.Parse(myInputBoxes[i, j].Text) && Int32.Parse(myInputBoxes[i, j].Text) <= 9))
                        {
                            string s = "Square ( " + i.ToString() + ", " + j.ToString() + " ) has an illegal value.";
                            ErrorMessage em = new ErrorMessage(s);
                            em.ShowDialog();
                            return;
                        }
                    }
                    catch (Exception e1)
                    {
                        string s = "Square ( " + i.ToString() + ", " + j.ToString() + " ) has illegal characters.";
                        ErrorMessage em = new ErrorMessage(s);
                        em.ShowDialog();
                        return;
                    }
                }
            }

           mySolverFSM.EventOccured(SolverFSM.transitionEvent.SOLVE_CLICKED, null);
        }

        //==================================================
        // Process clear button click
        private void clearButton_Click(object sender, EventArgs e)
        {
            mySolverFSM.EventOccured(SolverFSM.transitionEvent.CLEAR_CLICKED, null);
        }

        //==================================================
        // Empty the contents of the results board
        private void ResetResultsBoard()
        {
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    SetControlText(myResultsDisplay[i, j], string.Empty);
                }
            }
        }

        // This code is necessary because C# blocks operations across threads.
        // The FSM is on another thread and it is controlling what we display here.
        Action<Control, string> setterCallback_str = (toSet, text) => toSet.Text = text;
        Action<Control, bool> setterCallback_bool = (toSet, val) => toSet.Enabled = val;

        private void SetControlText(Control toSet, string text)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(setterCallback_str, toSet, text);
            }
            else
            {
                setterCallback_str(toSet, text);
            }
        }

        private void SetControlEnabled(Control toSet, bool theVal)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(setterCallback_bool, toSet, theVal);
            }
            else
            {
                setterCallback_bool(toSet, theVal);
            }
        }

        //==================================================
        // Display the results board
        public void DisplayResultsBoard(byte[] theData)
        {
            int rowIdx = 1;
            int colIdx = 1;

            for (int i = 0; i < SudokuLibApi.RESPONSE_SIZE; ++i)
            {
                if (theData[i] == 0)
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


                SetControlText(myResultsDisplay[rowIdx, colIdx], theData[i].ToString());
            }
        }

        private void enableGuessingButton_Click(object sender, EventArgs e)
        {
            SudokuLibApi.EnableGuessing();
        }

        private void disableGuessing_Click(object sender, EventArgs e)
        {
            SudokuLibApi.DisableGuessing();
        }

        //==================================================
        // Process the events in the manual input box
        private void manualInputBox_TextChanged(object sender, EventArgs e)
        {
            label1.Text = "Manual entry... 0 for empty boxes.";

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
                    myInputBoxes[row, col].Text = userEntry;
                    ++col;
                    if (col > 9)
                    {
                        ++row;
                        col = 1;
                    }
                }
            }
        }

        private void exitButtonClick(object sender, EventArgs e)
        {
            mySolverFSM.EventOccured(SolverFSM.transitionEvent.EXIT_BUTTON_CLICKED, null);
        }

        public void ResetDisplay()
        {
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    SetControlText(myInputBoxes[i, j], string.Empty);
                    SetControlText(myResultsDisplay[i, j], string.Empty);
                }
            }

            SetControlText(manualInputBox, string.Empty);
            SetControlText(label1, "Manual entry... 0 for empty boxes.");
            SetControlText(numGuesses, "0");
            SetControlText(lowestScoreLabel, "0");
            SetControlText(surrenderCountLabel, "0");
            SetControlText(invalidCountLabel, "0");
            SetControlEnabled(clearButton, true);
        }

        public void SetBestScore(byte[] theData)
        {
            SetControlText(lowestScoreLabel, System.Text.Encoding.Default.GetString(theData));
        }

        public void SetNumGuesses(byte[] theData)
        {
            var theStr = System.Text.Encoding.Default.GetString(theData).ToString();
            SetControlText(numGuesses, theStr);
        }

        public void SetInvalidCount(byte[] theData)
        {
            SetControlText(invalidCountLabel, System.Text.Encoding.Default.GetString(theData));
        }

        public void SetSurrenderCount(byte[] theData)
        {
            SetControlText(surrenderCountLabel, System.Text.Encoding.Default.GetString(theData));
        }

        public void DisableClearButton()
        {
            SetControlEnabled(clearButton, false);
        }

        public void EnableClearButton()
        {
            SetControlEnabled(clearButton, true);
        }

        public void DisableExitButton()
        {
            SetControlEnabled(exitButton, false);
        }

        public void EnableExitButton()
        {
            SetControlEnabled(exitButton, true);
        }

        public void Shutdown()
        {
            CloseForm(this);
        }

        Action<Form> setterCallback_Close = (toSet) => toSet.Close();

        private void CloseForm(Form toSet)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(setterCallback_Close, toSet);
            }
            else
            {
                setterCallback_Close(toSet);
            }
        }

        private void Main_FormClosing(object sender, FormClosingEventArgs e)
        {
            mySolverFSM.EventOccured(SolverFSM.transitionEvent.EXIT_BUTTON_CLICKED, null);
        }
    }
}
