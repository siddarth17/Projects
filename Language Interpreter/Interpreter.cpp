// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "ProgramState.h"
#include "arithmetic.h"
#include "EndStatement.h"
#include "IfStatement.h"
#include "GoToStatement.h"
#include "GoSubStatement.h"
#include "ReturnStatement.h"
#include "PrintAllStatement.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <iostream>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


// Turn in assignment with this main(), not the one provided in hw2_tests
int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine(line) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	int lineNum;
	string type;
	string var;
	string lhs;
	string rhs;
	string op;
	int val;
	int val2;

	ss << line;
	ss >> lineNum;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}

	// Incomplete;  TODO:  Finish this function!
    else if(type == "PRINT")
    {
        ss >> var;
        statement = new PrintStatement(var);
    }
    else if (type == "PRINTALL") {
        statement = new PrintAllStatement();
    } 
    else if (type == "END") {
        statement = new EndStatement();
    } 
    else if (type == "GOTO") {
        ss >> lineNum;
        statement = new GoToStatement(lineNum);
    } 
    else if (type == "IF") {
        // type here is used to extract the 'then' in the line and the other variables extract the operator, line number and variables/values.
        ss >> lhs >> op >> val2 >> type >> lineNum; 
        statement = new IfStatement(lhs, op, val2, lineNum);
    } 
    else if (type == "GOSUB") {
        ss >> lineNum;
        statement = new GoSubStatement(lineNum);
    } 
    else if (type == "RETURN") {
        statement = new ReturnStatement();
    }
    else if (type == "ADD") {
        ss >> lhs;
        //Conditional checks whether we have to add an int to the variable or add two variables.
        if (ss >> val2) {
            statement = new AddStatement(lhs, val2);
        }
        else {
            ss.clear();  
            ss >> rhs;
            statement = new AddStatement(lhs, rhs);
        }
    }
    
    else if (type == "SUB") {
        ss >> lhs;
        //Conditional checks whether we have to subtract an int from the variable or perform substraction with two variables.
        if (ss >> val2) {
            statement = new SubStatement(lhs, val2);
        }
        else {
            ss.clear();  
            ss >> rhs;
            statement = new SubStatement(lhs, rhs);
        }
    }
    else if (type == "MULT") {
        ss >> lhs;
        //Conditional checks whether we have to multiply an int with the variable or multiply two variables.
        if (ss >> val2) {
            statement = new MultStatement(lhs, val2);
        }
        else {
            ss.clear();  
            ss >> rhs;
            statement = new MultStatement(lhs, rhs);
        }
    } 
	else if (type == "DIV") {
        ss >> lhs;
        //Conditional checks whether we have to divide variable with int or perform division with two variables.
        if (ss >> val2) {
            statement = new DivStatement(lhs, val2);
        }
        else {
            ss.clear();
            ss >> rhs;
            statement = new DivStatement(lhs, rhs);
        }
    }

    else if (type=="."){
        // Ends the program as '.' is used at the ending.
        statement = new EndStatement();
    }
    
    return statement;
}

void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement*> program;
	parseProgram( inf, program );
	
	ProgramState* state = new ProgramState(program.size());
	
    if(state == nullptr){
        return;
    }
    
    // Loop executes all the statements in the vector. 
    while(state->getcounter() < state->getNumberOfLines())
    {
        size_t counter = state->getcounter();
        size_t size = program.size();
        if(counter >= 0 && counter < size){
            program[counter]->execute(state, outf);
        }
        else {
            break;
        }
    }
    
    // Clearing the vector contents and deallocating state.
    for(std::size_t i = 0; i < program.size(); i++){
		delete program[i];
	}

    delete state;
}
