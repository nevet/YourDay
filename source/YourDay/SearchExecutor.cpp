#include<cassert>

#include "SearchExecutor.h"

//@author A0088455R
/**
* Sets predifined days of a month
**/
const int SearchExecutor::MONTH[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
* These are predefined value for the matching level of the
* keyword and the string inside the entry list
* applicable for searchDate and searchTime
**/
const int SearchExecutor::PERFECT_MATCH = 0;
const int SearchExecutor::HIGH_MATCH = 1;
const int SearchExecutor::MEDIOCORE_MATCH = 2;
const int SearchExecutor::LOW_MATCH = 3;
const int SearchExecutor::NO_MATCH = 4;

/**
* This methods retrieves user's input word by word ad erasing it from the whole
* chunk of input
**/
string SearchExecutor::splitFirstTerm(string* rawString)
{
	stringstream tempHolder;
	string firstTerm;
	char spaceEater;
	tempHolder<<*rawString;
	tempHolder>>firstTerm;
	(*rawString).erase(0,firstTerm.size()+1);
	return firstTerm;
}

void SearchExecutor::formatSearchResult(int index, string result, string* formattedResult)
{
	assert(result!="");

	ostringstream ostring;
	ostring << "#" << index << result.substr(1,result.size()-1);

	*formattedResult = ostring.str();
}

bool SearchExecutor::isLeap(int year)
{

	bool flag = false;
	
	if (year % 100 == 0)
	{
		if (year % 400 == 0)
		{
			flag = true;
		}
	} else
	{
		if (year % 4 == 0)
		{
			flag = true;
		}
	}

	return flag;
}

bool SearchExecutor::isDate(string date)
{
	int year, month, day;

	return sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) == 3;
}

bool SearchExecutor::isTime(string time)
{
	int hour, minute;

	return sscanf(time.c_str(), "%d:%d", &hour, &minute) == 2;
}

bool SearchExecutor::isLogicDate(string date)
{
	assert(date!="");
	int year, month, day;

	bool flag = true;

	//extract year, month and day from the string
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);

	if (year > 9999 || year < 1000)
	{
		flag = false;
	} else
	if (month > 12 || month < 1)
	{
		flag = false;
	} else
	if (day < 1)
	{
		flag = false;
	} else
	{
		if (day > MONTH[month - 1])
		{
			flag = false;
		} else
		{
			if (!isLeap(year) && month == 2 && day == 29)
			{
				flag =false;
			}
		}
	}

	return flag;
}

bool SearchExecutor::isLogicTime(string time)
{
	assert(time!="");
	int hour, minute;

	bool flag = true;

	sscanf(time.c_str(), "%d:%d", &hour, &minute);

	if (hour > 23 || hour < 0)
	{
		flag = false;
	} else
	if (minute > 59 || minute < 0)
	{
		flag = false;
	}

	return flag;
}

/**
* This method uses assign function of vector to assign a predefined value of 0
**/
void SearchExecutor::initializeVectors(int totalSize, vector<int>* score, vector<int>* rank)
{
	assert(score != NULL);
	assert(rank != NULL);

	score->clear();
	rank->clear();
	//assigns NULL value to both arrays with the size of totalSize
	score->assign(totalSize, NULL);
	rank->assign(totalSize, NULL);
}

/**
* This method initializes rank vector to the value of totalSize
* the ranks are going to be demoted later according to the match level
* highest rank = totalSize, lowest rank = 0
**/
void SearchExecutor::initializeRank(int totalSize, vector<int>* rank)
{
	rank->clear();
	rank->assign(totalSize,totalSize);
}

/**
* this method initializes the combined entry list consisting of
* general entry and calendar entry
**/
void SearchExecutor::initializeCombinedEntry()
{
	int i;
	int generalEntrySize = _generalEntryList->size();
	int calendarEntrySize = _calendarEntryList->size();
	for (i = 0; i < generalEntrySize; i++)
	{
		_combinedEntryList.push_back((*_generalEntryList)[i]);
	}
	for (i = 0; i < calendarEntrySize; i++)
	{
		_combinedEntryList.push_back( (*_calendarEntryList)[i]);
	}
}

