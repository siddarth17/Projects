#include "ReturnStatement.h"
#include "ProgramState.h"

ReturnStatement::ReturnStatement(){}

ReturnStatement::~ReturnStatement(){}
void ReturnStatement::execute(ProgramState* state, std::ostream& outf)
{
    if (state == nullptr){
        return;
    }

    // Popping stack to find the line to go back to.
    int returnline = state->popStack();
    state->setCounter(returnline);
}
