
#include "gtest/gtest.h" //include to use Google Unit test's stuff

#include "AddExecutor.h"
#include "DeleteExecutor.h"
#include "SearchExecutor.h"
#include "UpdateExecutor.h"
#include "ExitExecutor.h"

vector<string>* testGeneralVectorPointer;
vector<string>* testCalendarVectorPointer;
vector<string>* testResultVectorPointer;
vector<string>* matchedListPointer;
vector<string> testGeneralVector;
vector<string> testCalendarVector;
vector<string> testResultVector;
vector<string> matchedList;
string EncodedUserInput;
Signal focusingField;
/************************************************************************/

/* We write test cases here */

/************************************************************************/
//@author A0088455R
TEST(add_executor,general_entry_simple_add)
{
	// This test to test the General Vector input function
	// #index#description#location#time#date#mark#
	// We wil purposefully set the date and time empty
	EncodedUserInput = "##Meeting CS2103#UTown###*#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer,EncodedUserInput);
	addExec.execute();
	ASSERT_EQ(testGeneralVector[0],"##Meeting CS2103#UTown###*#");
}

/**
* Test Target: AddExecutor
* Test objective: The entry with time/date information would be added into Calendar List automatically.
* Assumption: We will purposefully give EncodedUserInput to the list
*/
//@author A0091734A
TEST(add_executor,calendar_entry_simple_add)
{
	//The format of UserInput should be: #index#description#location#time#date#mark#
	EncodedUserInput = "##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#";
	AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	addExec.execute();

	ASSERT_EQ(testCalendarVector[0],"##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#");
}

/**
* Test Target: AddExecutor
* Test objective: The calendar entries added into Calendar List would be sorted by time in increasing order automatically.
* Assumption: We will purposefully give EncodedUserInput to the list
*/
//@author A0091734A
TEST(add_executor,calendar_entry_automaitcally_sorting_by_time)
{
	//The format of UserInput should be: #index#description#location#time#date#mark#
	EncodedUserInput = "##Meeting CS2100#UTown#12:00-13:00#21/10/2012#*#";
	AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	addExec1.execute();
	EncodedUserInput = "##Lecture CS2103#Soc#15:00-17:00#21/10/2012#*#";
	AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	addExec2.execute();
	//Test by comparing desired result with entryList
	ASSERT_EQ(testCalendarVector[0],"##Meeting CS2100#UTown#12:00-13:00#21/10/2012#*#");
	ASSERT_EQ(testCalendarVector[1],"##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#");
	ASSERT_EQ(testCalendarVector[2],"##Lecture CS2103#Soc#15:00-17:00#21/10/2012#*#");
}

/**
* Test Target: AddExecutor
* Test objective: The calendar entries added into Calendar List would be sorted by date in increasing order automatically.
* Assumption: We will purposefully give EncodedUserInput to the list
*/
//@author A0091734A
TEST(add_executor,calendar_entry_automaitcally_sorting_by_date)
{
	//The format of UserInput should be: #index#description#location#time#date#mark#
	EncodedUserInput = "##Meeting CG2100#UTown#12:00-13:00#20/10/2012#*#";
	AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	addExec1.execute();
	EncodedUserInput = "##Lecture CG2103#Soc#15:00-17:00#22/10/2012#*#";
	AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	addExec2.execute();
	//Test by comparing desired result with entryList
	ASSERT_EQ(testCalendarVector[0],"##Meeting CG2100#UTown#12:00-13:00#20/10/2012#*#");
	ASSERT_EQ(testCalendarVector[1],"##Meeting CS2100#UTown#12:00-13:00#21/10/2012#*#");
	//Except the following entry, other entries all before 22/10, so the following entry should be at the end of vector
	ASSERT_EQ(testCalendarVector[4],"##Lecture CG2103#Soc#15:00-17:00#22/10/2012#*#");
}

