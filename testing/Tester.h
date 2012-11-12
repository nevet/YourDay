
#include "gtest/gtest.h" //include to use Google Unit test's stuff

#include "AddExecutor.h"
#include "DeleteExecutor.h"
#include "SearchExecutor.h"
#include "UpdateExecutor.h"
#include "ExitExecutor.h"

/************************************************************************/

/* We write test cases here */

/************************************************************************/
//@author A0088455R
TEST(add_executor,general_entry)
{
	vector<string>* testGeneralVectorPointer;
	vector<string>* testCalendarVectorPointer;
	vector<string>* testResultVectorPointer;
	vector<string> testGeneralVector;
	vector<string> testCalendarVector;
	vector<string> testResultVector;


	testResultVectorPointer = &testResultVector;
	testGeneralVectorPointer=&testGeneralVector;
	testCalendarVectorPointer=&testCalendarVector;

	// This test to test the General Vector input function
	// #index#description#location#time#date#mark#
	// We wil purposefully set the date and time empty
	string details = "##Meeting CS2103#UTown###*#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	addExec.execute();
	ASSERT_EQ(testGeneralVector[0],"##Meeting CS2103#UTown###*#");
}
//@author A0091734A
TEST(add_executor,calendar_entry)
{
	vector<string>* testGeneralVectorPointer;
	vector<string>* testCalendarVectorPointer;
	vector<string>* testResultVectorPointer;
	vector<string> testGeneralVector;
	vector<string> testCalendarVector;
	vector<string> testResultVector;


	testResultVectorPointer = &testResultVector;
	testGeneralVectorPointer=&testGeneralVector;
	testCalendarVectorPointer=&testCalendarVector;

	// This test to test the Calendaer Vector input function
	// #index#description#location#time#date#mark#
	// We wil purposefully give the full entry to the list
	string details = "##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	addExec.execute();
	ASSERT_EQ(testCalendarVector[0],"##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#");
}
//@author A0091734A
 TEST(add_executor,combined_entries)
{
	vector<string>* testGeneralVectorPointer;
	vector<string>* testCalendarVectorPointer;
	vector<string>* testResultVectorPointer;
	vector<string> testGeneralVector;
	vector<string> testCalendarVector;
	vector<string> testResultVector;


	testResultVectorPointer = &testResultVector;
	testGeneralVectorPointer=&testGeneralVector;
	testCalendarVectorPointer=&testCalendarVector;

	// This test to test the Calendaer Vector input function
	// #index#description#location#time#date#priority#
	// We wil purposefully give the full entry to the list
	string details = "##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	addExec.execute();
    details = "##Meeting CS2103#UTown###*#";
	AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	addExec1.execute();
	ASSERT_EQ(testGeneralVector[0],"##Meeting CS2103#UTown###*#");
	ASSERT_EQ(testCalendarVector[0],"##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#");
}
 //@author A0091734A
 TEST(delete_executor,calendar_entry)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;

	 string details;
	 //we add 5 different entries to Calendar entry Lists.
	
	 details = "##1.Meeting CS2103#UTown#13:00-14:01#21/10/2012#*#";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec1.execute();
	 details = "##2.Meeting CS2103#UTown#13:01-14:02#21/10/2012#*#";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec2.execute();
	 details = "##3.Meeting CS2103#UTown#13:02-14:00#21/10/2012#*#";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec3.execute();
	 details = "##4.Meeting CS2103#UTown#13:03-14:00#21/10/2012#*#";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec4.execute();
	 details = "##5.Meeting CS2103#UTown#13:04-14:00#21/10/2012#*#";
	 AddExecutor addExec5(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec5.execute();
	 // This part is to test the General Vector delete function
	 // #index#description#location#time#date#mark#
	 // We wil purposefully give the correct details to deleteExecutor
	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#3######",CALENDAR);
	 //Here we delete the 3rd entry , so the output should be 4 entries without the 3rd one.
	  delExec.execute();
	  ASSERT_EQ(testCalendarVector[0],"##1.Meeting CS2103#UTown#13:00-14:01#21/10/2012#*#");
	  ASSERT_EQ(testCalendarVector[1],"##2.Meeting CS2103#UTown#13:01-14:02#21/10/2012#*#");
	  ASSERT_EQ(testCalendarVector[2],"##4.Meeting CS2103#UTown#13:03-14:00#21/10/2012#*#");
	  ASSERT_EQ(testCalendarVector[3],"##5.Meeting CS2103#UTown#13:04-14:00#21/10/2012#*#");
	 
 }
 //@author A0091734A
 TEST(delete_executor,general_entry)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	
	 string details;
	 //we add 5 different entries to General Lists.
	  for (int i = 0; i < 5; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown###high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
		 addExec.execute();
	 }

	  // This part is to test the General Vector delete function
	  // #index#description#location#time#date#priority#
	  // We wil purposefully give the correct details to deleteExecutor
	  DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#3######",GENERAL);
	  delExec.execute();
	  //Here we delete the 3rd entry , so the output should be 4 entries without the thrid one.
	 
	  ASSERT_EQ(testGeneralVector[0],"##1.Meeting CS2103#UTown###high#");
	  ASSERT_EQ(testGeneralVector[1],"##2.Meeting CS2103#UTown###high#");
	  ASSERT_EQ(testGeneralVector[2],"##4.Meeting CS2103#UTown###high#");
	  ASSERT_EQ(testGeneralVector[3],"##5.Meeting CS2103#UTown###high#");
	
 }
 //@author A0091734A
 TEST(delete_executor,combined_entries)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;

	 string details;

	 for (int i = 0; i < 3; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown###high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
		 addExec.execute();
	 }// we add three different entries to general List
	 
	 for (int i = 0; i < 2; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
		 addExec.execute();
	 }// we add two general event to calendar entry list.

	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#1######",CALENDAR);
	 delExec.execute();
	 //the 1st entry of CalendarVector should be deleted.
	 
	 DeleteExecutor delExec2(testGeneralVectorPointer, testCalendarVectorPointer, "#3######",GENERAL);
	 delExec2.execute();
	 //Here we delete the 3rd entry ,it should be the 3rd entry of generalVecotr
	 //The expectation should be three entry including two general entries and one calendar entries.
	  
	 ASSERT_EQ(testGeneralVector[0],"##1.Meeting CS2103#UTown###high#");
	 ASSERT_EQ(testGeneralVector[1],"##2.Meeting CS2103#UTown###high#");
	 ASSERT_EQ(testCalendarVector[0],"##1.Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#");

 }
 //@author A0091734A
 TEST(update_executor,combined_entries)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 Signal focusingField;
	 int lastEntry;
	 string details;

	 for (int i = 0; i < 3; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown###high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
		 addExec.execute();
	 }// we add three different entries to general List

	 for (int i = 0; i < 2; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
		 addExec.execute();
	 }// we add two general event to calendar entry list.
	 
	 //this one would be testing on updating full information
	 focusingField = CALENDAR;
	 details = "#1#CS2103 Lecture#ICUBE#14:00-15:00#08/11/2012#low#";
	 UpdateExecutor uptExec0(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details ,focusingField);
	 uptExec0.execute();
	 ASSERT_EQ(testCalendarVector[0],"##CS2103 Lecture#ICUBE#14:00-15:00#08/11/2012#low#");
	 
	 //this one would be testing on an incomplete update with only description
	 focusingField = GENERAL;
	 details = "#2#CS2103 Lecture#####";
	 UpdateExecutor uptExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details ,focusingField);
	 uptExec1.execute();
	 ASSERT_EQ(testGeneralVector[1],"##CS2103 Lecture#UTown###high#");
	
	 //this one would be testing on an imcomplete update with only Time
	 focusingField = CALENDAR;
	 details = "#1###14:01-15:02###";
	 UpdateExecutor uptExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details ,focusingField);
	 uptExec2.execute();
	 ASSERT_EQ(testCalendarVector[0],"##CS2103 Lecture#ICUBE#14:01-15:02#08/11/2012#low#");

	 //this one would be testing on an incomplete update with Time&Date when the foucing filed is General
	 //The entry in General List should be updated to Calendar List 's lastentry. 
	 focusingField = GENERAL;
	 details = "#1###13:00-14:00#09/11/2012##"; 
	 UpdateExecutor uptExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details ,focusingField);
	 uptExec3.execute();
	 lastEntry=testCalendarVectorPointer->size()-1;
	 ASSERT_EQ(testCalendarVector[lastEntry], "##1.Meeting CS2103#UTown#13:00-14:00#09/11/2012#high#");
	 
 }
 //@author A0091734A
 TEST(basic_test,search_executor)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string>* matchedListPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;
	 vector<string> matchedList;


	 string details;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 matchedListPointer=&matchedList;
	 testResultVectorPointer = &testResultVector;

	 details = "##I am Wu Pei, the test leader of our group.####";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec1.execute();
	 details =  "##Sometimes I feel sad, because as a tester, I find it is harder.####";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec2.execute();
	 details =  "##But most time I am still happy, because I am in a nice group.####";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec3.execute();
	 details =  "##So, I am painful but happy now.####";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec4.execute();

	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##wu pei####");
	 searchExec1.execute();	
	 //	 this is only one entry containing "wu pei".
	 ASSERT_EQ(matchedList[0],"#G0#I am Wu Pei, the test leader of our group.####");
	 matchedList.clear();
	 SearchExecutor searchExec2(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##time####");
	 searchExec2.execute();
	 //there is one entry containing "time".
	 ASSERT_EQ(matchedList[0],"#G2#But most time I am still happy, because I am in a nice group.####");
	
 }
 //@author A0091734A
 TEST(Power_search_test, nothing_matched)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string>* matchedListPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;
	 vector<string> matchedList;
	 string details;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 matchedListPointer=&matchedList;
	 testResultVectorPointer = &testResultVector;

	 details = "##Wu Pei####";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec1.execute();
	 details =  "##Ignatius Damai####";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec2.execute();
	 details =  "##Nhu Thao Nguyen####";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec3.execute();
	 details =  "##Da Huang####";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec4.execute();

	 SearchExecutor searchExec(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##Soe Myat####");
	 searchExec.execute();
	 //As nothing matched, there should be no result.
	 // ASSERT_EQ(matchedListPointer->size(),0);

 }
 //@author A0091734A
 TEST(power_search_test, time_search)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string>* matchedListPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;
	 vector<string> matchedList;


	 string details;

	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 matchedListPointer=&matchedList;
	 testResultVectorPointer = &testResultVector;

	 Signal focusingField;
	 int lastEntry;


	 details = "##Meeting CS2100#UTown#13:01-13:05#21/10/2012#high#";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec1.execute();
	 details = "##Meeting CS2103#UTown#13:05-14:00#21/10/2012#high#";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);;
	 addExec2.execute();
	 details =  "##Meeting CS2106#UTown#15:00-18:00#21/10/2012#high#";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec3.execute();
	 details = "##Meeting CS2104#UTown#16:00-19:00#20/10/2012#high#";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec4.execute();
	 //when there are two calendar entries containing this specific time, one is at front ,one is at the back
	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##13:05####");
	 searchExec1.execute();
	 ASSERT_EQ(matchedList[0],"#C2#Meeting CS2103#UTown#13:05-14:00#21/10/2012#high#");
	// ASSERT_EQ(matchedList[1],"#C1#Meeting CS2100#UTown#13:01-13:05#22/10/2012#high#");
	 ASSERT_EQ(matchedListPointer->size(),2);
	 matchedList.clear();
	 //when there are two calendar entries containing the same time, one is in the between, one is at the front.
	 SearchExecutor searchExec2(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##16:00####");
	 searchExec2.execute();
	 ASSERT_EQ(matchedList[0],"#C0#Meeting CS2104#UTown#16:00-19:00#20/10/2012#high#");
	 ASSERT_EQ(matchedList[1],"#C3#Meeting CS2106#UTown#15:00-18:00#24/10/2012#high#");
	 ASSERT_EQ(matchedListPointer->size(),2);
	 //when there is no entry containing this specific time.
	 SearchExecutor searchExec3(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##14:02####");
	 searchExec3.execute();
	 ASSERT_EQ(matchedListPointer->size(),0);
 }
 //@author A0091734A
 TEST(power_search_test, date_search)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string>* matchedListPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;
	 vector<string> matchedList;


	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 matchedListPointer=&matchedList;
	 testResultVectorPointer = &testResultVector;

	 Signal focusingField;
	 int lastEntry;
	 string details;

	 details = "##Meeting CS2100#UTown#13:01-13:05#21/10/2012#high#";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec1.execute();
	 details = "##Meeting CS2103#UTown#13:05-14:00#21/10/2012#high#";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec2.execute();
	 details =  "##Meeting CS2103#UTown#15:00-18:00#21/10/2012#high#";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec3.execute();
	 details = "##Meeting CS2103#UTown#16:00-19:00#20/10/2012#high#";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec4.execute();
	 //when there are two calendar entries containing this specific time, one is at front ,one is at the back
	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##21/10/20212####");
	 searchExec1.execute();
	 ASSERT_EQ(matchedList[0],"##Meeting CS2103#UTown#15:00-18:00#21/10/2012#high#");
	 ASSERT_EQ(matchedListPointer->size(),1);


 }
 //@author A0091734A
 TEST(undo_test,add_undo)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 // This test to test the General Vector input function
	 // #index#description#location#time#date#priority#
	 // We wil purposefully set the date and time empty
	 string details = "##Meeting CS2103#UTown###high#";
	 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec.execute();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());
	
	 addExec.undo();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());
 }
 //@author A0091734A
 TEST(undo_test,delete_undo)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;
	 // This test to test the General Vector input function
	 // #index#description#location#time#date#priority#
	 // We wil purposefully set the date and time empty
	 string details = "##Meeting CS2103#UTown###high#";
	 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec.execute();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#1######",GENERAL);
	 delExec.execute();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());

	 delExec.undo();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

 }
 //@author A0091734A
 TEST(undo_test,consecutive_undo)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;

	 // This test to test the General Vector input function
	 // #index#description#location#time#date#priority#
	 // We wil purposefully set the date and time empty
	 string details = "##Meeting CS2103#UTown###high#";
	 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
	 addExec.execute();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#1######",GENERAL);
	 delExec.execute();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());

	 delExec.undo();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

	 addExec.undo();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());
 }
  //@author A0091734A
 TEST(integration_test,ui_to_add)
 {

 }

 /*
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
 }*/
 //@author A0091734A
 TEST(systematic_test, adding_performance_test_100entries)
 {
	 vector<string>* testGeneralVectorPointer;
	 vector<string>* testCalendarVectorPointer;
	 vector<string>* testResultVectorPointer;
	 vector<string> testGeneralVector;
	 vector<string> testCalendarVector;
	 vector<string> testResultVector;


	 testResultVectorPointer = &testResultVector;
	 testGeneralVectorPointer=&testGeneralVector;
	 testCalendarVectorPointer=&testCalendarVector;

	 string details;
	 //we add 5 different entries to Calendar entry Lists.
	 for (int i = 0; i < 100; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 details = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, details);
		 addExec.execute();
	 }
	 ASSERT_EQ(testCalendarVector.size(),100);
 }

 
void runTest(int argument_count, char** argument_vars)

{

testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest

RUN_ALL_TESTS();

std::getchar(); //pause the program after all the testing

}
