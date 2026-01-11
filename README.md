# Big-integer-arithmetic Library

## Project Overview

This is a big-integer arithmetic library implemented in C language, supporting four basic operations (addition, subtraction, multiplication, division) for integers of arbitrary length. The project uses a 10,000-ary system (storing every four decimal digits as one unit) for efficient storage and computation of large numbers and implements various optimization algorithms to improve performance.

## Technical Evolution

### First Generation: Basic Implementation (September 2025)
On September 20, 2025, officially started the big-integer arithmetic project on the teacher's suggestion.
-   Used decimal linked lists for storage, completed basic four operations
-   Multiplication of ten-thousand-digit numbers took several hours, with obvious performance bottlenecks

### Second Generation: 10,000-ary Optimization (September - October 2025)
Created a "new version" folder, switched from decimal to 10,000-ary, efficiency improved by 4 times.
-   Implemented Karatsuba convolution multiplication, efficiency improved by tens of times
-   Optimized 60,000-digit number multiplication to about 0.7 seconds
-   Attempted Burnikel-Ziegler algorithm (normalization issues to be resolved)
-   Initially implemented Newton iterative division (unstable at the time)

### Third Generation: Advanced Algorithm Exploration (October - November 2025)
Created a "final version" folder, established a complete error reporting mechanism, optimized through continuous debugging.
-   Implemented stable Newton iterative division
-   Began researching more advanced multiplication algorithms

In the document "final version PLUS version":
-   Implemented DFT multiplication, discovered single-modulus limitation (only supports up to 40 bits)
-   Studied the Chinese Remainder Theorem, implemented a prototype of multi-modulus DFT
-   Further optimized to an NTT multiplication prototype

### Fourth Generation: Engineering Organization and Open Source (January 2026)
The PLUS version only implemented a multi-modulus DFT prototype. Recognizing the huge optimization space and that progress is endless, temporarily shifted to learning other fields.
On January 1, 2026, after mastering more advanced compilation skills, reorganized the project in VSCode and made it open source.

(File structures from the evolution process can be seen in the README appendix)

## Features

### 1. Basic Operations
-   **Addition**: Supports addition of integers of arbitrary length
-   **Subtraction**: Supports subtraction of integers of arbitrary length, automatically handles signs
-   **Multiplication**: Implements three multiplication algorithms:
    -   Ordinary multiplication (basic algorithm)
    -   Karatsuba algorithm (recursive divide-and-conquer optimization)
    -   NTT (Number Theoretic Transform) algorithm (high-performance multiplication, ongoing optimization)
-   **Division**: Implements two division algorithms:
    -   Ordinary long division
    -   Newton's iterative method (fast reciprocal calculation)

### 2. Technical Characteristics
-   **Efficient Storage Structure**: 10,000-ary block linked list storage, 4 decimal digits per block
-   **Intelligent Memory Management**: Dynamic memory allocation and release, compatible with fragmented memory environments
-   **Complete Error Handling**: Robust error reporting mechanism and boundary checking
-   **Cross-platform Support**: Pure C implementation, console supports UTF-8 encoding
-   **File I/O Support**: Supports reading large numbers from files and outputting results

## Project Structure

```
Big_integer_arithmetic/
├── CMakeLists.txt              # CMake build configuration
├── build/                      # Compilation output directory
├── include/                    # Header file directory
│   └── main.h                  # Main header file (function declarations and data structure definitions)
├── src/                        # Source code directory
│   ├── main.c                  # Main program file (operation logic and user interface)
│   ├── list.c                  # Linked list operation implementation
│   ├── num.c                   # Large number basic operation implementation
│   └── ntt.c                   # NTT (Number Theoretic Transform) algorithm auxiliary
├── test/                       # Test data directory
│   └── Num_1shiwan.txt
│   └── ...
└── output/                     # Program output directory
    └── answer.txt              # Operation result output file
    └── ...
```

## Usage

### 1. Input Large Numbers
The program supports two input methods:

**Method 1: File Input (Default)**
```c
FILE *fp = fopen("test\\Num_1shiwan.txt","r");
Num num_1 = fgetNum(fp);
```

**Method 2: Console Input**
```c
printf("Please enter two large numbers:\n");
Num num_1 = getNum();
Num num_2 = getNum();
```

### 2. Select Operation
After the program runs, it will prompt to select the operation type:
```
Please enter the operation you want to perform: (+-*/)
```
Enter the corresponding operator to perform the operation.

### 3. View Results
Operation results will:
-   Be displayed on the console
-   Be saved to the `output/answer.txt` file

## Performance Characteristics

### Integer Representation Range
-   **int**: Maximum 10 digits (2147483647)
-   **long long**: Maximum 19 digits (9223372036854775807)
-   **This Library**: Theoretically unlimited, constrained by memory size

---

Welcome everyone to submit issues and improvement suggestions.

This project is for learning and exchange purposes only.

---
**Author**: Zhejiang University Student - Lüyibuxi

**Version**: 1.0

**Core Code Completion Date**: November 4, 2025

**Open Source Release Date**: January 1, 2026

**Document Update Date**: January 2, 2026

## Appendix: Project Evolution Screenshots

### First Generation: Basic Implementation (September 2025)
![Initial Project Structure](./docs/20260102132642.png)
*Folder structure in the initial stage of the project, starting from the simplest decimal linked list*

### Second Generation: 10,000-ary Optimization (September - October 2025)
![New Version Folder Structure](./docs/20260102132740.png)
*"New version" folder structure, introducing 10,000-ary and Karatsuba algorithm*

### Third Generation: Advanced Algorithm Exploration (October - November 2025)
![Final Version Folder](./docs/20260102134057.png)
*"Final version" folder, containing a complete error handling module*

### Fourth Generation: Engineering Exploration (November 2025)
![Final Version PLUS Folder](./docs/20260102134445.png)
*"Final version PLUS version" folder, exploring DFT/NTT algorithms*

*Note: The above are screenshots of historical versions during development. Please refer to the main directory of the GitHub repository for the current project structure.*
