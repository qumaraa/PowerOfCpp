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


int findDuplicates(vector<int>& vec)
{
	unordered_map<int, int> countMap;
	/* countMap <int, int>  -> 
		1) * ключ 
		2) * в нашем случае,количество вхождений элемента */
	
	int duplicates = 0;
	for (int v : vec)
	{
		if (++countMap[v] == 2)
		{
			++duplicates;
		}
	}
	return duplicates;
}



int main()
{
	vector<int> v{ 1,1,2,2,4,4,5,5,7,7,8,8,9,9,100 };
	
	cout << findDuplicates(v);


	cout << "this_thread: " << this_thread::get_id() << endl;
	system("pause");
}
 
