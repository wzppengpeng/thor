#ifndef THOR_IDIOMS_UNCOPY_H_
#define THOR_IDIOMS_UNCOPY_H_

#include "common.h"

TI_NS_BEGIN

class Uncopyable {

protected:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator= (const Uncopyable&);

};

TI_NS_END

#endif /*THOR_IDIOMS_UNCOPY_H_*/