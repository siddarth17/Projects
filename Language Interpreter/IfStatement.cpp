#include "IfStatement.h"
#include "ProgramState.h"

IfStatement::IfStatement(std::string variableName, std::string op, int value, int linenum){
    m_variableName = variableName;
    m_operator = op;
    m_value = value;
    m_gotoLine = linenum;
}

IfStatement::~IfStatement(){}

void IfStatement::execute(ProgramState* state, std::ostream& outf)
{
    if (state == nullptr){
        return;
    }
    
    int value = state->getValue(m_variableName);
    
    // Conditons for all operators, comparing the values
    if (m_operator == "=" && value == m_value)
    {
        // Checks if the Go To line is there in the program and does not have a line that does not exist.
        if(m_gotoLine > state->getNumberOfLines()){
            outf << "Illegal jump instruction" << std::endl;
        }
        state->setCounter(m_gotoLine);
    }
    else if (m_operator == "<" && value < m_value) {
        if(m_gotoLine > state->getNumberOfLines()){
            outf << "Illegal jump instruction" << std::endl;
        }
        state->setCounter(m_gotoLine);
    }
    else if (m_operator == "<=" && value <= m_value) {
        if(m_gotoLine > state->getNumberOfLines()){
            outf << "Illegal jump instruction" << std::endl;
        }
        state->setCounter(m_gotoLine);
    }
    else if (m_operator == ">" && value > m_value) {
        if(m_gotoLine > state->getNumberOfLines()){
            outf << "Illegal jump instruction" << std::endl;
        }
        state->setCounter(m_gotoLine);
    }
    else if (m_operator == ">=" && value >= m_value) {
        if(m_gotoLine > state->getNumberOfLines()){
            outf << "Illegal jump instruction" << std::endl;
        }
        state->setCounter(m_gotoLine);
    }
    else if (m_operator == "=" && value == m_value) {
        if(m_gotoLine > state->getNumberOfLines()){
            outf << "Illegal jump instruction" << std::endl;
        }
        state->setCounter(m_gotoLine);
    }
    else if (m_operator == "<>" && value != m_value) {
        if(m_gotoLine > state->getNumberOfLines()){
            outf << "Illegal jump instruction" << std::endl;
        }
        state->setCounter(m_gotoLine);
    }
    //Simply goes to the next line if the condition is not true
    else{
        state->incrementcounter();
    }
}
