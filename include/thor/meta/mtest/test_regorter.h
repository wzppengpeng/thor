#ifndef THOR_META_MTEST_TEST_REPORTER_H_
#define THOR_META_MTEST_TEST_REPORTER_H_

#include <iostream>

#include "test_register.h"

TM_NS_BEGIN

#define __RED     "\033[1;31m"
#define __GREEN   "\033[1;32m"
#define __YELLOW  "\033[1;33m"
#define __BLUE    "\033[1;34m"
#define __MAGENTA "\033[1;35m"
#define __CYAN    "\033[1;36m"
#define __WHITE   "\033[0m"

struct TestPrintReporter : TestReporter
{
    static int report()
    {
        static TestPrintReporter reporter;
        reporter.doReport();
        return 0;
    }

private:
    void onFixtureStart(std::string name, const size_t testNum) override
    {
        allFixtureNum++;
        allTestsNum += testNum;

        std::cout << __GREEN << "[----------] "
                  << __WHITE << testNum << " tests from " << name << std::endl
                  << __GREEN << "[----------] " << std::endl;
    }

    void onFixtureEnd(std::string name, const size_t testNum) override
    {
        std::cout << __GREEN << "[----------] "
                  << __WHITE << testNum << " tests from " << name << std::endl << std::endl;
    }

    void onTest(std::string fixtureName, std::string testName) override
    {
        std::cout << __GREEN << "[ RUN      ] "
                  << __WHITE << fixtureName << "::" << testName << std::endl
                  << __GREEN << "[       OK ] " << std::endl;
    }

private:
    void onTestReportStart()
    {
        std::cout << __GREEN << "[==========] "
                  << __WHITE << "List all test cases:" << std::endl << std::endl;
    }

    void onTestReportEnd()
    {
        std::cout << __GREEN << "[==========] "
            << __WHITE << allFixtureNum << " fixtures, "
            << __WHITE << allTestsNum << " test cases ran OK!" << std::endl;
    }

    void onTestReporting()
    {
        TestRegister::getInstance().report(*this);
    }

    void doReport()
    {
        onTestReportStart();
        onTestReporting();
        onTestReportEnd();
    }

private:
    size_t allTestsNum{0};
    size_t allFixtureNum{0};
};

TM_NS_END

#define TM_REPORT_ALL_TESTS() TM_NS::TestPrintReporter::report()

#endif /*THOR_META_MTEST_TEST_REPORTER_H_*/