/**
* This method changes the rank of each etry according to its level of match
**/
void SearchExecutor::setRank(int index, int level, vector<int>* rank, int* currentHighest)
{
	(*rank)[index]-= level;

	if( *currentHighest < (*rank)[index])
	{
		*currentHighest = (*rank)[index];
	}

}

/**
* This method adjust the rank if none of the entry has a perfect match
**/
void SearchExecutor::adjustRank(vector<int>* rank, int currentHighest)
{
	int listSize = _combinedEntryList.size();
	int i;
	if ( currentHighest > 1 )
	{
		for (i = 0; i < listSize; i++)
		{
			(*rank)[i] += ( listSize-currentHighest  );
			// The rank cannot be less than 0.
			if ( (*rank)[i] < 0 )
			{
				(*rank)[i] = 0;
			}
		}
	}
}

	

void SearchExecutor::splitWords(string encoded, vector<string>* list)
{
	string sentence = extractDescription(encoded) + " " + extractLocation(encoded);
	stringstream sin(sentence);

	string temp;

	while (sin >> temp)
	{
		list->push_back(temp);
	}
}

void SearchExecutor::calInfo(int i, int j, string a, string b, string & x, string & y, matchInfo & t)
{	
	if (i == 0)
	{
		t.ms += g[0][j];
		t.ms_lead += g[0][j];

		while (g[0][j])
		{
			x = " " + x;
			y = b[g[0][j] - 1] + y;

			g[0][j]--;
		}

		return;
	} else
	if (j == 0)
	{
		while (g[i][0])
		{
			x = a[g[i][0] - 1] + x;
			y = " " + y;

			g[i][0]--;
		}

		return;
	}

	switch (g[i][j])
	{
		case 0:
			//f[i-1][j]
			x = a[i - 1] + x;
			y = " " + y;

			calInfo(i - 1, j, a, b, x, y, t);

			break;
		
		case 1:
			//f[i][j-1]
			x = " " + x;
			y = b[j - 1] + y;
			t.ms++;

			if (!t.match && !t.change) t.ms_trail++;
			
			calInfo(i, j - 1, a, b, x, y, t);
			
			break;
		
		case 2:
			//not same
			x = a[i - 1] + x;
			y = a[i - 1] + y;
			t.change++;

			calInfo(i - 1, j - 1, a, b, x, y, t);

			break;

		case 3:
			// same
			x = a[i - 1] + x;
			y = b[j - 1] + y;
			t.match++;

			calInfo(i - 1, j - 1, a, b, x, y, t);

			break;
	}
}

int SearchExecutor::notsame(char a, char b)
{
	if (tolower(a) == tolower(b)) return 0;

	return 1;
}

void SearchExecutor::edit(string a, string b, matchInfo & ans)
{
	matchInfo temp;

	int lena = a.length();
	int lenb = b.length();

	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));

	for (int i = 1; i <= lena; i++)
	{
		f[i][0] = i;
		g[i][0] = i;
	}

	for (int i = 1; i <= lenb; i++)
	{
		f[0][i] = i;
		g[0][i] = i;
	}

	for (int i = 1; i <= lena; i++)
		for (int j = 1; j <= lenb; j++)
		{
			f[i][j] = f[i - 1][j] + 1;
			g[i][j] = 0;

			if (f[i][j - 1] + 1 < f[i][j])
			{
				f[i][j] = f[i][j - 1] + 1;
				g[i][j] = 1;
			}

			if (f[i - 1][j - 1] + notsame(a[i - 1], b[j - 1]) < f[i][j])
			{
				f[i][j] = f[i - 1][j - 1] + notsame(a[i - 1], b[j - 1]);
				if (notsame(a[i -1], b[j - 1]))
				{
					g[i][j] = 2;
				} else
				{
					g[i][j] = 3;
				}
			}
		}

	ans.dis = f[lena][lenb];

	string newa = "";
	string newb = "";

	calInfo(lena, lenb, a, b, newa, newb, ans);

	ans.continuity = ans.ms - (ans.ms_lead + ans.ms_trail);
}

