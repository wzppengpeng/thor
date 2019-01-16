#ifndef TEST_FACTORY_B_H_
#define TEST_FACTORY_B_H_

#include "abstract.h"


class B : public Base {

public:
    B(const int& a, int b);

    virtual int Run();
};

#endif /*TEST_FACTORY_B_H_*/