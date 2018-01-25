using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SudokuInterface
{
    public class SolverFSM
    {
        private enum solverState { IDLE, DISPLAYING_EXTRA_DATA, SOLVING, POLLING, BEGIN_DISPLAYING, COMPL_DISPLAYING, CLEARING, ALL_STATES };
        public enum transitionEvent { SOLVE_CLICKED, CLEAR_CLICKED, WAIT_FOR_RESPONSE, BOARD_NOT_SOLVED, BOARD_SOLVED, DATA_RCVD, ALL_TXNS };

        public delegate void myDelegate(Request theReq);
        static myDelegate[,] myFSM;

        solverState myState;

        Main myMainWindow;

        int myResponseCounter;

        public SolverFSM(Main theMainWindow)
        {
            myMainWindow = theMainWindow;

            myFSM = new myDelegate[(int)solverState.ALL_STATES, (int)transitionEvent.ALL_TXNS];
            myFSM[(int)solverState.IDLE, (int)transitionEvent.SOLVE_CLICKED] =new myDelegate(STATE_SOLVING);
            myFSM[(int)solverState.IDLE, (int)transitionEvent.CLEAR_CLICKED] = new myDelegate(STATE_CLEARING);
            myFSM[(int)solverState.SOLVING, (int)transitionEvent.WAIT_FOR_RESPONSE] = new myDelegate(STATE_POLLING);
            myFSM[(int)solverState.POLLING, (int)transitionEvent.BOARD_NOT_SOLVED] = new myDelegate(STATE_POLLING);
            myFSM[(int)solverState.POLLING, (int)transitionEvent.DATA_RCVD] = new myDelegate(DISPLAYING_EXTRA_DATA);
            myFSM[(int)solverState.POLLING, (int)transitionEvent.BOARD_SOLVED] = new myDelegate(STATE_BEGIN_DISPLAYING);
            myFSM[(int)solverState.BEGIN_DISPLAYING, (int)transitionEvent.DATA_RCVD] = new myDelegate(STATE_COMPL_DISPLAY);
            myFSM[(int)solverState.COMPL_DISPLAYING, (int)transitionEvent.DATA_RCVD] = new myDelegate(DISPLAYING_EXTRA_DATA);
            myFSM[(int)solverState.COMPL_DISPLAYING, (int)transitionEvent.CLEAR_CLICKED] = new myDelegate(STATE_CLEARING);
            myFSM[(int)solverState.CLEARING, (int)transitionEvent.SOLVE_CLICKED] = new myDelegate(STATE_SOLVING);
            myFSM[(int)solverState.CLEARING, (int)transitionEvent.CLEAR_CLICKED] = new myDelegate(STATE_CLEARING);
            myFSM[(int)solverState.POLLING, (int)transitionEvent.CLEAR_CLICKED] = new myDelegate(STATE_CLEARING);
            myFSM[(int)solverState.CLEARING, (int)transitionEvent.DATA_RCVD] = new myDelegate(IgnoreEvent);
            myFSM[(int)solverState.CLEARING, (int)transitionEvent.BOARD_NOT_SOLVED] = new myDelegate(IgnoreEvent);
            myFSM[(int)solverState.CLEARING, (int)transitionEvent.BOARD_SOLVED] = new myDelegate(IgnoreEvent);

            myState = solverState.IDLE;
            myResponseCounter = 0;
        }

        public void Run()
        {
            myState = solverState.IDLE;
        }

        private void IgnoreEvent(Request theRequest)
        {

        }

        private void STATE_IDLE(Request theRequest)
        {
            myState = solverState.IDLE;
        }

        private void STATE_SOLVING(Request theRequest)
        {
            myState = solverState.SOLVING;

            SudokuLibApi.EnableGuessing();

            myMainWindow.DisableClearButton();

            // Convert the user input to a byte array to send to the Sudoku API
            byte[] myBytes = new byte[81];

            int byteIdx = 0;
            for (int i = 1; i <= 9; ++i)
            {
                for (int j = 1; j <= 9; ++j)
                {
                    myBytes[byteIdx] = Convert.ToByte(Int32.Parse(myMainWindow.myInputBoxes[i, j].Text));
                    ++byteIdx;
                }
            }

            // Call the Sudoko API to initialize the board
            SudokuLibApi.Reset();
            SudokuLibApi.Initialize(myBytes);
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.Solve));

            EventOccured(SolverFSM.transitionEvent.WAIT_FOR_RESPONSE, null);
        }

        private void STATE_POLLING(Request theRequest)
        {
            myState = solverState.POLLING;
            Thread.Sleep(100);

            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetNumSurrenders));
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetNumInvalids));
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetBestScore));
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetNumGuesses));
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.IsSolved));
            ++myResponseCounter;
        }

        private void DISPLAYING_EXTRA_DATA(Request theRequest)
        {
            //myState = solverState.DISPLAYING_EXTRA_DATA;

            if (theRequest != null)
            {
                if (theRequest.myRequestType == RequestType.GetBestScore)
                {
                    myMainWindow.SetBestScore(theRequest.GetByteData());
                }
                else if (theRequest.myRequestType == RequestType.GetNumGuesses)
                {
                    myMainWindow.SetNumGuesses(theRequest.GetByteData());
                }
                else if (theRequest.myRequestType == RequestType.GetNumInvalids)
                {
                    myMainWindow.SetInvalidCount(theRequest.GetByteData());
                }
                else if (theRequest.myRequestType == RequestType.GetNumSurrenders)
                {
                    myMainWindow.SetSurrenderCount(theRequest.GetByteData());
                }
            }
        }

        private void STATE_CLEARING(Request theRequest)
        {
            myState = solverState.CLEARING;

            Request req = new Request(this, RequestType.Reset);
            APIMonitor.Instance.NewRequest(req);

            myMainWindow.ResetDisplay();
        }

        private void STATE_BEGIN_DISPLAYING(Request theRequest)
        {
            myState = solverState.BEGIN_DISPLAYING;
            Request req = new Request(this, RequestType.GetSolved);
            APIMonitor.Instance.NewRequest(req);
        }

        private void STATE_COMPL_DISPLAY(Request theRequest)
        {
            myMainWindow.DisplayResultsBoard(theRequest.GetByteData());

            myState = solverState.COMPL_DISPLAYING;
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetNumSurrenders));
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetNumInvalids));
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetBestScore));
            APIMonitor.Instance.NewRequest(new Request(this, RequestType.GetNumGuesses));

            myMainWindow.EnableClearButton();
        }

        public void EventOccured(transitionEvent theEvent, Request theRequest)
        {
            try
            {
                myFSM[(int)myState, (int)theEvent](theRequest);
            }
            catch (Exception e)
            {
                string theMessage = "Transition not defined: \n";
                theMessage += myState.ToString() + "..." + theEvent.ToString();
                theMessage += "\n or";
                theMessage += e.Message;

                ErrorMessage em = new ErrorMessage(theMessage);
                em.ShowDialog();
            }
        }

        public void RequestResponse(Request theRequest)
        {
            if (theRequest.myRequestType == RequestType.IsSolved)
            {
                if (theRequest.GetBoolData() == false)
                {
                    EventOccured(transitionEvent.BOARD_NOT_SOLVED, null);
                }
                else
                {
                    EventOccured(transitionEvent.BOARD_SOLVED, null);
                }
            }

            else if (theRequest.myRequestType == RequestType.GetSolved ||
                     theRequest.myRequestType == RequestType.GetNumGuesses ||
                     theRequest.myRequestType == RequestType.GetBestScore ||
                     theRequest.myRequestType == RequestType.GetNumInvalids ||
                     theRequest.myRequestType == RequestType.GetNumSurrenders)
            {
                EventOccured(transitionEvent.DATA_RCVD, theRequest);
            }
        }
    }
}
