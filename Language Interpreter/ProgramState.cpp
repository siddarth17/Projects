#include "ProgramState.h"
#include <ostream> 


ProgramState::ProgramState(int numLines)
{
    m_programcounter = 1;
    m_numLines = numLines;
}

// Used to make variable and add it to the map.
void ProgramState::setValue(const std::string &name, int value)
{
    m_variable[name] = value;
}


// Used to find and get value of the key (variable name).
int ProgramState::getValue(const std::string &name) const
{
    if(m_variable.find(name) != m_variable.end()){
        return m_variable.at(name);
    }
    return 0; 
}

// Checks whether a variable exists in the map.

bool ProgramState::variableExists(const std::string &name) const
{
    return m_variable.find(name) != m_variable.end();
}


// These 4 functions perform arithmetic operations on variables
void ProgramState::add(const std::string &name, int value)
{
    m_variable[name] = m_variable[name] + value;
}

void ProgramState::subtract(const std::string &name, int value)
{
    m_variable[name] = m_variable[name] - value;
}

void ProgramState::multiply(const std::string &name, int value)
{
    m_variable[name] = m_variable[name] * value;
}

void ProgramState::divide(const std::string &name, int value)
{
    if(value != 0){
        m_variable[name] = m_variable[name] / value;
    }
}

// Making the program go to the next line.
void ProgramState::incrementcounter()
{
    m_programcounter++;
}

// Returns the counter or the line the program is on.
int ProgramState::getcounter() const
{
    return m_programcounter;
}

// Used to add lines to the stack, mainly for the gosub statement.
void ProgramState::pushstackvalue(int val)
{
    m_stack.push(val);
}

// Used to extract the lines from the stack, mainly for the return statement.
int ProgramState::popStack()
{
    if(m_stack.empty()){
        return -1;
    } 
    int value = m_stack.top();
    m_stack.pop();
    return value;
}

// Changes the line value of the counter so that lines can be skipped or to visit a previous line. Mainly used for GoTo and GoSub statements.
void ProgramState::setCounter(int counter)
{
    m_programcounter = counter;
}

// Returns the total number of lines in the program.
int ProgramState::getNumberOfLines() const
{
    return m_numLines;
}

// Iterates through the map to print all the variables and their values that were in the program.
void ProgramState::printAll(std::ostream &outf) const
{
    for (std::map<std::string, int>::const_iterator var = m_variable.begin(); var != m_variable.end(); ++var){
        outf << var->first << " " << var->second << std::endl;
    }
}


