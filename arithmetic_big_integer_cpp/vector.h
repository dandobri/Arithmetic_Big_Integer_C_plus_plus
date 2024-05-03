#ifndef BACKLOG_ITMO_CPP_LN_DANDOBRI_MAIN_VECTOR_H
#define BACKLOG_ITMO_CPP_LN_DANDOBRI_MAIN_VECTOR_H
#include "LN.h"
class Vector
{
public:
    void push(const LN& c);
    long long size_() const;
    LN pop();
    Vector();
private:
    LN* mas;
    long long size_mas;
    long long size;
};
#endif
