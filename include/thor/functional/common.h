#ifndef THOR_FUNCTIONAL_COMMON_H_
#define THOR_FUNCTIONAL_COMMON_H_

/**
 * the macro of namespace declaration
 */
#define TF_NS thor::fuctional

#define TF_NS_BEGIN namespace thor {\
    namespace fuctional {

#define TF_NS_END }\
    }

#define DECLARE_LAMBDA_FUNCTION_TEMPLATE(NAME) \
    template<typename Fun>                     \
    class NAME : public NAME<decltype(&Fun::operator())> {}; \
                                                                   \
    template<typename R, typename... Args>                         \
    class NAME<R(*)(Args...)> : public NAME<R(Args...)> {};


#define DECLARE_MEMBER_FUNCTION_POINTER_TEMPLATE(NAME) \
    template<typename C, typename R, typename... Args> \
    class NAME<R(C::*)(Args...)> : public NAME<R(Args...)> {}; \
                                                                    \
    template<typename C, typename R, typename... Args>              \
    class NAME<R(C::*)(Args...) const> : public NAME<R(Args...)> {}; \
                                                                            \
    template<typename C, typename R>                                        \
    class NAME<R(C::*)> : public NAME <R()> {};

#endif /*THOR_FUNCTIONAL_COMMON_H_*/