#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"

class IfStatement: public Statement
{
public:
    IfStatement(std::string var1, std::string op, int value, int linenum);
    ~IfStatement();
    
    virtual void execute(ProgramState * state, std::ostream &outf);

private:
    std::string m_variableName;
    std::string m_operator;
    int m_value;
    int m_gotoLine;
};

#endif