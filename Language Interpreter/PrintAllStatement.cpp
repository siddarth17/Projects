#include "PrintAllStatement.h"
#include "ProgramState.h"

PrintAllStatement::PrintAllStatement() {}

PrintAllStatement::~PrintAllStatement() {}

void PrintAllStatement::execute(ProgramState * state, std::ostream &outf)
{
	// Calls the printAll function from ProgramState
	state->printAll(outf);
	state->incrementcounter();
}
