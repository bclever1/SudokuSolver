
# SudokuSolver
My badass sudoku solver

IS NOT WORKING RIGHT NOW... Need to upload the DLL and RECOMPILE

This project is not meant to be the fastest solver in the world. It will get faster as I 
add more solving techniques (which means less guessing), nor is it the prettiest (yet). 
I used this project to learn/explore the following subjects:

1) Linking a C# graphical interface to a C++ code engine (DLL).
2) Modern C++ including:
   a) threads
   b) thread-safe singletons (my design!) and classes
   c) templates
   d) shared_ptrs and unique_ptrs and data structures of such beasts
   e) memory management
   f) functors (function classes)
3) Algorithmic sudoku solving techniques.
4) Advanced debugging in VS2017
5) GitHub

Known issues:
(Hey I did this in five days.)
1) Clearing the fast entry box sometimes leaves the character count at 1 (fixed)
2) It's a little slow (hmm not so with the Release version)
3) shared_ptr memory doesn't seem to clean up the way I understood it should. 
