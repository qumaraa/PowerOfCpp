#include <iostream>
#include <vector>

 


class IObserver {
public:
    virtual void Update() = 0;
};

 

class ConcreteObserver : public IObserver {
public:
    void Update() {
        std::cout << "ConcreteObserver is notified!" << std::endl;
    }
};
 
class IObservable {
public:
    
    virtual void AddObserver(IObserver* observer) = 0;
    virtual void RemoveObserver(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

 
class ConcreteObservable : public IObservable {
public:
    void AddObserver(IObserver* observer) {
        m_observers.push_back(observer);
    }

    void RemoveObserver(IObserver* observer) {
        for (auto it = m_observers.begin(); it != m_observers.end(); ++it) {
            if (*it == observer) {
                m_observers.erase(it);
                break;
            }
        }
    }

    void Notify() {
        for (auto observer : m_observers) {
            observer->Update();
        }
    }

private:
    std::vector<IObserver*> m_observers;
};

// Тестирование
int main() {
    ConcreteObserver observer1;
    ConcreteObserver observer2;

    ConcreteObservable observable;
    observable.AddObserver(&observer1);
    observable.AddObserver(&observer2);

    observable.Notify();
    observable.RemoveObserver(&observer1);

    observable.Notify();

    return 0;
}
