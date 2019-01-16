#include "base.h"

#include "../../help_function.h"

void MulVisitor::Visit(A& a) {
    ASSERT_EQ(1, a.val * 1);
}


void MulVisitor::Visit(B& b) {
    ASSERT_EQ(1.0, b.val * 1.0);
}