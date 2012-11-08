#include<cassert>

#include "SearchExecutor.h"

//@author A0088455R
const int SearchExecutor::MONTH[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const int SearchExecutor::PERFECT_MATCH = 3;
const int SearchExecutor::MEDIOCORE_MATCH = 1;

string SearchExecutor::splitFirstTerm(string* mString)
{
	stringstream tempHolder;
	string firstTerm;
	char spaceEater;
	tempHolder<<*mString;
	tempHolder>>firstTerm;
	(*mString).erase(0,firstTerm.size()+1);
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
//@author A0088455R
int SearchExecutor::extractDay(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return day;
}

int SearchExecutor::extractMonth(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return month;
}

int SearchExecutor::extractYear(string date)
{
	int year, month, day;
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	return year;
}

int SearchExecutor::extractHour(string time)
{
	int hour, minute;
	sscanf(time.c_str(), "%d:%d", &hour, &minute);
	return hour;
}

int SearchExecutor::extractMinute(string time)
{
	int hour, minute;
	sscanf(time.c_str(), "%d:%d", &hour, &minute);
	return minute;
}

void SearchExecutor::splitStartEndTime(string* start, string* end, string timeRange)
{
	*start=timeRange.substr(0,5);
	*end=timeRange.substr(6,5);
}

void SearchExecutor::initializeVectors(int totalSize, vector<int>* score, vector<int>* rank)
{
	score->clear();
	rank->clear();
	score->assign(totalSize,NULL);
	rank->assign(totalSize,NULL);
}

void SearchExecutor::initializeRank(int totalSize, vector<int>* rank)
{
	rank->clear();
	rank->assign(totalSize,totalSize);
}

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

void SearchExecutor::setRank(int index, int level, vector<int>* rank, int* currentHighest)
{
	(*rank)[index]-= level;
	if( *currentHighest < (*rank)[index])
	{
		*currentHighest = (*rank)[index];
	}
	if ( (*rank)[index]<0)
	{
		(*rank)[index] = 0;
	}
}

void SearchExecutor::adjustRank(vector<int>* rank, int currentHighest)
{
	int listSize = _combinedEntryList.size();
	int i;
	if ( currentHighest > 1 )
	{
		for (i = 0; i < listSize; i++)
		{
			(*rank)[i] += ( listSize-currentHighest  );
		}
	}	
}

void SearchExecutor::splitWords(string encoded, vector<string>* list)
{
	string sentence = extractDescription(encoded);
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
	if (a.match > b.match) return true; else
	if (a.match < b.match) return false; else
	if (a.continuity < b.continuity) return true; else
	if (a.continuity > b.continuity) return false; else
	if (a.ms < b.ms) return true; else
	if (a.ms > b.ms) return false; else
	if (a.change < b.change) return true; else
	if (a.change > b.change) return false;

	return false;
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

void SearchExecutor::searchDate(string keyword, vector<int>* rank)
{	
	assert(keyword!="");
	int i;

	noMatch = true;
	string toBeCompared;

	int listSize = _combinedEntryList.size();

	int highestRank=0;
	int entryDay;
	int keywordDay;
	int entryMonth;
	int keywordMonth;
	int entryYear;
	int keywordYear;

	initializeRank(listSize, rank);

	for (i = 0; i < listSize; i++)
	{
		toBeCompared= extractDate(_combinedEntryList[i]);

		if (toBeCompared == "")
		{
			setRank( i, 4, rank, &highestRank);
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
						setRank( i, 0, rank, &highestRank);
						noMatch = false;
					}
					else
					{
						setRank( i, 1, rank, &highestRank);
						noMatch = false;
					}
				}
				else if (entryDay == keywordDay)
				{
					setRank( i, 1, rank, &highestRank);
					noMatch = false;
				}
				else
				{
					setRank( i, 2, rank, &highestRank);
					noMatch = false;
				}
			}
			else if (entryMonth == keywordMonth)
			{
				if (entryDay == keywordDay)
				{
					setRank( i, 1, rank, &highestRank);
					noMatch = false;
				}
				else
				{
					setRank( i, 2, rank, &highestRank);
					noMatch = false;
				}
			}
			else if (entryDay == keywordDay)
			{
				setRank( i, 2, rank, &highestRank);
				noMatch = false;
			}
			else
			{
				setRank( i, 3, rank, &highestRank);
			}
		}
	}
	adjustRank(rank, highestRank);	
}

