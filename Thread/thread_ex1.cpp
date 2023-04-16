#include <iostream>
#include <fstream>

#include <algorithm>
#include <vector>

#include <unordered_map>
#include <thread>
#include <mutex>
#include <fstream>
#include <qcc/windows/mapping.h>
#include <string>

#define TH1_STARTED_FEXPORT   cout << "th1:\t\twork started\t\tfexport()\n";
#define TH1_FINISHED_FEXPORT  cout << "th1:\t\twork finished\t\tfexport()\n";

#define TH2_STARTED_FIMPORT	  cout << "th2:\t\twork started\t\tfimport()\n";
#define TH2_FINISHED_FIMPORT  cout << "th2:\t\twork finished\t\tfimport()\n";

#define T1_STARTED_FEXPORT    cout << "t1:\t\twork started\t\tfexport()()\n";
#define T1_FINISHED_FEXPORT   cout << "t1:\t\twork started\t\tfexport()()\n";


#define T2_STARTED_FIMPORT	  cout << "t2:\t\twork started\t\tfimport()()\n";
#define T2_FINISHED_FIMPORT	  cout << "t2:\t\twork started\t\tfimport()()\n";

 
using namespace std;
class Bank
{
public:
	Bank(const string userID, int balance)
	{
		this->useridx = userID;
		this->balancex = balance;
		customerx[userID] = balancex;
	}
	int balance() const noexcept { return balancex; }
	string userid() const noexcept { return useridx; }
	void print() const noexcept
	{
		for (auto& i : customerx)
		{
			cout << "User : " << i.first << "\nBalance : " << i.second << "$" << endl;
		}
	}

private:
	string useridx;

	int balancex;
	unordered_map<string, int> customerx;

};
mutex mtx;

class IEManager
{
	Bank bankTemp;
	string fileName;
	;
public:
	IEManager(const Bank& bank, const string _toFile)
		: bankTemp(bank), fileName(_toFile)
	{
	}

	void fexport() const noexcept
	{
		mtx.lock();
		cout << "Thread ID: " << this_thread::get_id() << endl;
		ofstream f(fileName, ios::app);
		if (f.is_open())
		{
			cout << "Exporting data ... Wait" << endl;
			f << endl << "User: " << bankTemp.userid()
				<< "\nBalance: " << bankTemp.balance() << endl;
			cout << "Exported data successfully in " << fileName << endl;

			f.close();
		}
		else cerr << "Failed to open file for writing data from Bank!";

		mtx.unlock();
	}
	void fimport(string& toStr) const noexcept
	{
		mtx.lock();
		cout << "Thread ID: " << this_thread::get_id() << endl;
		ifstream f(fileName);

		/* do not use `return` here because we do not unlock mutex here (UB)*/
		if (!f)
		{
			cerr << "Failed to open file!" << endl;
		}
		cout << endl;
		while (getline(f, toStr))
		{
			cout << "Imported: " << toStr << endl;
		}
		f.close();
		mtx.unlock();
	}


};



int main()
{
	Bank user1("Alice", 50);
	cout << user1.balance() << endl << user1.userid() << endl << endl;
	user1.print();


	IEManager manager(user1, "C:/Users/qumar/Desktop/bank_data_tmp.txt");
	string import_tmp = "";

	TH1_STARTED_FEXPORT
		thread th1(&IEManager::fexport, &manager);
	TH1_FINISHED_FEXPORT
		TH2_STARTED_FIMPORT
		thread th2(&IEManager::fimport, &manager, ref(import_tmp));
	TH2_FINISHED_FIMPORT

		IEManager manager2(user1, "C:/Users/qumar/Desktop/bank_data_tmp.txt");
	string import_tmp2 = "";

	T1_STARTED_FEXPORT
		thread t1(&IEManager::fexport, &manager2);

	T1_FINISHED_FEXPORT
		T2_STARTED_FIMPORT
		thread t2(&IEManager::fimport, &manager2, ref(import_tmp2));
	T2_FINISHED_FIMPORT
		t1.join();
	t2.join();

	th1.join();
	th2.join();
}
