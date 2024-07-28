#include <iostream>
#include <string>


/**
 * Complexity: The client code is responsible for managing interactions with multiple subsystems, making it complex and difficult to maintain. 
 * We need to hide secrets instead
 * Tight Coupling: The client code is tightly coupled with the subsystems, making it hard to change the subsystems without affecting the client.
 * Code Duplication: If similar sequences of interactions are needed elsewhere, the code would have to be duplicated.
 */

// Order system
class Order {
public:
    void createOrder(const std::string& item, int quantity) {
        std::cout << "Order created for " << quantity << " " << item << "(s)" << std::endl;
    }
    void cancelOrder(const std::string& item, int quantity) {
        std::cout << "Order cancelled for " << quantity << " " << item << "(s)" << std::endl;
    }
};

// Payment system
class Payment {
public:
    void processPayment(const std::string& item, int quantity, double price) {
        std::cout << "Processed payment for " << quantity << " " << item << "(s) costing " << price << std::endl;
    }
    void refundPayment(const std::string& item, int quantity, double price) {
        std::cout << "Refunded payment for " << quantity << " " << item << "(s) costing " << price << std::endl;
    }
};

// Inventory system
class Inventory {
public:
    void updateStock(const std::string& item, int quantity) {
        std::cout << "Updated stock for " << quantity << " " << item << "(s)" << std::endl;
    }
    void checkStock(const std::string& item) {
        std::cout << "Checked stock for " << item << std::endl;
    }
};

// Shipping system
class Shipping {
public:
    void arrangeShipping(const std::string& item, int quantity) {
        std::cout << "Arranged shipping for " << quantity << " " << item << "(s)" << std::endl;
    }
    void cancelShipping(const std::string& item, int quantity) {
        std::cout << "Cancelled shipping for " << quantity << " " << item << "(s)" << std::endl;
    }
};

// Client code
int main() {
    Order order;
    Payment payment;
    Inventory inventory;
    Shipping shipping;

    std::string item = "Laptop";
    int quantity = 1;
    double price = 1000.0;

    // Placing an order
    order.createOrder(item, quantity);
    payment.processPayment(item, quantity, price);
    inventory.updateStock(item, quantity);
    shipping.arrangeShipping(item, quantity);

    // Cancelling an order
    order.cancelOrder(item, quantity);
    payment.refundPayment(item, quantity, price);
    inventory.updateStock(item, -quantity);
    shipping.cancelShipping(item, quantity);

    return 0;
}
