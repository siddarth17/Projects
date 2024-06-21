README.md

This program works as an Interpreter for BASIC. BASIC is a well-known programming language that was used a lot decades ago.
The interpreter handles multiple statements from the BASIC program. The table below shows different statements and symbols
that this program can handle. 

LET *var* *int*  | Change the value of variable *var* to the integer *int*
--------------------------------------------------------------------------------------------------------
PRINT *var*      | Print the value of variable *var* to output
--------------------------------------------------------------------------------------------------------
PRINTALL         | Prints the value of all used variables to output, one per line.
--------------------------------------------------------------------------------------------------------
ADD *var* *p*    | Adds *p* to the value of the variable *var*, where *p* is an int or variable.
--------------------------------------------------------------------------------------------------------
SUB *var* *p*    | Subtracts *p* from  the value of the variable *var*, where *p* is an int or variable.
--------------------------------------------------------------------------------------------------------
MULT *var* *p*   | Multiplies the value of the variable *var* by the integer or variable *p*
--------------------------------------------------------------------------------------------------------
DIV *var* *p*    | Divides the value of the variable *var* by the integer or variable *p*
--------------------------------------------------------------------------------------------------------
GOTO *linenum*   | Jumps execution of the program to the line numbered *linenum*
--------------------------------------------------------------------------------------------------------
IF *var* *op*    | Compares the value of the variable *var* to the integer *int*
*int* THEN       | via the operator *op* (<, <=, >, >=, =, <>), and jumps
*linenum*        | execution of the program to line *linenum* if true.
--------------------------------------------------------------------------------------------------------
GOSUB *linenum*  | Temporarily jumps to line *linenum*, and jumps back after a RETURN
--------------------------------------------------------------------------------------------------------
RETURN           | Jumps execution of the program back to the most recently executed GOSUB.
--------------------------------------------------------------------------------------------------------
END              | Immediately terminates the program.
--------------------------------------------------------------------------------------------------------
.                | Placed at the end of the program, and behaves like an END statement.

The interpretProgram function will read in a valid program from an input stream, interpret that program, and output everything 
to an output stream in Interpreter.cpp. 

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

