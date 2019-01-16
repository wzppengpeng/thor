#include "base.h"

#include "../../help_function.h"

int main()
{
    TEST_BEGIN(Visitor);

    AddVisitor add_visitor;
    MulVisitor mul_visitor;

    A a; B b;

    a.val = 1; b.val = 1.0;

    Base* ptr = &a;

    ptr->Accept(add_visitor);
    ptr->Accept(mul_visitor);

    ptr = &b;

    ptr->Accept(add_visitor);
    ptr->Accept(mul_visitor);

    TEST_SUCCESS(Visitor);
    return 0;
}