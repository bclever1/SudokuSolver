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
        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Initialize", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Initialize(byte[] b);

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Reset", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Reset();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "GetCurrentBoard", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetCurrentBoard();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "GetBoardValue", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetBoardValue();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "GetSolved", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetSolved();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "Solve", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Solve();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "EnableGuessing", CallingConvention = CallingConvention.Cdecl)]
        public static extern void EnableGuessing();

        [DllImport(@"C:\Users\Brian\source\repos\SudokuSolver\Debug\SudokuLibraryDll.dll", EntryPoint = "DisableGuessing", CallingConvention = CallingConvention.Cdecl)]
        public static extern void DisableGuessing();
    }
}
