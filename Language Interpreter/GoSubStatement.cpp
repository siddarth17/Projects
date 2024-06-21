#include "GoSubStatement.h"
#include "ProgramState.h"

GoSubStatement::GoSubStatement(int gotoLine){
    m_gotoLine = gotoLine;
}

GoSubStatement::~GoSubStatement(){
}

void GoSubStatement::execute(ProgramState* state, std::ostream& outf){
    
    if (state == nullptr){
        return; 
    }
    // Adding the line to the stack when return statement is used.
    state->pushstackvalue(state->getcounter() + 1);
     // Conditional checks whether the go to line exists in the program or not. 
    if (m_gotoLine > 0 && m_gotoLine <= state->getNumberOfLines()) {
        state->setCounter(m_gotoLine);
    } 
    else {
        outf << "Illegal jump instruction" << std::endl;
        state->incrementcounter();
    }
}
