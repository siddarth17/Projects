#include "EndStatement.h"
#include "ProgramState.h"

using namespace std;

EndStatement::EndStatement() {}

EndStatement::~EndStatement() {}

void EndStatement::execute(ProgramState * state, ostream &outf)
{
    if (state != nullptr){
        // Setting the counter at a line that is not present in the program so that the iteration stops and program ends.
        state->setCounter(state->getNumberOfLines() + 1);
    }
    else{
        return;
    }

    state->incrementcounter();
}