bool SearchExecutor::cmp(matchInfo a, matchInfo b)
{
	bool flag = false;
	
	if (a.match > b.match)
	{
		flag = true;
	} else
	if (a.match < b.match)
	{
		flag = false;
	} else
	if (a.continuity < b.continuity)
	{
		flag = true;
	} else
	if (a.continuity > b.continuity)
	{
		flag = false;
	} else
	if (a.ms < b.ms)
	{
		flag = true;
	} else
	if (a.ms > b.ms)
	{
		flag = false;
	} else
	if (a.change < b.change)
	{
		flag = true;
	} else
	if (a.change > b.change)
	{
		flag = false;
	} else
	if (a.str < b.str)
	{
		flag = true;
	} else
	if (a.str > b.str)
	{
		flag = false;
	}

	return flag;
}

SearchExecutor::matchInfo SearchExecutor::compare(matchInfo a, matchInfo b)
{
	if (cmp(a, b))
	{
		return a;
	} else
	{
		return b;
	}
}

bool SearchExecutor::unrelavent(matchInfo info, string key)
{
	bool flag;

	if (info.match <= key.length() / 2)
	{
		flag = true;
	} else
	if (info.match <= info.str.length() / 2)
	{
		if (info.continuity > info.str.length() / 2)
		{
			flag = true;
		} else
		{
			flag = false;
		}
	} else
	if (info.continuity > info.str.length() / 2)
	{
		flag = true;
	} else
	{
		flag = false;
	}

	return flag;
}

void SearchExecutor::examRelavence(vector<matchInfo>* list, vector<int>* rank, string key)
{
	vector<matchInfo> newList;
	
	int oldSize = list->size();

	newList.clear();

	for (int i = 0; i < oldSize; i++)
	{
		if (!unrelavent((*list)[i], key))
		{
			newList.push_back((*list)[i]);
		} else
		{
			(*rank)[(*list)[i].index] = 0;
		}
	}

	*list = newList;
}

void SearchExecutor::updateSuggestWords(string* suggestWords, string updWord)
{
	*suggestWords = *suggestWords + updWord + '#';
}

void SearchExecutor::encodeIndex(string* encodedEntry, int index)
{
	char inx[5];
	
	if (index < _generalEntryList->size())
	{
		sprintf(inx, "%d", index);

		string tempInx(inx);
		
		*encodedEntry = "#G" + tempInx + encodedEntry->substr(1);
	} else
	{
		index -= _generalEntryList->size();
				
		sprintf(inx, "%d", index);

		string tempInx(inx);

		*encodedEntry = "#C" + tempInx + encodedEntry->substr(1);
	}
}

//@author A0088455R

/**
* Checks the entry at index "index" for matching date
**/
void SearchExecutor::checkEntryDate(int index, vector<int>* rank, string keyword , int &highestRank)
{
	string toBeCompared;

	int entryDay;
	int keywordDay;
	int entryMonth;
	int keywordMonth;
	int entryYear;
	int keywordYear;

	toBeCompared= extractDate(_combinedEntryList[index]);

		if (toBeCompared == "")
		{
			setRank( index, NO_MATCH, rank, &highestRank);
		}
		else
		{
			entryDay = extractDay(toBeCompared);
			entryMonth = extractMonth(toBeCompared);
			entryYear = extractYear(toBeCompared);
			keywordDay = extractDay(keyword);
			keywordMonth = extractMonth(keyword);
			keywordYear = extractYear(keyword);

			if (entryYear == keywordYear)
			{
				if (entryMonth == keywordMonth)
				{
					if (entryDay == keywordDay)
					{
						setRank( index, PERFECT_MATCH, rank, &highestRank);
						noMatch = false;
					}
					else
					{
						setRank( index, HIGH_MATCH, rank, &highestRank);
						noMatch = false;
					}
				}
				else if (entryDay == keywordDay)
				{
					setRank( index, HIGH_MATCH, rank, &highestRank);
					noMatch = false;
				}
				else
				{
					setRank( index, MEDIOCORE_MATCH, rank, &highestRank);
					noMatch = false;
				}
			}
			else if (entryMonth == keywordMonth)
			{
				if (entryDay == keywordDay)
				{
					setRank( index, HIGH_MATCH, rank, &highestRank);
					noMatch = false;
				}
				else
				{
					setRank( index, MEDIOCORE_MATCH, rank, &highestRank);
					noMatch = false;
				}
			}
			else if (entryDay == keywordDay)
			{
				setRank( index, MEDIOCORE_MATCH, rank, &highestRank);
				noMatch = false;
			}
			else
			{
				//setRank( index, LOW_MATCH, rank, &highestRank);
			}
		}
}

