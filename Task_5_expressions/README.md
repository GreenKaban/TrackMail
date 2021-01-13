# Expression tree

## Description

Here is a set of functions to work with expressions. Correct expression could be a double-precision floating-point number, a variable (one letter from the English alphabet)
or an operation on arguments, which are correct expressions.
Here are the list of supported operations:
| Operation | Meaning     | Usage (1) | Usage (2) | Bad example |
|-----------|-------------|-----------|-----------|-------------|
| +         | plus        | 5 + 3 | 1 + 1 + x | 1 + |
| -         | minus       | 7 - a + 6| 5 - (3 + 1) | 7 - +3 |
| -         | unary minus | -8 | 8 + 3 + (-5) | 8 + -6 |
| *         | multiply    | 7 * 9.234 | -8 * (5 + 7) | 8**9 |
| /         | divide      | 2.3/x | 2 + a/7 - 2 * 3 | / 1 |
| ^         | power       | 2^(5+5) | 2 ^ (-5) + 5 | 4^-3 |
| sin       | sine        | sin(5.0) | 2 * sin(5.0 + 3) | sin 1 |
| cos       | cosine      | -cos(1) | cos(sin(x) + 5) | cos(x |
| ln        | natural logarithm | ln(4)^2 | ln(sin(-5))| ln^2(4) |

In usage you can see correct examples of the input for read_expression.

The expression is stored in the binary tree. Pay attention, that unary minus is not stored as operation with one argument, but as binary minus
with zero first argument, so printed formula (output of print_expr_formula function) sometimes looks not as it could be expected.

There are two functions to print expression tree as a graph: print_expr_tree_stdout and print_expr_tree_graph .

You can also copy expression, simplify it and differentiate it with respect to some variable.

## Getting Started

### Dependencies

* Windows

* MinGW

* LaTeX (add path to the "pdflatex" command to the PATH)

* Graphviz (add path to the "dot" command to the PATH)



### Building


* Run mingw32-make
```
> mingw32-make
```

### Running tests

* Run mingw32-make with argument test
```
> mingw32-make test
```
> **Note:** mingw32-make test execute run_tests.exe redirecting input

Be careful, this will create and open a lot of PDF files if you uncomment some lines in run_tests.c .
Believe me, you don't want this.

You can also use run_tests.exe with your own expressions:
Run program
```
> run_tests.exe
```
Then write your expression in format in which it can be read by read_expression. Then press Enter.






