#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "Statement.h"

class GoSubStatement : public Statement
{
private:
    int m_gotoLine;

public:
    GoSubStatement(int gotoLine);
    ~GoSubStatement();

    virtual void execute(ProgramState* state, std::ostream& outf);
};

#endif
