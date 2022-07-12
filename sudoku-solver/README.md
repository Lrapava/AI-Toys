# Sudoku solver

A simple sudoku solver written in C++. The program assumes that the input is a valid sudoku puzzle with an existing solution. example1.txt, example2.txt, example3.txt and example4.txt contain example puzzles.


P.S. Ignore debug.cpp

# Examples

```
$ g++ main.cpp -o main && ./main
Enter your sudoku:
75.2.....
.1..96..4
4...5...3
....3...5
..7.4..3.
5.1..29..
9.....387
....6....
..4..851.

Solution:
753284169
218396754
496157823
649831275
827549631
531672948
962415387
185763492
374928516
```

```
$ g++ main.cpp -o main && cat example4.txt | ./main
Enter your sudoku:
Solution:
813257649
594613827
627984531
369745218
175832496
248196753
451378962
982561374
736429185
```
