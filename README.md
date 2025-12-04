
# LAST EDIT: 2025-12-04 15:00

(redownload if downloaded before)

## C-Minus Semantic Analysis Test cases

202520HY12780 class C-minus Project 4 semantic analysis and  automatic tester.

## Features

This automatic testcase runner mainly uses sorted diff + **unique** command.

The program is expected to be executed within the docker container, ran with

```c
docker run --name compiler2025 --rm -it -v "$PWD":/work -w /work cs-compiler-hw:1.0
```

> Note that the ordering **and numbers** of the error messages are ignored.
> 

## Using the Automatic Test Case Runner

1. Clone the files into the working directory.
2. Execute:
    
    ```c
    gcc -o test test.c
    ```
    
    - for full test:
    
    ```c
    ./test
    ```
    
    - or one specific testcase:
    
    ```c
    ./test <num> // ex: ./test 33
    ```
    

## Adding the testcases

1. In the testsuite, add these two files:
    
    ```c
    test_<num>.cm // ex: test_34.cm
    result_<num>.txt // ex: result_34.txt
    ```
    
2. modify the TESTCASE macro in test.c

```c
#include <stdio.h>
#include <stdlib.h>

#define TESTCASES 33 // Modify here.
```

## Compositions of the testcases

### [1, 4]: Testcases provided by our professor

### [5, 14]: Testcases provided by our professor

All of the results should match until here.

---

### [15, 33]: Student-generated Testcases

Results here might be unstable, or include undefined behavior, so the you can ignore the error messages generated here. (my compiler is imperfect too)

### Some notes:

Testcase 24: Redeclaration of function - variable was not mentioned in the requirement

Testcase 25: Whether the indice error should return its original type is unclear.
I did not return invalid condition here.

### About the illegal testcases/Want to add more testcases

You can open the concerns on the issue tab of this repository.

This repository will be maintained until the project submission deadline.

---

### Edit [2025-12-04 : 1]

1. modified 12th testcase result.txt not representing the true result as a hot fix.
    
    before:
    
    ```python
    C-MINUS COMPILATION: testsuite/test_12.cm
    Error: invalid operation at line 6
    Error: invalid operation at line 6
    ```
    
    after:
    
    ```python
    C-MINUS COMPILATION: testsuite/test_12.cm
    Error: invalid operation at line 6
    ```
### Edit [2025-12-04 : 2]

1. Modified the testcase runner to ignore the **number of the same error messages.**
    
    > Now, the testcase 12 will be marked correct before and after.
    > 
2. Critical bug of using later-defined variable was found.
    
    ```c
    /* later assignment */
    
    int main(void)
    {
      a = 1; /* error */
    }
    
    int a;
    ```
    
    Testcases like this (test_30.cm) was not generating undeclared variable error.
    
    before:
    
    ```
    C-MINUS COMPILATION: testsuite/test_30.cm
    Error: invalid assignment at line 5
    ```
    
    after:
    
    ```
    C-MINUS COMPILATION: testsuite/test_30.cm
    **Error: undeclared variable "a" is used at line 5**
    Error: invalid assignment at line 5
    ```
    
    Testcases 23, 25, 27, 30 are affected by this change.