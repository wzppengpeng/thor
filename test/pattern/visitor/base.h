#ifndef TEST_VISITOR_BASE_H_
#define TEST_VISITOR_BASE_H_

#include "base_visitor.h"

struct Base {
    virtual void Accept(BaseVisitor&) = 0;
};

struct A : Base {
    int val;
    DEFINE_VISITOR_ACCEPT_FUNCTION(BaseVisitor);
};

struct B : Base {
    double val;
    DEFINE_VISITOR_ACCEPT_FUNCTION(BaseVisitor);
};

#endif /*TEST_VISITOR_BASE_H_*/