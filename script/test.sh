#!/bin/bash

TestModule() {
    cd ..
    ./bin/test-"$1"
    cd script
}


TestModule apply
TestModule functor
TestModule invoke
TestModule observer
TestModule pimpl
TestModule scope_guard
TestModule singleton
TestModule factory
TestModule visitor
TestModule any
TestModule variant
TestModule optional
TestModule object_pool