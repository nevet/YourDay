
#include "gtest/gtest.h" //include to use Google Unit test's stuff

/************************************************************************/

/* We write test cases here */

/************************************************************************/



 

void runTest(int argument_count, char** argument_vars)

{

testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest

RUN_ALL_TESTS();

std::getchar(); //pause the program after all the testing

}