/**
* Test Target: AddExecutor
* Test objective: Test on whether calendar entry and general entry work fine independently.
* Assumption: We will purposefully give EncodedUserInput to the list
*/
//@author A0091734A
TEST(add_executor,Integration_test)
{
	// This test to test the Calendaer Vector input function
	// #index#description#location#time#date#priority#
	// We wil purposefully give the full entry to the list
	ASSERT_EQ(testGeneralVector[0],"##Meeting CS2103#UTown###*#");
	ASSERT_EQ(testCalendarVector[0],"##Meeting CG2100#UTown#12:00-13:00#20/10/2012#*#");
}

/**
 * Test Target: DeleteExecutor
 * Test objective: Test on deleting calendar entry.
 * Assumption: We will purposefully give EncodedUserInput to the list
 *             We use the entry List we added in previous tests.
 */
 //@author A0091734A
TEST(delete_executor,calendar_entry)
 {

	 //The format of UserInput should be: #index#description#location#time#date#mark#
	  DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#3######",CALENDAR);
	 //Here we delete the 3rd entry , so the output should be 4 entries without the 3rd one.
	 //Based on the previous test, the 3rd entry should be "##Meeting CS2103#UTown#13:00-14:00#21/10/2012#*#"
	  delExec.execute();
	  ASSERT_EQ(testCalendarVector[0],"##Meeting CG2100#UTown#12:00-13:00#20/10/2012#*#");
	  ASSERT_EQ(testCalendarVector[1],"##Meeting CS2100#UTown#12:00-13:00#21/10/2012#*#");
	  ASSERT_EQ(testCalendarVector[2],"##Lecture CS2103#Soc#15:00-17:00#21/10/2012#*#");
	  ASSERT_EQ(testCalendarVector[3],"##Lecture CG2103#Soc#15:00-17:00#22/10/2012#*#");
	 
 }

 /**
 * Test Target: DeleteExecutor
 * Test objective: Test on deleting general entry.
 * Assumption: We will purposefully give EncodedUserInput to the list
 *             We use a new General Entry list.
 */
 //@author A0091734A
 TEST(delete_executor,general_entry)
 {
	 //Clear original entry list
	 testGeneralVector.clear();
	 //we add 5 different entries to General Lists.
	  for (int i = 0; i < 5; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		  //The format of UserInput should be: #index#description#location#time#date#mark#
		 EncodedUserInput = "##" + convert.str()+ ".Meeting CS2103#UTown###*#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
		 addExec.execute();
	 }
	  
	  DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#3######",GENERAL);
	  delExec.execute();
	  //Here we delete the 3rd entry , so the output should be 4 entries without the thrid one.
	  ASSERT_EQ(testGeneralVector[0],"##1.Meeting CS2103#UTown###*#");
	  ASSERT_EQ(testGeneralVector[1],"##2.Meeting CS2103#UTown###*#");
	  ASSERT_EQ(testGeneralVector[2],"##4.Meeting CS2103#UTown###*#");
	  ASSERT_EQ(testGeneralVector[3],"##5.Meeting CS2103#UTown###*#");
	
 }

 /**
 * Test Target: DeleteExecutor
 * Test objective: Test on consecutive deleting on different entry list.
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use the entry List we operated in previous tests.
 */
 //@author A0091734A
 TEST(delete_executor,combined_entries)
 {
	 ASSERT_EQ(testGeneralVector.size(),4);
	 DeleteExecutor delExec2(testGeneralVectorPointer, testCalendarVectorPointer, "#3######",GENERAL);
	 delExec2.execute();
	 //the 1st entry of CalendarVector should be deleted.
	 ASSERT_EQ(testGeneralVector.size(),3);
	 ASSERT_EQ(testGeneralVector[2],"##5.Meeting CS2103#UTown###*#");

	 ASSERT_EQ(testCalendarVector.size(),4);
	 //The 3rd entry of GeneralVecotr should be deleted.
	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#1######",CALENDAR);
	 delExec.execute();
	 ASSERT_EQ(testCalendarVector.size(),3);
	 ASSERT_EQ(testCalendarVector[0],"##Meeting CS2100#UTown#12:00-13:00#21/10/2012#*#");
 }

 /**
 * Test Target: UpdateExecutor
 * Test objective: Test on updating full/partial information except for updating time/date on general Entry
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use the entry List we operated in previous tests.
 */
 //@author A0091734A
 TEST(update_executor,updating_full_partial_information_test)
 {
	 //this one would be testing on updating full information
	 focusingField = CALENDAR;
	 EncodedUserInput = "#1#CS2103 Lecture#ICUBE#14:00-15:00#08/11/2012# #";
	 UpdateExecutor uptExec0(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput ,focusingField);
	 uptExec0.execute();
	 ASSERT_EQ(testCalendarVector[0],"##CS2103 Lecture#ICUBE#14:00-15:00#08/11/2012# #");
	 
	 //this one would be testing on an incomplete update with only description
	 focusingField = GENERAL;
	 EncodedUserInput = "#2#CS2103 Lecture#####";
	 UpdateExecutor uptExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput ,focusingField);
	 uptExec1.execute();
	 ASSERT_EQ(testGeneralVector[1],"##CS2103 Lecture#UTown###*#");
	
	 //this one would be testing on an imcomplete update with only Time
	 focusingField = CALENDAR;
	 EncodedUserInput = "#1###14:01-15:02###";
	 UpdateExecutor uptExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput ,focusingField);
	 uptExec2.execute();
	 ASSERT_EQ(testCalendarVector[0],"##CS2103 Lecture#ICUBE#14:01-15:02#08/11/2012# #");
 }

 /**
 * Test Target: UpdateExecutor
 * Test objective: Test on updating a general entry to calendar entry by updating time/date
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *             We use a new calendar entry and new general entry
 */
 //@author A0091734A
