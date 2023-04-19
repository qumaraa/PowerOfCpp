#include <iostream>
#include <functional>

#include <thread>
#include <future>

#include <chrono>
#include <mutex>
using namespace std;


int add(int a, int b) { return a + b; }


int main() {
	// Создаем promise, чтобы в будущем положить в него результат выполнения функции
	promise<int> p;

	// Получаем future, чтобы в дальнейшем получить результат выполнения функции
	future<int> f = p.get_future();
	thread t([&p]()
		{
			p.set_value(add(2, 3));
		});
	// Ждем, пока функция выполнится в другом потоке
    
	// и результат будет положен в promise
	f.wait();
	cout << "Result: " << f.get() << endl;

	t.join();
}
 
