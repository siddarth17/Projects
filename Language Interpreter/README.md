README.md

This program works as an Interpreter for BASIC, a well-known programming languagedecades ago.
The interpreter handles multiple statements from the BASIC program. 

Below are the statement files I used and their functions:

Statement.h: This is a generic class as it serves as the base class for all the other statement types. 

ProgramState.h: Handles many basic functions and the current state of the program such as storing variables and counters/lines.

Interpreter.cpp: Evaluates the lines of the programs and creates appropriate statements to execute. 

LetStatement.h: Performs the let function by creating and editing variables.

PrintStatement.h: Prints values of variables. 

ReturnStatement.h: Used for Return function to jump back to the most recent GOSUB statement. 

PrintAllStatement.h: Prints all the variables and their values. 

IfStatement.h: Used for the if statement to compare variables to integer values and jumps to the appropriate lines. 

GoToStatement.h: Used for the GoTo statement to jump to the specified line. 

GoSubStatement.h: Used to temporarily jump to a line for the GOSUB statement as it jumps back to the initial place after a return. 

EndStatement.h: Used for the Endstatement to terminate or end the program.

arithmetic.h: Used for all the arithmetic statements like Addition, Substraction, Multiplication and Division.

Here's an example program: 
LET X 10            // Set variable X to 10
LET Y 20            // Set variable Y to 20
ADD X Y             // Add Y to X (X becomes 30)
IF X = 30 THEN 8    // If X equals 30, jump to line 8
SUB Y X             // Subtract X from Y (not executed if jump happens)
MULT X 2            // Multiply X by 2 (X becomes 60 if jump happens)
GOTO 10             // Jump to line 10
PRINT X             // Print X (prints 60)
PRINT Y             // Print Y (prints 20 as no change after initialization)
GOSUB 13            // Jump to subroutine at line 13
LET Z 5             // Sets variable Z to 5 (part of subroutine)
ADD Z X             // Add X to Z (Z becomes 65)
RETURN              // Return from subroutine
PRINTALL            // Prints all variables: X, Y, Z
END                 // End of the program
.                   // Acts as an END statement