void SearchExecutor::searchTime(string keyword, vector<int>* rank)
{
	assert(keyword!="");

	int i;
	int highestRank=0;

	noMatch = true;

	string entryTimeRange;
	string entryStartTime;
	string entryEndTime;

	int entryStartHour;
	int entryEndHour;
	int entryStartMinute;
	int entryEndMinute;
	int keywordHour;
	int keywordMinute;

	int listSize = _combinedEntryList.size();

	
	initializeRank(listSize, rank);

	for (i=0; i<listSize; i++)
	{
		entryTimeRange=extractTime(_combinedEntryList[i]);
		if (entryTimeRange == "")
		{
			setRank( i, 4, rank, &highestRank);
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
					setRank( i, 0, rank, &highestRank);
					noMatch = false;
				}
				else if (entryStartMinute < keywordMinute)
				{
					setRank( i, 1, rank, &highestRank);
					noMatch = false;
				}
				else
				{
					setRank( i, 2, rank, &highestRank);
					noMatch = false;
				}
			}
			else if (entryEndHour == keywordHour)
			{
				if (entryEndMinute == keywordMinute)
				{
					setRank( i, 0, rank, &highestRank);
					noMatch = false;
				}
				else if (entryEndMinute < keywordMinute)
				{
					setRank( i, 1, rank, &highestRank);
					noMatch = false;
				}
				else
				{
					setRank( i, 2, rank, &highestRank);
					noMatch = false;
				}
			}
			else if ((entryStartHour < keywordHour) && (entryEndHour > keywordHour))
			{
				setRank( i,2, rank, &highestRank);
				noMatch = false;
			}
			else
			{
				setRank( i, 3, rank, &highestRank);
			}
		}
	}
	adjustRank(rank, highestRank);
}

void SearchExecutor::searchText(string key, vector<int>* rank)
{
	int tot = _combinedEntryList.size();
	vector<matchInfo> best;
	
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
				
			matchInfo curM;

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
		
	int p = 0;
	int q = 1;

	while (p < tot)
	{
		while (q < tot && !cmp(best[q - 1], best[q])) q++;

		for (int r = tot - p; p < q; p++)
		{
			(*rank)[best[p].index] = r;
		}

		q++;
	}
}

SearchExecutor::SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details)
{
	assert(details!="");
	assert(matchedEntryList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_details = details;
	_matchedEntryList = matchedEntryList;

	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
	_undoMatchedEntryList = *matchedEntryList;
}

void SearchExecutor::execute()
{
	string currentKey;
	vector<int> rank;
	vector<int> score;
	
	int weight = 1;
	initializeCombinedEntry();
	
	int totalEntries = _combinedEntryList.size();

	initializeVectors(totalEntries,&score,&rank);
	
	//while we can still extract keywords from the input
	while (!_details.empty())
	{
		currentKey = splitFirstTerm(&_details);
		
		if (isDate(currentKey))
		{
			if (isLogicDate(currentKey))
			{
				searchDate(currentKey, &rank);
			} else
			{
				throw string ("date error\n");
				//log.writeException("date error");
			}
		} else
		if (isTime(currentKey))
		{
			if (isLogicTime(currentKey))
			{
				searchTime(currentKey, &rank);
			} else
			{
				throw string ("time error\n");
				log.writeException("time error");
			}
		} else
		{
			searchText(currentKey, &rank);
		}
		
		for (int i = 0; i < totalEntries; i++)
		{
			score[i] += rank[i] * weight;
		}
	}

	vector<pair<int, int>> v;

	for (int i = 0; i < totalEntries; i++)
	{
		v.push_back(make_pair(score[i], i));
	}

	sort(v.rbegin(), v.rend());
	
	for (int i = 0; i < totalEntries; i++)
	{
		int curRecord = v[i].second;
		
		_matchedEntryList->push_back(_combinedEntryList[curRecord]);
	}
}

void SearchExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
	*_matchedEntryList = _undoMatchedEntryList;
}