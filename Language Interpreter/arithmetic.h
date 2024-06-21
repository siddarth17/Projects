#ifndef ARITHMETIC_INCLUDED
#define ARITHMETIC_INCLUDED

#include "Statement.h"
#include <string>

class AddStatement : public Statement
{
public:
    AddStatement(std::string variableName, int value);
    AddStatement(std::string variableName, std::string variableName2);
    virtual void execute(ProgramState * state, std::ostream &outf);
    
private:
    std::string m_variableName;
    std::string m_variableName2;
    int m_value;
    bool vartype;
};

class SubStatement : public Statement
{
public:
    SubStatement(std::string variableName, int value);
    SubStatement(std::string variableName, std::string variableName2);
    virtual void execute(ProgramState * state, std::ostream &outf);
    
private:
    std::string m_variableName;
    std::string m_variableName2;
    int m_value;
    bool vartype;
};

class MultStatement : public Statement
{
public:
    MultStatement(std::string variableName, int value);
    MultStatement(std::string variableName, std::string variableName2);
    virtual void execute(ProgramState * state, std::ostream &outf);
    
private:
    std::string m_variableName;
    std::string m_variableName2;
    int m_value;
    bool vartype;
};

class DivStatement : public Statement
{
public:
    DivStatement(std::string variableName, int value);
    DivStatement(std::string variableName, std::string variableName2);
    virtual void execute(ProgramState * state, std::ostream &outf);
    
private:
    std::string m_variableName;
    std::string m_variableName2;
    int m_value;
    // This bool variable is used to check whether the first argument variable should be added to an int or another variable.
    bool vartype;
};

#endif

