# Lost Temple Operators
Initial Project for Analysis and Synthesis of Algorithms

## Introduction
This project involves creating an algorithm to determine the correct parenthesization of a sequence of binary operations (⊕) to achieve a desired result, given a custom operation table and input sequence. The output should indicate if this is possible and provide the leftmost parenthesization.

## Input & Output
The input file should be a `.txt` file that contain the following:

- The first line contains an integer `n`, the number of elements in the custom operation table.
- The next `n` lines contain `n` integers, each representing the result of a binary operation `⊕` between elements.
- The next line contains a sequence of binary operations that needs to be parenthesized.
- The last line contains the expected result
  
The output will be printed to stdout and will contain the follow:

- If a valid parenthesization exists, the output will be `1` and the leftmost parenthesization«. 
- If no valid parenthesization exists, the output will be `0`.

### Example:
```bash
3 6
3 2 1
3 2 1
1 3 3
2 2 2 2 1 3
1
```
The output should be:
```bash
1
((((2 2) 2) (2 1)) 3)
```
## Compilation and Execution

To compile and run the program, use the following commands:
```bash
g++ -std=c++11 -O3 -Wall file.cpp -lm
./a.out < filename.txt
```

