**README for P2**
Author: Thaddeus King
CS4280

Usage:
Makefile instructions:
-make all -> compiles P1 as well as all tests for development. Tests run silently at end of compilation
-make frontEnd -> compiles P1
-make test -> compiles all tests
-make clean -> removes all object files, output files as well as all executables

Invocation:
./frontEnd [filename]

Output:
All output is outputed via the console. Output is 1 token per line and displays the token type, token value, and linenumber correctly. The first linenumber of the input is 0.

P2 Notes:

Any errors from the parser are returned as Error tokens These errors prevent a tree from being built and instead will return an error token as the root of the 'tree' that is printed. If there is more than 1 error, only the first error will be shown.

Parse trees that are printed contain non-terminals and their name is in the format is shown belown. Non-terminals do not contain tokens themselves and thus will not show token output. Terminals contain tokens and show the token (value and linenumber.)

Node names:
-terminal nodes: TerminalNode
-non terminal nodes: <Name>

Development notes:
Developed using test driven development. All of the tests used for development have been left inside the project for reference. These tests are all quiet (ie they produce no output.)

P2 successfully compiled and ran on tc.rnet.missouri.edu on 6.06.2020.

Bugs/Issues:
No known bugs or issues.