TEST(update_executor,updating_time_date_on_general_entry)
{
	 testCalendarVector.clear();
	 testGeneralVector.clear();
	 //The format of UserInput should be: #index#description#location#time#date#mark#
	 //Add a general entry.
	 EncodedUserInput = "##Meeting CS2103#UTown###*#";
	 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec.execute();
	 ASSERT_EQ(testGeneralVector.size(),1);
	 ASSERT_EQ(testCalendarVector.size(),0);
	 focusingField = GENERAL;
	 EncodedUserInput = "#1###13:00-14:00#09/11/2012##"; 
	 UpdateExecutor uptExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput ,focusingField);
	 uptExec3.execute();

	 ASSERT_EQ(testGeneralVector.size(),0);
	 ASSERT_EQ(testCalendarVector.size(),1);
	 ASSERT_EQ(testCalendarVector[0], "##Meeting CS2103#UTown#13:00-14:00#09/11/2012#*#");
 }

 /**
 * Test Target: UpdateExecutor
 * Test objective: Test on updating the index
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *             We use a new calendar entry and new general entry
 */
 //@author A0091734A
TEST(update_executor,updating_index_test)
{
	testCalendarVector.clear();
	testGeneralVector.clear();
	for (int i = 0; i < 5; i++)
	{
		ostringstream convert;
		convert<<i+1;
		//The format of UserInput should be: #index#description#location#time#date#mark#
		EncodedUserInput = "##" + convert.str()+ ".Meeting CS2103#UTown###*#";
		AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
		addExec.execute();
	}
	//This sub-test-case test when the old index is smaller than new index.
	focusingField = GENERAL;
	EncodedUserInput = "#1#2####"; 
	UpdateExecutor uptExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput ,focusingField);
	uptExec.execute();
	ASSERT_EQ(testGeneralVector[0],"##2.Meeting CS2103#UTown###*#");
	ASSERT_EQ(testGeneralVector[1],"##1.Meeting CS2103#UTown###*#");

	//This sub-test-case test when the new index is smaller than old index.
	EncodedUserInput = "#3#1####"; 
	UpdateExecutor uptExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput ,focusingField);
	uptExec3.execute();

	ASSERT_EQ(testGeneralVector[0],"##3.Meeting CS2103#UTown###*#");
	ASSERT_EQ(testGeneralVector[1],"##2.Meeting CS2103#UTown###*#");
}
/**
 * Test Target: SearchExecutor
 * Test objective: Test basic search function
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
TEST(basic_test,search_executor)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 //build a new database for testing
	 EncodedUserInput = "##I am Wu Pei, the test leader of our group.####";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 EncodedUserInput =  "##Sometimes I feel sad, because as a tester, I find it is harder.####";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec2.execute();
	 EncodedUserInput =  "##But most time I am still happy, because I am in a nice group.####";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec3.execute();
	 EncodedUserInput =  "##So, I am painful but happy now.####";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec4.execute();
	 
	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##wupei####");
	 searchExec1.execute();
    //this is only one entry containing "wupei".
	 ASSERT_EQ(matchedList[0],"#G0#I am Wu Pei, the test leader of our group.####");
	 
	 SearchExecutor searchExec2(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##time####");
	 searchExec2.execute();
	 
	 ASSERT_EQ(matchedList[0],"#C0#But most time I am still happy, because I am in a nice group.####");
	 ASSERT_EQ(matchedList[1],"##Sometimes I feel sad, because as a tester, I find it is harder.####");
 }

 /**
 * Test Target: SearchExecutor
 * Test objective: Test when there is no entry mathced with the keyword
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
 TEST(Power_search_test, nothing_matched_test)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 EncodedUserInput = "##Wu Pei####";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec1.execute();
	 EncodedUserInput =  "##Ignatius Damai####";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec2.execute();
	 EncodedUserInput =  "##Nhu Thao Nguyen####";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec3.execute();
	 EncodedUserInput =  "##Da Huang####";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec4.execute();

	 SearchExecutor searchExec(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##Soe Myat####");
	 searchExec.execute();
	 //As nothing matched, there should be no result.
	ASSERT_EQ(matchedListPointer->size(),0);

 }
 
 /**
 * Test Target: SearchExecutor
 * Test objective: Test the typo searching,eg when there is a entry"have lunch" 
											  we saerch "lunvh", the entry will still be returned to matchedList
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
 TEST(Power_search_test, typo_test)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 //build a new database for testing
	 EncodedUserInput = "##I am going to have lunch with Damai####";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 EncodedUserInput =  "##Due Yourday in next 10 minutes####";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec2.execute();
	 EncodedUserInput =  "##Group meeting for CG2271 makes me die####";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec3.execute();
	 EncodedUserInput =  "##Start to do the CG2271 term assignment.####";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec4.execute();
	 //searching test constructor
	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##asignment####");
	 searchExec1.execute();
	 //Compare actual result with expected result.
	 ASSERT_EQ(matchedList[0],"#G3#Start to do the CG2271 term assignment.####");
 }

 /**
 * Test Target: SearchExecutor
 * Test objective: Test the time searching 
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
 TEST(power_search_test, time_search_test)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 EncodedUserInput = "##Meeting CS2100#UTown#13:01-13:05#21/10/2012#high#";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec1.execute();
	 EncodedUserInput = "##Meeting CS2103#UTown#13:05-14:00#21/10/2012#high#";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);;
	 addExec2.execute();
	 EncodedUserInput =  "##Meeting CS2103#UTown#15:00-18:00#21/10/2012#high#";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec3.execute();
	 EncodedUserInput = "##Meeting CS2103#UTown#16:00-19:00#20/10/2012#high#";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec4.execute();
	 //when there are two calendar entries containing this specific time, one is at front ,one is at the back
	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##13:05####");
	 searchExec1.execute();
	 ASSERT_EQ(matchedList[0],"##Meeting CS2103#UTown#13:05-14:00#21/10/2012#high#");
	 ASSERT_EQ(matchedList[1],"##Meeting CS2100#UTown#13:01-13:05#22/10/2012#high#");
	 ASSERT_EQ(matchedListPointer->size(),2);
	 //when there are two calendar entries containing the same time, one is in the between, one is at the front.
	 SearchExecutor searchExec2(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##16:00####");
	 searchExec2.execute();
	 ASSERT_EQ(matchedList[0],"##Meeting CS2104#UTown#16:00-19:00#23/10/2012#high#");
	 ASSERT_EQ(matchedList[1],"##Meeting CS2106#UTown#15:00-18:00#24/10/2012#high#");
	 ASSERT_EQ(matchedListPointer->size(),2);
	 //when there is no entry containing this specific time.
	 SearchExecutor searchExec3(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##14:02####");
	 searchExec3.execute();
	 ASSERT_EQ(matchedListPointer->size(),0);
 }

 /**
 * Test Target: SearchExecutor
 * Test objective: Test the date searching
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
 TEST(power_search_test, date_search_test)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 EncodedUserInput = "##Meeting CS2100#UTown#13:01-13:05#21/10/2012#high#";
	 AddExecutor addExec1(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec1.execute();
	 EncodedUserInput = "##Meeting CS2103#UTown#13:05-14:00#21/10/2012#high#";
	 AddExecutor addExec2(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec2.execute();
	 EncodedUserInput =  "##Meeting CS2103#UTown#15:00-18:00#21/10/2012#high#";
	 AddExecutor addExec3(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec3.execute();
	 EncodedUserInput = "##Meeting CS2103#UTown#16:00-19:00#20/10/2012#high#";
	 AddExecutor addExec4(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec4.execute();
	 //when there are two calendar entries containing this specific time, one is at front ,one is at the back
	 SearchExecutor searchExec1(testGeneralVectorPointer, testCalendarVectorPointer, matchedListPointer, "##21/10/20212####");
	 searchExec1.execute();
	 ASSERT_EQ(matchedList[0],"##Meeting CS2103#UTown#15:00-18:00#21/10/2012#high#");
	 ASSERT_EQ(matchedListPointer->size(),1);
	 
	 
 }

 /**
 * Test Target: SearchExecutor
 * Test objective: Test undo (undo after adding entry)
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
 TEST(undo_test,add_undo)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 EncodedUserInput = "##Meeting CS2103#UTown###high#";
	 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec.execute();

	 EXPECT_EQ(testGeneralVectorPointer->size(),1);
	
	 addExec.undo();

	 EXPECT_EQ(testGeneralVectorPointer->size(),0);
 }

 /**
 * Test Target: SearchExecutor
 * Test objective: Test undo (undo after deleting entry)
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
 TEST(undo_test,delete_undo)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 EncodedUserInput = "##Meeting CS2103#UTown###high#";
	 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
	 addExec.execute();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

	 DeleteExecutor delExec(testGeneralVectorPointer, testCalendarVectorPointer, "#1######",GENERAL);
	 delExec.execute();

	 EXPECT_EQ(0,testGeneralVectorPointer->size());

	 delExec.undo();

	 EXPECT_EQ(1,testGeneralVectorPointer->size());

 }

 /**
 * Test Target: SearchExecutor
 * Test objective: Test undo (undo after undo)
 * Assumption:  We will purposefully give EncodedUserInput to the list
 *              We use a new calendar entry and new general entry 
 */
 //@author A0091734A
 TEST(undo_test,consecutive_undo)
 {
	 testCalendarVector.clear();
	 testGeneralVector.clear();

	 EncodedUserInput = "##Meeting CS2103#UTown###high#";
	 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
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
	 //we add 5 different entries to Calendar entry Lists.
	 for (int i = 0; i < 100; i++)
	 {
		 ostringstream convert;
		 convert<<i+1;
		 EncodedUserInput = "##" + convert.str()+ ".Meeting CS2103#UTown#13:00-14:00#21/10/2012#high#";
		 AddExecutor addExec(testGeneralVectorPointer, testCalendarVectorPointer, testResultVectorPointer, EncodedUserInput);
		 addExec.execute();
	 }
	 ASSERT_EQ(testCalendarVector.size(),100);
 }

 
void runTest(int argument_count, char** argument_vars)

{

testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest

testResultVectorPointer = &testResultVector;
testGeneralVectorPointer=&testGeneralVector;
testCalendarVectorPointer=&testCalendarVector;
matchedListPointer=&matchedList;

RUN_ALL_TESTS();

std::getchar(); //pause the program after all the testing

}
