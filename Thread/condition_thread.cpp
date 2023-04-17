#include <thread>
#include <mutex>

#include <condition_variable>
#include <iostream>

#include <vector>
#include <queue>
#include <atomic>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data;

void producer() {
    std::cout << "Producer: starting production..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    {
        std::lock_guard<std::mutex> lock(mtx);
        data.push(100);
        std::cout << "Producer: data produced" << std::endl;
    }
    cv.notify_one();
}

void consumer() {
    std::cout << "Consumer: waiting for data..." << std::endl;

    {
        std::unique_lock<std::mutex> lock(mtx);
        if (cv.wait_for(lock, std::chrono::milliseconds(3500), [] { return !data.empty(); }))
        {
            /*
            * Если за это время очередь data не перестанет быть пустой,
              то cv.wait_for вернет false. Если же очередь data станет 
              непустой до истечения заданного периода времени, то cv.wait_for вернет true.
            */
            std::cout << "Consumer: data received " << data.front() << std::endl;
            data.pop(); 
        }
        else
        {
            std::cout << "Consumer: timeout reached, no data received!" << std::endl;
        }
       
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
