#include <iostream> 
#include <memory>
#include <vector>

class Payment {
public:
	virtual ~Payment() = default;
	virtual void pay(float amount) const noexcept = 0;
};

class CreditCardPayment : public Payment {
public:
	void pay(float amount) const noexcept override {
		std::cout << "Paid " << amount << "$ via credit card" << std::endl;
	}
};
 
class PayPalPayment : public Payment {
public:
	void pay(float amount) const noexcept override {
		std::cout << "Paid " << amount << "$ via PayPal" << std::endl;
	}
};

class Order {
public:
	Order(float amount_, std::unique_ptr<Payment> payment) :
		amount(amount_), m_payment_t(std::move(payment)) {}

	void process() const {
		m_payment_t->pay(amount);
	}

private:
	float amount;
	std::unique_ptr<Payment> m_payment_t;
};

class User {
public:
	User() : orders{}, balance(0) {}

	void pay_via_credit_card(float amount) {
		if (balance > amount) {
			orders.emplace_back(amount, std::make_unique<CreditCardPayment>());
			balance -= amount;
		}
		else { throw std::exception("Insufficient funds"); }
	}
	void pay_via_paypal(float amount)
	{
		if (balance > amount) {
			orders.emplace_back(amount, std::make_unique<PayPalPayment>());
			balance -= amount;
		}else { throw std::exception("Insufficient funds"); }
	}

	void addBalance(float amount_)
	{
		balance += amount_;
	}
	int getBalance() { return static_cast<int>(balance); } 

	void showOrders() const {
		for (const auto& order : orders) {
			
			order.process();
		}
	}
private:
	std::vector<Order> orders;
	float balance;
};

  


int main() {
	
	try {
		User s;
		s.addBalance(1000000);
		std::cout << "Balance: " << s.getBalance() << std::endl;
		s.pay_via_credit_card(100);
		s.pay_via_paypal(200);
		
		s.showOrders();
		std::cout << std::endl;
		std::cout << "Balance: " << s.getBalance() << std::endl;

	}
	catch (std::exception& ex)
	{
		std::cout << std::endl << "Exception: " << ex.what() << std::endl;
	}
}
