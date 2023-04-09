#include <iostream>
 

/* * @file: singleton_pattern.cpp
* @brief: here is shown Simple Singleton pattern

* @developer: @ynwqmv
* @license: GNU General Public License 2.0
*/



class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;  
        return instance;  
    }

    void doSomething() {
        std::cout << "doing something...";
    }
    
private:
    Singleton() {}  
    ~Singleton() {}  
    Singleton(const Singleton&) = delete;  
    Singleton& operator=(const Singleton&) = delete;  

};


int main() {
    
    Singleton& instance = Singleton::getInstance();
    instance.doSomething();
    return 0;
} 
