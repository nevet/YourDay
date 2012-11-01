
#include "gtest/gtest.h" //include to use Google Unit test's stuff

#include "AddExecutor.h"



/************************************************************************/

/* We write test cases here */

/************************************************************************/

TEST(basic_test,add_executor_1)
{
	vector<string>* testGeneralVectorPointer;
	vector<string>* testCalendarVectorPointer;
	vector<string> testGeneralVector;
	vector<string> testCalendarVector;
	
	testGeneralVectorPointer=&testGeneralVector;
	testCalendarVectorPointer=&testCalendarVector;

	// This test to test the General Vector input function
	// #index#description#location#time#date#priority#
	// We wil purposefully set the date and time empty
	string details = "##Meeting CS2103#UTown###high#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
	addExec.execute();
	ASSERT_EQ(testGeneralVector[0],"##Meeting CS2103#UTown###high#");
}

/*TEST(basic_test,add_executor_2)
{
	vector<string>* testGeneralVectorPointer;
	vector<string>* testCalendarVectorPointer;
	vector<string> testGeneralVector;
	vector<string> testCalendarVector;
	
	testGeneralVectorPointer=&testGeneralVector;
	testCalendarVectorPointer=&testCalendarVector;

	// This test to test the Calendaer Vector input function
	// #index#description#location#time#date#priority#
	// We wil purposefully give the full entry to the list
	string details = "##Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
	addExec.execute();
	ASSERT_EQ(testCalendarVector[0],"##Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");
}*/

 TEST(basic_test,add_executor_2)
{
	vector<string>* testGeneralVectorPointer;
	vector<string>* testCalendarVectorPointer;
	vector<string> testGeneralVector;
	vector<string> testCalendarVector;
	
	testGeneralVectorPointer=&testGeneralVector;
	testCalendarVectorPointer=&testCalendarVector;

	// This test to test the Calendaer Vector input function
	// #index#description#location#time#date#priority#
	// We wil purposefully give the full entry to the list
	string details = "##Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
	addExec.execute();
	ASSERT_EQ(testCalendarVector[0],"##Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");
}


void runTest(int argument_count, char** argument_vars)

{

testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest

RUN_ALL_TESTS();

std::getchar(); //pause the program after all the testing

}
