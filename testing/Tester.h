
#include "gtest/gtest.h" //include to use Google Unit test's stuff

#include "AddExecutor.h"



/************************************************************************/

/* We write test cases here */

/************************************************************************/

TEST(add_executor,general_entry)
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

TEST(add_executor,calendar_entry)
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

 TEST(add_executor,combined_entries)
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

 TEST(delete_executor,calendar_entry)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;


	 string details;
	 //we add 5 different entries to Calendar entry Lists.
	 for (int i = 0; i < 5; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
		 addExec.execute();
	 }
	 // This part is to test the General Vector delete function
	 // #index#description#location#time#date#priority#
	 // We wil purposefully give the correct details to deleteExecutor
	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#3######");
	 //Here we delete the 3rd entry , so the output should be 4 entries without the third one.
	  delExec.execute();
	  ASSERT_EQ(testCalendarVector[0],"##1.Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");
	  ASSERT_EQ(testCalendarVector[1],"##2.Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");
	  ASSERT_EQ(testCalendarVector[2],"##4.Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");
	  ASSERT_EQ(testCalendarVector[3],"##5.Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");
	 
 }

 TEST(delete_executor,general_entry)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;

	
	 string details;
	 //we add 5 different entries to General Lists.
	  for (int i = 0; i < 5; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown###high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
		 addExec.execute();
	 }

	  // This part is to test the General Vector delete function
	  // #index#description#location#time#date#priority#
	  // We wil purposefully give the correct details to deleteExecutor
	  DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#3######");
	  delExec.execute();
	  //Here we delete the 3rd entry , so the output should be 4 entries without the thrid one.
	 
	  ASSERT_EQ(testGeneralVector[0],"##1.Meeting CS2103#UTown###high#");
	  ASSERT_EQ(testGeneralVector[1],"##2.Meeting CS2103#UTown###high#");
	  ASSERT_EQ(testGeneralVector[2],"##4.Meeting CS2103#UTown###high#");
	  ASSERT_EQ(testGeneralVector[3],"##5.Meeting CS2103#UTown###high#");
	
 }

 TEST(delete_executor,combined_entries)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;


	 string details;

	 for (int i = 0; i < 3; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown###high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
		 addExec.execute();
	 }// we add three different entries to general List
	 
	 for (int i = 0; i < 2; i++)
	 {
		 ostringstream convert;
		 convert<<testGeneralVector.size()+i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
		 addExec.execute();
	 }// we add two general event to calendar entry list.

	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#4######");
	 delExec.execute();
	 //Here we delete the 4th entry ,it should be the 1st entry of CalendarVector as the Calendar Entry's index is its' own index + GenerlVector's size, 
	 //so here the 1st entry of CalendarVector should be deleted.
	 
	 DeleteExecutor delExec2(testGeneralVectorPointer, testCalendarVectorPointer, "#3######");
	 delExec2.execute();
	 //Here we delete the 3rd entry ,it should be the 3rd entry of generalVecotr
	 //The expectation should be three entry including two general entries and one calendar entries.
	  
	 ASSERT_EQ(testGeneralVector[0],"##1.Meeting CS2103#UTown###high#");
	 ASSERT_EQ(testGeneralVector[1],"##2.Meeting CS2103#UTown###high#");
	 ASSERT_EQ(testCalendarVector[0],"##5.Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");

 }

 TEST(basic_test,search_executor_)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* matchedListPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> matchedList;

	 string details;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 matchedListPointer=&matchedList;

	
	 details = "##I am Wu Pei, the test leader of our group.####";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, details);
	 addExec1.execute();
	 details =  "##Sometimes I feel sad, because as a tester, I find it is harder.####";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, details);
	 addExec2.execute();
	 details =  "##But most time I am still happy, because I am in a nice group.####";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, details);
	 addExec3.execute();
	 details =  "##So, I am painful but happy now.####";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, details);
	 addExec4.execute();

	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##wupei####");
	 searchExec1.execute();
	 //this is only one entry containing "wupei".
	 ASSERT_EQ(matchedList[0],"##I am Wu Pei, the test leader of our group.####");

	 SearchExecutor searchExec2(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##time####");
	 searchExec2.execute();
	 //this is only one entry containing "wupei".
	 ASSERT_EQ(matchedList[0],"##But most time I am still happy, because I am in a nice group.####");
	 ASSERT_EQ(matchedList[1],"##Sometimes I feel sad, because as a tester, I find it is harder.####");
 }

 TEST(undo_test,add_undo)
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

	 EXPECT_EQ(1,testGeneralVectorPointer->size());
	
	 addExec.undo();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());
 }

 TEST(undo_test,delete_undo)
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

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#1######");
	 delExec.execute();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());

	 delExec.undo();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

 }

 TEST(undo_test,consecutive_undo)
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

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#1######");
	 delExec.execute();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());

	 delExec.undo();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

	 addExec.undo();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());
 }

 TEST(integration_test,ui_to_add)
 {

 }


 TEST(systematic_test, adding_performance_test_1000entries)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;


	 string details;
	 //we add 5 different entries to Calendar entry Lists.
	 for (int i = 0; i < 1000; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
		 addExec.execute();
	 }
 }

 TEST(systematic_test, adding_performance_test_100entries)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;


	 string details;
	 //we add 5 different entries to Calendar entry Lists.
	 for (int i = 0; i < 100; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, details);
		 addExec.execute();
	 }
 }

void runTest(int argument_count, char** argument_vars)

{

testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest

RUN_ALL_TESTS();

std::getchar(); //pause the program after all the testing

}
