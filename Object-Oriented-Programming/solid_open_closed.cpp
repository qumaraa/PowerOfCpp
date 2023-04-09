//   SOLID principes in C++
//   Open/Closed

#include <iostream>
#include <string>
#include <vector>

// Abstract class for payment
class Payment {
public:
    virtual void pay(float amount) = 0;
};

// Implementation of payment via PayPal
class PayPalPayment : public Payment {
public:
    void pay(float amount) override {
        std::cout << "Paid " << amount << " via PayPal" << std::endl;
    }
};

// Implementation of payment via bank

class CreditCardPayment : public Payment {
public:
    
    void pay(float amount) override {
        std::cout << "Paid " << amount << " via bank card." << std::endl;
    }
};

// Order class

class Order {
public:
    Order(float amount, Payment* paymentMethod) :
        m_amount(amount), m_paymentMethod(paymentMethod) {}

    void process() {
        m_paymentMethod->pay(m_amount);
    }

private:
    float m_amount;
    Payment* m_paymentMethod;
};


// App Class
class App {
public:
    void run() {
        std::vector<Order> orders = {
          Order(100, new PayPalPayment()),
          Order(200, new CreditCardPayment())
        };

        for (auto& order : orders) {
            order.process();
        }
    }
};

int main() {
    App app;
   
    app.run();

    return 0;
}
