#include <iostream>
#include <string>
#include <unordered_map>

/** 
 * Inefficiency: 
 * Creating each enemy instance from scratch can be inefficient, especially if the creation process involves complex setup or initialization.
 * 
 * Lack of Flexibility:
 * If you want to create a slightly modified version of an existing enemy, you have to go through the entire creation process again.
 * 
 * Code Duplication:
 * Creating multiple instances of the same enemy type involves duplicating code and configuration. 
*/

// Base class for all characters
class Character {
public:
    Character(std::string name, int health, int attack, int defense)
        : name(name), health(health), attack(attack), defense(defense) {}

    virtual void display() const = 0;
    virtual ~Character() {}

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
};

// Factory for creating characters (inefficient approach)
class CharacterFactory {
public:
    static Character* createCharacter(const std::string& type, const std::string& name) {
        if (type == "Warrior") {
            return new Warrior(name);
        } else if (type == "Mage") {
            return new Mage(name);
        } else {
            return nullptr;
        }
    }
};

int main() {
    Character* warrior1 = CharacterFactory::createCharacter("Warrior", "Thor");
    Character* mage1 = CharacterFactory::createCharacter("Mage", "Gandalf");

    if (warrior1) warrior1->display();
    if (mage1) mage1->display();

    // Clean up
    delete warrior1;
    delete mage1;

    return 0;
}
