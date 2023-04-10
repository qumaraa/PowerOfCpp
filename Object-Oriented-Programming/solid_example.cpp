#include <iostream>
#include <chrono>

#include <thread>


/* * @file: solid_example.cpp
* @brief: here is shown one example of SOLID 

* @developer: @ynwqmv
* @license: GNU General Public License 2.0
*/

class Engine {
public:
    Engine() = default;
    
    
    void start() {
        std::cout << "Starting engine...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // simulation
        std::cout << "Engine started!\n";
    }
    void stop() {
        std::cout << "Engine off!\n";
    }
};
class Car {

private:
    Engine engine;
public:
    void start() {
        engine.start();
    }
    void stop() {
        engine.stop();
    }
};
 
int main() {

    Car car;
    car.start();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    car.stop();
    return 0;
} 
