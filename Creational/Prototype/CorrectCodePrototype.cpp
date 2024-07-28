#include <iostream>
#include <string>
#include <unordered_map>

/** 
 * 
*/

// Base class for all characters
class Character {
public:
    Character(std::string name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    virtual void display() const = 0;
    virtual ~Character() {}

    // Abstract clone for prototype implementation
    virtual Character* clone() const = 0;

protected:
    std::string name;
    int health;
    int attack;
    int defense;
};

// Warrior class
class Warrior : public Character {
public:
    Warrior(std::string name)
        : Character(name, 100, 20, 10) {}

    void display() const override {
        std::cout << "Warrior: " << name << ", Health: " << health
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    Character* clone() const override {
        return new Warrior(*this);
    }

};

// Mage class
class Mage : public Character {
public:
    Mage(std::string name)
        : Character(name, 70, 25, 5) {}

    void display() const override {
        std::cout << "Mage: " << name << ", Health: " << health
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    Character* clone() const override {
        return new Mage(*this);
    }
};


int main() {
    Warrior* war_1 = new Warrior("Thor");
    war_1->display();
    // prototype working 
    Character* war_2 = dynamic_cast<Warrior*>(war_1->clone());
    war_2->display();

    // Clean up
    delete war_1;
    delete war_2;

    return 0;
}
