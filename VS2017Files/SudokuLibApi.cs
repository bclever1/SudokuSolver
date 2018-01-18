using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SudokuInterface
{
    public static class SudokuLibApi
    {
        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Add", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Add(double a, double b);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Solve", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Solve(
            int s_1_1, int s_1_2, int s_1_3, int s_1_4, int s_1_5, int s_1_6, int s_1_7, int s_1_8, int s_1_9,
            int s_2_1, int s_2_2, int s_2_3, int s_2_4, int s_2_5, int s_2_6, int s_2_7, int s_2_8, int s_2_9,
            int s_3_1, int s_3_2, int s_3_3, int s_3_4, int s_3_5, int s_3_6, int s_3_7, int s_3_8, int s_3_9,
            int s_4_1, int s_4_2, int s_4_3, int s_4_4, int s_4_5, int s_4_6, int s_4_7, int s_4_8, int s_4_9,
            int s_5_1, int s_5_2, int s_5_3, int s_5_4, int s_5_5, int s_5_6, int s_5_7, int s_5_8, int s_5_9,
            int s_6_1, int s_6_2, int s_6_3, int s_6_4, int s_6_5, int s_6_6, int s_6_7, int s_6_8, int s_6_9,
            int s_7_1, int s_7_2, int s_7_3, int s_7_4, int s_7_5, int s_7_6, int s_7_7, int s_7_8, int s_7_9,
            int s_8_1, int s_8_2, int s_8_3, int s_8_4, int s_8_5, int s_8_6, int s_8_7, int s_8_8, int s_8_9,
            int s_9_1, int s_9_2, int s_9_3, int s_9_4, int s_9_5, int s_9_6, int s_9_7, int s_9_8, int s_9_9);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "SolveB", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SolveB(byte[] b, ref byte[] c);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Initialize", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Initialize(byte[] b);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Reset", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Reset();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "ReduceRow", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReduceRow(int row);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "ReduceColumn", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReduceColumn(int col);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "ReduceBlock", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReduceBlock(int theBlock);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveStrandedSinglesFromRow", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveStrandedSinglesFromRow(int theRow);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveStrandedSinglesFromColumn", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveStrandedSinglesFromColumn(int theCol);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveStrandedSinglesFromBlock", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveStrandedSinglesFromBlock(int theBlock);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveNakedPairsFromRow", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveNakedPairsFromRow(int theRow);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveNakedPairsFromColumn", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveNakedPairsFromColumn(int theCol);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveNakedPairsFromBlock", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveNakedPairsFromBlock(int theBlock);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "GetCurrentBoard", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetCurrentBoard();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "GetBoardValue", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetBoardValue();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "GetSolved", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetSolved();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Reduce", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Reduce();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveStrandedSingles", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveStrandedSingles();
 
        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "RemoveNakedPairs", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RemoveNakedPairs();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Solve", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Solve();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Solved", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Solved();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "EnableGuessing", CallingConvention = CallingConvention.Cdecl)]
        public static extern void EnableGuessing();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "DisableGuessing", CallingConvention = CallingConvention.Cdecl)]
        public static extern void DisableGuessing();
    }
}
