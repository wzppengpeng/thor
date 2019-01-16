#ifndef TEST_ABSTRCT_H_
#define TEST_ABSTRCT_H_

class Base {
public:
    Base(const int& a, int b) : a_(a), b_(b) {}

    virtual ~Base() {}

    virtual int Run() = 0;

protected:
    int a_;
    int b_;
};

#endif /*TEST_ABSTRCT_H_*/