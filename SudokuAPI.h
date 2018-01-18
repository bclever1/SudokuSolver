#pragma once

#if 0
#ifdef SUDOKU_SOLVER_EXPORTS  
#define SUDOKU_SOLVER_API __declspec(dllexport)   
#else  
#define SUDOKU_SOLVER_API __declspec(dllimport)   
#endif  

#include <vector>
#include <string>
#include <stdexcept>

using namespace std;


namespace SudokuAPI
{
	// This class is exported from the MathLibrary.dll  
	class Functions
	{
	public:

		// Returns a + b  
		static SUDOKU_SOLVER_API double Add(double a, double b);
		
		// Returns a * b  
		static SUDOKU_SOLVER_API double Multiply(double a, double b);

		// Returns a + (a * b)  
		static SUDOKU_SOLVER_API double AddMultiply(double a, double b);

		static SUDOKU_SOLVER_API void PrintSomething() {};

		static SUDOKU_SOLVER_API void Solve(string theInputs);
	};
}

#endif