/**
* Iterates through the entry list and searches for a matching date
* The ranks are going to be updated after this method called
**/
void SearchExecutor::searchDate(string keyword, vector<int>* rank)
{	
	assert(keyword!="");

	int i;

	noMatch = true;

	int listSize = _combinedEntryList.size();

	int highestRank=0;


	initializeRank(listSize, rank);

	for (i = 0; i < listSize; i++)
	{
		checkEntryDate(i , rank, keyword , highestRank);
	}
	adjustRank(rank, highestRank);	
}

/**
* Checks the entry at index "index" for matching time, including checking the time intervals
**/
void SearchExecutor::checkEntryTime(int index, vector<int>* rank, string keyword , int &highestRank)
{
	string entryStartTime;
	string entryEndTime;

	int entryStartHour;
	int entryEndHour;
	int entryStartMinute;
	int entryEndMinute;
	int keywordHour;
	int keywordMinute;

	string entryTimeRange = extractTime(_combinedEntryList[index]);

	if (entryTimeRange == "")
	{
		setRank( index, NO_MATCH, rank, &highestRank);
	}
	else
	{
		splitStartEndTime(&entryStartTime, &entryEndTime, entryTimeRange);
		entryStartHour = extractHour(entryStartTime);
		entryEndHour = extractHour(entryEndTime);
		entryStartMinute = extractMinute(entryStartTime);
		entryEndMinute = extractMinute(entryEndTime);
		keywordHour = extractHour(keyword);
		keywordMinute = extractMinute(keyword);
		if (entryStartHour == keywordHour)
		{
			if (entryStartMinute == keywordMinute)
			{
				setRank( index, PERFECT_MATCH, rank, &highestRank);
				noMatch = false;
			}
			else if (entryStartMinute < keywordMinute)
			{
				setRank( index, HIGH_MATCH, rank, &highestRank);
				noMatch = false;
			}
			else
			{
				setRank( index, MEDIOCORE_MATCH, rank, &highestRank);
				noMatch = false;
			}
		}
		else if (entryEndHour == keywordHour)
		{
			if (entryEndMinute == keywordMinute)
			{
				setRank( index, PERFECT_MATCH, rank, &highestRank);
				noMatch = false;
			}
			else if (entryEndMinute < keywordMinute)
			{
				setRank( index, HIGH_MATCH, rank, &highestRank);
				noMatch = false;
			}
			else
			{
				setRank( index, MEDIOCORE_MATCH, rank, &highestRank);
				noMatch = false;
			}
		}
		else if ((entryStartHour < keywordHour) && (entryEndHour > keywordHour))
		{
			setRank( index, MEDIOCORE_MATCH, rank, &highestRank);
			noMatch = false;
		}
		else
		{
			setRank( index, LOW_MATCH, rank, &highestRank);
		}
	}
}

/**
* Iterates through the entry list and searches for a matching time
* The ranks are going to be updated after this method called
**/
void SearchExecutor::searchTime(string keyword, vector<int>* rank)
{
	assert(keyword!="");

	int i;
	int highestRank=0;

	noMatch = true;

	int listSize = _combinedEntryList.size();

	
	initializeRank(listSize, rank);

	for (i=0; i<listSize; i++)
	{
		checkEntryTime(i, rank, keyword, highestRank);
	}
	adjustRank(rank, highestRank);
}

