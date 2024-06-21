// PrintStatement.cpp:
#include "PrintStatement.h"
using namespace std;

PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName )
{}

PrintStatement::~PrintStatement(){}

void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
    if (state != nullptr)
    {
        // Adds variable to map with value 0 if the variable to be printed does not exist.
        if (!state->variableExists(m_variableName)) {
            state->setValue(m_variableName, 0);
        }

        int value = state->getValue(m_variableName);
        outf << value << endl;
        state->incrementcounter();
    }
}


