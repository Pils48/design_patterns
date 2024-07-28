#include <iostream>
#include <string>
#include <memory>

// Subsystems (Order, Payment, Inventory, Shipping) remain the same

class Order {
public:
    void createOrder(const std::string& item, int quantity) {
        std::cout << "Order created for " << quantity << " " << item << "(s)" << std::endl;
    }
    void cancelOrder(const std::string& item, int quantity) {
        std::cout << "Order cancelled for " << quantity << " " << item << "(s)" << std::endl;
    }
};

class Payment {
public:
    void processPayment(const std::string& item, int quantity, double price) {
        std::cout << "Processed payment for " << quantity << " " << item << "(s) costing " << price << std::endl;
    }
    void refundPayment(const std::string& item, int quantity, double price) {
        std::cout << "Refunded payment for " << quantity << " " << item << "(s) costing " << price << std::endl;
    }
};

class Inventory {
public:
    void updateStock(const std::string& item, int quantity) {
        std::cout << "Updated stock for " << quantity << " " << item << "(s)" << std::endl;
    }
    void checkStock(const std::string& item) {
        std::cout << "Checked stock for " << item << std::endl;
    }
};

class Shipping {
public:
    void arrangeShipping(const std::string& item, int quantity) {
        std::cout << "Arranged shipping for " << quantity << " " << item << "(s)" << std::endl;
    }
    void cancelShipping(const std::string& item, int quantity) {
        std::cout << "Cancelled shipping for " << quantity << " " << item << "(s)" << std::endl;
    }
};

// Facade class
class OnlineShoppingFacade {
public:
    OnlineShoppingFacade() 
        : order(std::make_shared<Order>()), 
          payment(std::make_shared<Payment>()), 
          inventory(std::make_shared<Inventory>()), 
          shipping(std::make_shared<Shipping>()) {}

    void placeOrder(const std::string& item, int quantity, double price) {
        // So we just call proper sequence of method calls right from this class
        // Client should not think about the order they are just placing an order here
        // Essentially works like functions in procedural programming
        order->createOrder(item, quantity);
        payment->processPayment(item, quantity, price);
        inventory->updateStock(item, -quantity);
        shipping->arrangeShipping(item, quantity);
    }

    void cancelOrder(const std::string& item, int quantity, double price) {
        order->cancelOrder(item, quantity);
        payment->refundPayment(item, quantity, price);
        inventory->updateStock(item, quantity);
        shipping->cancelShipping(item, quantity);
    }

private:
    std::shared_ptr<Order> order;
    std::shared_ptr<Payment> payment;
    std::shared_ptr<Inventory> inventory;
    std::shared_ptr<Shipping> shipping;
};

// Client code
int main() {
    OnlineShoppingFacade shoppingFacade;

    std::string item = "Laptop";
    int quantity = 1;
    double price = 1000.0;

    // Placing an order using the facade
    shoppingFacade.placeOrder(item, quantity, price);

    std::cout << std::endl;

    // Cancelling an order using the facade
    shoppingFacade.cancelOrder(item, quantity, price);

    return 0;
}
