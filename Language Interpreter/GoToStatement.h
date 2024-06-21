#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"

class GoToStatement : public Statement
{
private:
    int m_gotoLine;

public:
    GoToStatement(int gotoLine);
    ~GoToStatement();

    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
