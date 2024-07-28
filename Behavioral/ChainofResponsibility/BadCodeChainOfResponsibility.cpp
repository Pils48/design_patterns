#include <iostream>
#include <string>

/**
 * Hard-Coded Logic: The logic to handle tickets at different levels is hard-coded within the SupportStaff class, 
 * making it difficult to add new levels of support or change existing ones.
 * Single Responsibility Principle Violation: The SupportStaff class has multiple responsibilities: 
 * determining the difficulty level of the ticket and handling it accordingly.
 * Scalability Issues: If more levels of support or different handling mechanisms are needed, 
 * the SupportStaff class will become increasingly complex and harder to maintain.
 */

// Support Ticket class
class SupportTicket {
public:
    SupportTicket(const std::string& description, int difficultyLevel)
        : description(description), difficultyLevel(difficultyLevel) {}

    int getDifficultyLevel() const {
        return difficultyLevel;
    }

    const std::string& getDescription() const {
        return description;
    }

private:
    std::string description;
    int difficultyLevel;
};

// Support Staff class
class SupportStaff {
public:
    SupportStaff(const std::string& name) : name(name) {}

    void handleTicket(const SupportTicket& ticket) {
        if (ticket.getDifficultyLevel() <= 1) {
            handleLevel1(ticket);
        } else if (ticket.getDifficultyLevel() <= 2) {
            handleLevel2(ticket);
        } else {
            handleLevel3(ticket);
        }
    }

private:
    std::string name;

    void handleLevel1(const SupportTicket& ticket) {
        std::cout << name << " (Level 1): Handling ticket - " << ticket.getDescription() << std::endl;
    }

    void handleLevel2(const SupportTicket& ticket) {
        std::cout << name << " (Level 2): Handling ticket - " << ticket.getDescription() << std::endl;
    }

    void handleLevel3(const SupportTicket& ticket) {
        std::cout << name << " (Level 3): Handling ticket - " << ticket.getDescription() << std::endl;
    }
};

// Client code
int main() {
    SupportTicket ticket1("Cannot connect to the internet", 1);
    SupportTicket ticket2("Computer is slow", 2);
    SupportTicket ticket3("System crash on startup", 3);

    SupportStaff supportStaff("Alice");

    supportStaff.handleTicket(ticket1);
    supportStaff.handleTicket(ticket2);
    supportStaff.handleTicket(ticket3);

    return 0;
}
