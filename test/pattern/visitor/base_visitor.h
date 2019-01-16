#ifndef TEST_VISITOR_BASE_VISITOR_H_
#define TEST_VISITOR_BASE_VISITOR_H_

#include "thor/pattern/visitor.h"

struct A;
struct B;

using BaseVisitor = TP_NS::Visitor<__type_list__(A, B)>;

struct AddVisitor : BaseVisitor {
    void Visit(A& a) override;
    void Visit(B& b) override;
};


struct MulVisitor : BaseVisitor {
    void Visit(A& a) override;
    void Visit(B& b) override;
};

#endif /*TEST_VISITOR_BASE_VISITOR_H_*/