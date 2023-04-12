#include <iostream>
#include <algorithm>

#include <fstream>
using namespace std;

 

class FileSystem
{
public:
	void write(const string& file_name, string message)
	{
		ofstream file(file_name, ios::app);
		if (file.is_open())
		{
			file << message << endl;
			file.close();
		}else throw std::runtime_error("Couldn't write data to file");
		 
	}
	void read(const string& file_name, string& out_text)
	{
		ifstream file(file_name);
		if (file.is_open())
		{
			while (file >> out_text)
				cout << out_text << endl;
		}else throw std::runtime_error("Couldn't read data from file");
		file.close();
	}

	
	
	void remove(const string& file)
	{
		if (std::remove(file.c_str()) != 0)
			cout << "File " << file << " : couldn't delete\n";
		else
			cout << "File " << file << " has been deleted successfully!\n";
	}
};

using fs = FileSystem;

int main() 
{
	
	fs f;
	const string path = "path/to/file";
	f.write(path, "Hello,World!");
	
	std::string temp = "";
	f.read(path, temp);
	
	f.remove(path);
	
	 
}
