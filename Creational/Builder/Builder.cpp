#include <iostream>
#include <string>
#include <memory>


using namespace std;

class Warrior
{
private:
    unsigned int _hp;
    string _melee_weapon;
    string _ranged_weapon;
    string _armor;
    string _shield;
    string _rank;

// Конструктор желательно должен быть объявлен приватным, чтобы все объекты создавались билдером
public:
    Warrior(
        const unsigned int hp, 
        const string &melee_weapon, 
        const string &ranged_weapon, 
        const string &armor, 
        const string &shield,
        const string &rank
    ) : _hp(hp),
    _melee_weapon(melee_weapon),
    _ranged_weapon(ranged_weapon),
    _armor(armor),
    _shield(shield),
    _rank(rank)
    {

    }
};


class WarriorBuilder
{
private:
    unsigned int _hp;
    string _melee_weapon;
    string _ranged_weapon;
    string _armor;
    string _shield;
    string _rank;

public:
    friend class Warrior;

    WarriorBuilder()
    {

    }

    WarriorBuilder& hp(const unsigned int hp_value)
    {
        _hp = hp_value;
        return *this;
    }

    WarriorBuilder& melee(const string &melee_weapon)
    {
        _melee_weapon = melee_weapon;
        return *this;
    }

    // Аналогично остальные функции

    shared_ptr<Warrior> build()
    {
        // Does not work with new Warrior
        return make_shared<Warrior>(Warrior(_hp, _melee_weapon, _ranged_weapon, _armor, _shield, _rank));
    }
};


int main()
{
    WarriorBuilder builder = WarriorBuilder();
    builder.hp(100).melee("Sword");
    //or
    // builder.hp(100);
    // builder.melee("Sword");
    auto warrior = builder.build();
    return 0;
}