void SearchExecutor::searchText(string key, vector<int>* rank, vector<string>* suggestWords)
{
	int tot = _combinedEntryList.size();
	int tempTreshold = -1;

	vector<matchInfo> best;
	vector<string> tempSuggestWords;
	
	for (int j = 0; j < tot; j++)
	{
		matchInfo temp;
		vector<string> list;

		list.clear();

		splitWords(_combinedEntryList[j], &list);
		
		temp.dis = -1;
		
		for (int k = 0; k < (int)list.size(); k++)
		{
			string curP = list[k];
				
			matchInfo curM(curP);

			edit(key, curP, curM);

			if (temp.dis == -1)
			{
				temp = curM;
			} else
			{
				temp = compare(temp, curM);
			}
		}
		
		temp.index = j;
		best.push_back(temp);
	}

	sort(best.begin(), best.end(), cmp);

	examRelavence(&best, rank, key);

	if (!best.empty())
	{
		noMatch = false;

		int p = 0;
		int q = 1;
		int r = tot;
		int relaventEntrySize = best.size();

		while (p < relaventEntrySize)
		{			
			while (q < relaventEntrySize && !cmp(best[q - 1], best[q])) q++;

			r = tot - p;

			for (; p < q; p++)
			{
				(*rank)[best[p].index] = r;
			}

			q++;
		}

		tempTreshold = r;

		for (int i = 0; i < best.size() && suggestWords->size() < 4; i++)
		{
			if (best[i].match != best[i].str.length() || best[i].match != key.length())
			{
				if (suggestWords->empty())
				{
					suggestWords->push_back(best[i].str);
				} else
				if (best[i].str != suggestWords->back())
				{
					suggestWords->push_back(best[i].str);
				}
			}
		}
	} else
	{
		tempTreshold = 1;
	}

	treshold += tempTreshold;
}

SearchExecutor::SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details)
{
	assert(details!="");
	assert(matchedEntryList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	_undoEnable = false;

	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;
	_matchedEntryList = matchedEntryList;

	treshold = 0;

	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
	_undoMatchedEntryList = *matchedEntryList;
}

void SearchExecutor::execute() throw (string)
{
	vector<int> rank;
	vector<int> score;

	vector<string> suggestWords;
	
	string encodedSuggestWords = "#";

	vector<integerPair> tempMatchedList;

	int weight;
	int suggestWordsCnt = 1;
	
	string key = extractDescription(_details);
	string currentKey;

	updateSuggestWords(&encodedSuggestWords, key);
	
	initializeCombinedEntry();
	
	int totalEntries = _combinedEntryList.size();

	initializeVectors(totalEntries,&score,&rank);
	
	//while we can still extract keywords from the input
	while (!key.empty())
	{
		currentKey = splitFirstTerm(&key);
		weight = 1;
		
		if (isDate(currentKey))
		{
			if (isLogicDate(currentKey))
			{
				searchDate(currentKey, &rank);
				treshold += rank.size();
			} else
			{
				log.writeException("date error");
				throw string ("date error\n");
			}
		} else
		if (isTime(currentKey))
		{
			if (isLogicTime(currentKey))
			{
				searchTime(currentKey, &rank);
				treshold += rank.size();
			} else
			{
				log.writeException("time error");
				throw string ("time error\n");
			}
		} else
		{
			searchText(currentKey, &rank, &suggestWords);
		}

		//if there is no match, weight will be zero, i.e. this key is omitted
		weight = (int) !noMatch;
		
		for (int i = 0; i < totalEntries; i++)
		{
			score[i] += rank[i] * weight;
		}
	}

	for (int i = 0; i < totalEntries; i++)
	{
		if (score[i] < treshold) continue;
		tempMatchedList.push_back(integerPair(score[i], i));
	}

	if (tempMatchedList.empty())
	{
		log.writeException("No Match Found");
		throw string("No Match Found\n");
	} else
	{
		sort(tempMatchedList.rbegin(), tempMatchedList.rend());

		for (int i = 0; i < tempMatchedList.size(); i++)
		{
			int curRecord = tempMatchedList[i].second;
			string curEncodedEntry = _combinedEntryList[curRecord];

			encodeIndex(&curEncodedEntry, curRecord + 1);
		
			_matchedEntryList->push_back(curEncodedEntry);
			log.writeData("record", _matchedEntryList->back());
		}
		
		for (int i = 0; i < suggestWords.size(); i++)
		{
			updateSuggestWords(&encodedSuggestWords, suggestWords[i]);
		}

		_matchedEntryList->push_back(encodedSuggestWords);
		log.writeData("record", _matchedEntryList->back());
	}
}

void SearchExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
	*_matchedEntryList = _undoMatchedEntryList;
}