#ifndef THOR_PATTERN_VISITOR_H_
#define THOR_PATTERN_VISITOR_H_

#include "thor/meta/list/type_list.h"

#include "common.h"

/**
 * The helper to generate the code of visitor pattern
 */

TP_NS_BEGIN

// the delaration
template<typename TL> struct Visitor;

template<typename Head, typename Tail>
struct Visitor<TM_NS::TypeElem<Head, Tail>> : Visitor<Tail> {
    using Visitor<Tail>::Visit;
    virtual void Visit(Head&) = 0;
};

template<typename Head>
struct Visitor<TM_NS::TypeElem<Head, TM_NS::NullType>> {
    virtual void Visit(Head&) = 0;
};

TP_NS_END

// delare a macro to generate the code of Accept in host class
#define DEFINE_VISITOR_ACCEPT_FUNCTION(VISITOR) \
void Accept(VISITOR& visitor) override { \
    visitor.Visit(*this); \
}

#endif /*THOR_PATTERN_VISITOR_H_*/