#include "GoToStatement.h"
#include "ProgramState.h"

GoToStatement::GoToStatement(int gotoLine){
    m_gotoLine = gotoLine;
}

GoToStatement::~GoToStatement(){
    
}


void GoToStatement::execute(ProgramState* state, std::ostream& outf){

    if (state == nullptr){
        return;
    } 
    // Conditional checks whether the go to line exists in the program or not. 
    if (m_gotoLine > 0 && m_gotoLine <= state->getNumberOfLines()) {
        state->setCounter(m_gotoLine);
    } 
    else {
        outf << "Illegal jump instruction" << std::endl;
        state->incrementcounter();
    }
}
