project(THOR)
cmake_minimum_required(VERSION 2.8)

SET(ENABLE_TEST_META   ON CACHE BOOL "Enable the test meta")
SET(ENABLE_TEST_PATTERN   ON CACHE BOOL "Enable the test pattern")
SET(ENABLE_TEST_IDIOMS   ON CACHE BOOL "Enable the test idioms")
SET(ENABLE_TEST_FUNCTIONAL   ON CACHE BOOL "Enable the test functional")

SET(THOR_HEADER_DIR ${PROJECT_SOURCE_DIR}/include)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")

IF(UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
ENDIF()

INCLUDE_DIRECTORIES(${THOR_HEADER_DIR})

IF(ENABLE_TEST_META)
    ADD_SUBDIRECTORY(test/meta)
ENDIF()


IF(ENABLE_TEST_PATTERN)
    ADD_SUBDIRECTORY(test/pattern)
ENDIF()

IF(ENABLE_TEST_IDIOMS)
    ADD_SUBDIRECTORY(test/idioms)
ENDIF()

IF(ENABLE_TEST_FUNCTIONAL)
    ADD_SUBDIRECTORY(test/functional)
ENDIF()