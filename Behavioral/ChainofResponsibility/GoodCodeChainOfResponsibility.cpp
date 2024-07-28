#include <iostream>
#include <string>
#include <memory>

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

// Abstract Handler class
class SupportHandler {
public:
    virtual ~SupportHandler() = default;

    void setNextHandler(std::shared_ptr<SupportHandler> next) {
        nextHandler = next;
    }

    void handleTicket(const SupportTicket& ticket) {
        if (canHandle(ticket)) {
            processTicket(ticket);
        } else if (nextHandler) {
            nextHandler->handleTicket(ticket);
        } else {
            std::cout << "No handler available for ticket: " << ticket.getDescription() << std::endl;
        }
    }

protected:
    virtual bool canHandle(const SupportTicket& ticket) const = 0;
    virtual void processTicket(const SupportTicket& ticket) const = 0;

private:
    std::shared_ptr<SupportHandler> nextHandler;
};

// Concrete Handlers
class Level1Support : public SupportHandler {
protected:
    bool canHandle(const SupportTicket& ticket) const override {
        return ticket.getDifficultyLevel() <= 1;
    }

    void processTicket(const SupportTicket& ticket) const override {
        std::cout << "Level 1 Support: Handling ticket - " << ticket.getDescription() << std::endl;
    }
};

class Level2Support : public SupportHandler {
protected:
    bool canHandle(const SupportTicket& ticket) const override {
        return ticket.getDifficultyLevel() <= 2;
    }

    void processTicket(const SupportTicket& ticket) const override {
        std::cout << "Level 2 Support: Handling ticket - " << ticket.getDescription() << std::endl;
    }
};

class Level3Support : public SupportHandler {
protected:
    bool canHandle(const SupportTicket& ticket) const override {
        return ticket.getDifficultyLevel() <= 3;
    }

    void processTicket(const SupportTicket& ticket) const override {
        std::cout << "Level 3 Support: Handling ticket - " << ticket.getDescription() << std::endl;
    }
};

// Client code
int main() {
    auto level1 = std::make_shared<Level1Support>();
    auto level2 = std::make_shared<Level2Support>();
    auto level3 = std::make_shared<Level3Support>();

    level1->setNextHandler(level2);
    level2->setNextHandler(level3);

    SupportTicket ticket1("Cannot connect to the internet", 1);
    SupportTicket ticket2("Computer is slow", 2);
    SupportTicket ticket3("System crash on startup", 3);

    level1->handleTicket(ticket1);
    level1->handleTicket(ticket2);
    level1->handleTicket(ticket3);

    return 0;
}
