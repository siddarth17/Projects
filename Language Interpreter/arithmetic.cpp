#include "arithmetic.h"
#include "ProgramState.h"

AddStatement::AddStatement(std::string variableName, int value){
    m_variableName = variableName;
    m_value = value;
    vartype = false;
}
    
AddStatement::AddStatement(std::string variableName, std::string variableName2){
    m_variableName = variableName;
    m_variableName2 = variableName2;
    vartype = true;
    
}

void AddStatement::execute(ProgramState * state, std::ostream &outf)
{
    if (vartype){
        state->add(m_variableName, state->getValue(m_variableName2));
    }
    else{
        state->add(m_variableName, m_value);
    }

    state->incrementcounter();
}


SubStatement::SubStatement(std::string variableName, int value){
    m_variableName = variableName;
    m_value = value;
    vartype = false;
}

SubStatement::SubStatement(std::string variableName, std::string variableName2){
    m_variableName = variableName;
    m_variableName2 = variableName2;
    vartype = true;
}

void SubStatement::execute(ProgramState * state, std::ostream &outf)
{
    if (vartype){
        state->subtract(m_variableName, state->getValue(m_variableName2));
    }
    else{
        state->subtract(m_variableName, m_value);
    }

    state->incrementcounter();
}


MultStatement::MultStatement(std::string variableName, int value){
    m_variableName = variableName;
    m_value = value;
    vartype = false;
}

MultStatement::MultStatement(std::string variableName, std::string variableName2){
    m_variableName = variableName;
    m_variableName2 = variableName2;
    vartype = true;
}

void MultStatement::execute(ProgramState * state, std::ostream &outf)
{
    if (vartype){
        state->multiply(m_variableName, state->getValue(m_variableName2));
    }
    else{
        state->multiply(m_variableName, m_value);
    }

    state->incrementcounter();
}


DivStatement::DivStatement(std::string variableName, int value){
    m_variableName = variableName;
    m_value = value;
    vartype = false;
}

DivStatement::DivStatement(std::string variableName, std::string variableName2){
    m_variableName = variableName;
    m_variableName2 = variableName2;
    vartype = true;
}

void DivStatement::execute(ProgramState * state, std::ostream &outf)
{
    int end = state->getNumberOfLines() + 1;
    if (vartype){
        // Condition checks if denominator is zero.
        if(state->getValue(m_variableName2) == 0){
            outf << "Divide by 0 exception" << std::endl;
            state->setCounter(end);
        }
        else{
            state->divide(m_variableName, state->getValue(m_variableName2));
        }
    }
    else{
        // Condition checks if denominator is zero.
        if(m_value == 0){
            outf << "Divide by 0 exception" << std::endl;
            state->setCounter(end);
        }
        else{
            state->divide(m_variableName, m_value);
        }
    }

    state->incrementcounter();
}
