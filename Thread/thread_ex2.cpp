#include <iostream>
#include <thread>

#include <mutex>
//#include <memory>

//#include <vector>
//#include <queue>
#include <condition_variable>
#include <fstream>
#include <string>
using namespace std; // bad practice but now, for us it's OK!




mutex mtx;
condition_variable cv;

bool _var = false;
bool ret() { return _var; }



void foo()
{
	ofstream log;
	string str;
	static int numFoo = 0;
	
	while (true)
	{
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, ret);
		// or
		// cv.wait(lock, [&]() { return _var; });
		
		/*
		* @brief: блокируется поток до тех пор,пока
		* cv не получит _var как true. если получил _var = true,
		* поток разблокируется (mtx.unlock()) и выполниться код ниже!
		*/
		
		log.open("C:/Users/qumar/Desktop/logcpp.txt", ios::app);
			str = "Is Foo: " + to_string(++numFoo) + '\n';
			log.write(str.c_str(), str.length());
		log.close();
		
	}

}


void bar()
{
	while (true)
	{
		char input;
		cout << "Input: "; cin >> input;
		cin.clear();
		if (input == 'y')
		{
			_var = true;
			cv.notify_one();
		}
		
		if (input == 'n')
		{
			/*
			* @: когда пользователь введет n, то флаг станет "false (0)",
			* тоесть, это означает то,что наш поток замерзнет, до тех пор пока не получит "true (1)",
			* но когда пользователь после этого захочет отправить 'y', мы перекидываем флаг в состояние "true (1)",
			* и для того,что бы разбудить поток,мы должны отправить ему сигнал (cv.notify_one), который значит что
			* наш флаг уже "true (1)" и мы можем работать с кодом! 
			* 
			*/
			_var = false;	
		}
	}
}




int main()
{
	thread th(bar);
	thread th2(foo);

	th.join();
	th2.join();
	return 0;
} 
