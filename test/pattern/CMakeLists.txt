
ADD_EXECUTABLE(test-singleton singleton/test_singleton.cpp)
ADD_EXECUTABLE(test-pimpl pimpl/type.cpp pimpl/main.cpp)
ADD_EXECUTABLE(test-observer observer/observer.cpp)

AUX_SOURCE_DIRECTORY(./factory FACTORY_SRC_LIST)
ADD_EXECUTABLE(test-factory ${FACTORY_SRC_LIST})

AUX_SOURCE_DIRECTORY(./visitor VISITOR_SRC_LIST)
ADD_EXECUTABLE(test-visitor ${VISITOR_SRC_LIST})