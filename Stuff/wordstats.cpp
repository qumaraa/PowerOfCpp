/*
*
* 
-------------------------------
	  # CHAT-GPT TASK (lol)
-------------------------------
@about:
	 * chatgpt gave me this task so
	 * i decided to implement it :D
	 * here i adding multithreading
	 * and fstream. maybe it will be
	 * interesting. the task is simple (just for fun)
	 * 
	 * ...
@else: 
	
	NO WARRANTY
@author: https://github.com/xqmvio - GitHub
		 qmvscorpio@gmail.com      - Mail (for questions)
@file: wordstats.cpp
*/

#include <iostream>
#include <functional>

#include <thread>
#include <future>

#include <chrono>
#include <mutex>
#include <vector>

#include <queue>
#include <algorithm>

#include <unordered_map>

using namespace std;


class WordStats
{
public:
	/* constructor with non-const ref. of vector*/
	WordStats(vector<string>& vec);
	/* classmethod for counting words in vector */
	void countWords();
	/* getter */
	int getWordCount(const std::string& word) const;
	/* pair to return 2 values */
	pair<string,int> getMostFrequentWord();

private:
	vector<string> temp_vec;
	unordered_map<string, int> counterMap;
};

/*
	@param: [main]
*/
int main()
{ 
	vector<string> vec{ "banana", "apple", "thread", "thread", "thread","thread","thread"};
	WordStats d(vec);
	cout << "1)`thread` counts in map : " << d.getWordCount("thread") << " times!" << endl;

	d.countWords();
	cout << "2)`thread` counts in map : " << d.getWordCount("thread") << " times!" << endl;
	cout << "`apple` counts in map : " << d.getWordCount("apple") << " times!" << endl;
	cout << "frequent word: ";
	auto val = d.getMostFrequentWord();
	
	cout << val.first << " " << val.second << endl;
	 
}
WordStats::WordStats(vector<string>& vec)
{	
	if (!vec.empty()) {
		this->temp_vec = vec;
		sort(temp_vec.begin(), temp_vec.end()); // sort the vector of strings
	}
}
/*
* @param: [classmethod]
* @brief: adds each element to the map
*/
void WordStats::countWords()
{
	for (const auto& i : temp_vec)
		++counterMap[i];
}
/*
* @param: [classmethod]
* @brief: getting the count number
          of the string from the arg.
*/
int WordStats::getWordCount(const std::string& word) const
{
	auto it = counterMap.find(word);
	if (it != counterMap.end())
	{
		return it->second;
	}
	else return -1;
}

/*
* @param: [classmethod]
* @brief: we use pair to return the string that 
          repeats most often, along with its value!
*/
pair<string, int> WordStats::getMostFrequentWord()
{	
	int local = 0;
	string str_local = "";
	for (auto i : counterMap)
	{
		if (i.second > local)
		{
			str_local = i.first;
			local = i.second;
		}
	}
	return make_pair(str_local, local);
}
