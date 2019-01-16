#include "base_visitor.h"

#include "base.h"

#include "../../help_function.h"

void AddVisitor::Visit(A& a) {
    ASSERT_EQ(2, a.val + 1);
}


void AddVisitor::Visit(B& b) {
    ASSERT_EQ(2.0, b.val + 1.0);
}