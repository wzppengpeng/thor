#ifndef TEST_FACTORY_A_H_
#define TEST_FACTORY_A_H_

#include "abstract.h"


class A : public Base {

public:
    A(const int& a, int b);

    virtual int Run();
};

#endif /*TEST_FACTORY_A_H_*/