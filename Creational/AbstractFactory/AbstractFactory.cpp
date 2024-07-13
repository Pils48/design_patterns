#include <vector>
#include <iostream>


struct Mesh
{
    std::vector<std::vector<int>> points{};
};



class Building
{
private:
    unsigned int _hp;
    Mesh _mesh;
    bool _visibility;

public:

    Building(Mesh mesh) : _hp(100), _mesh(mesh), _visibility(true)
    {

    }

    unsigned int getHP() const
    {
        return _hp;
    }

    Mesh getMesh() const
    {
        return _mesh;
    }

    bool getVisibility()
    {
        return _visibility;
    }

    void setHP(const unsigned int upd_hp)
    {
        _hp = upd_hp;
    }

    void toogleVisibility()
    {
        _visibility = !_visibility; 
    }

    // К каждому зданию может понадобится по разному подбежать
    virtual std::vector<float> planPath(std::vector<float> from, std::vector<float> to)
    {
        return std::vector<float>{};
    } // Это полная дичь, но если пишу =0 не получается возвращать Building из create dynamic_cast?
};


class ProductionBuilding : public Building
{
public:

    ProductionBuilding(Mesh mesh) : Building(mesh)
    {
        std::cout << "Production building has been created." << std::endl;
    }

    ProductionBuilding(const ProductionBuilding &other) = delete;

    ProductionBuilding operator=(const ProductionBuilding &other) = delete;

    std::vector<float> planPath(std::vector<float> from, std::vector<float> to) override
    {
        std::cout << "Simple path planning along the roads!" << std::endl;
        return std::vector<float>{};
    }
};


class MilitaryBuilding : public Building
{
public:

    MilitaryBuilding(Mesh mesh) : Building(mesh)
    {
        std::cout << "Military building has been created." << std::endl;
    }

    MilitaryBuilding(const MilitaryBuilding &other) = delete;

    MilitaryBuilding operator=(const MilitaryBuilding &other) = delete;

    std::vector<float> planPath(std::vector<float> from, std::vector<float> to) override
    {
        std::cout << "Straight path ignoring the roads!" << std::endl;
        return std::vector<float>{};
    }
};

// Есди мы захотим добавить новый класс зданий мы легко это сделаем реализовав класс зданий и фактори класс
class GeneralBuilding : public Building
{
public:

    GeneralBuilding(Mesh mesh) : Building(mesh)
    {
        std::cout << "General building has been created." << std::endl;
    }

    GeneralBuilding(const GeneralBuilding &other) = delete;

    GeneralBuilding operator=(const GeneralBuilding &other) = delete;

    // Блин planPath точно такой же как у ProductionBuilding, по идее хорошо бы сделать PathPlanner полем Building
    std::vector<float> planPath(std::vector<float> from, std::vector<float> to) override
    {
        std::cout << "Simple path planning along the roads!" << std::endl;
        return std::vector<float>{};
    }
};


// Abstract Factory По существу получилась она а не метод, так как если BuildingСreator
// может возвращать его больше объектов
class BuildingsCreator
{

public:
    // Снова убрал чисто виртуальную функцию
    virtual Building create(Mesh mesh) const = 0;

    // Ниже можно добавлять другие шутки которые может создавать этот абстрактный класс
};


class MilitaryBuildingsCreator : public BuildingsCreator
{

public:
    // Здесь сделал planPath не абстрактным, но в примере абстрактный, что за дичь
    Building create(Mesh mesh) const override
    {
        // Здесь будет использоваться конструктор копирования который я удалил
        return MilitaryBuilding(mesh);
    }
};


class ProductionBuildingCreator : public BuildingsCreator
{

public:
    // Здесь сделал planPath не абстрактным, но в примере абстрактный, что за дичь
    Building create(Mesh mesh) const override
    {
        // Здесь будет использоваться конструктор копирования который я удалил
        return ProductionBuilding(mesh);
    }
};


//Теперь мы реализуем фабрику для GeneralBuilding и ниже ничего не сломается
class GeneralBuildingsCreator : public BuildingsCreator
{

public:
    // Здесь сделал planPath не абстрактным, но в примере абстрактный, что за дичь
    Building create(Mesh mesh) const override
    {
        // Здесь будет использоваться конструктор копирования который я удалил
        return GeneralBuilding(mesh);
    }
};


/*
    Без использования фабрики, мы не смогли бы нормально реализовать следующую функцию
    В противном случае нам пришлось бы передавать, некоторый аргумент, который определял, 
    что должно создавться внутри. Так как контруктор проассоциирован с конкретным классом 
    и что еще важнее вызывается имеено в момент создания объекта
    мы не можем делигировать выяснение того какой объект создать самим классам зданий.
*/
void initializeBuildingAndPath(const BuildingsCreator &creator, const Mesh &mesh)
{
    Building building = creator.create(mesh);
    building.planPath({0}, {0});

    /*
     Иначе мы бы писали что-то вроде

    switch (type_of_building)
    {
        case "Military":
        building = MilitaryBuilding(mesh);
        break;

        case "Production":
        building = ProductionBuilding(mesh);
        break;
    }

    Как только появится новый тип зданий, нам придется менять эту секцию
    */
}


int main()
{
    Mesh mesh;
    MilitaryBuildingsCreator military_creator = MilitaryBuildingsCreator();
    ProductionBuildingCreator production_creator = ProductionBuildingCreator();

    // Не очень полезное использование, так как можно просто вызвать конструкторы
    Building building = military_creator.create(mesh);
    building = production_creator.create(mesh);

    MilitaryBuilding mb = MilitaryBuilding(mesh);
    ProductionBuilding pb = ProductionBuilding(mesh);

    // Гораздо более полезный кейс
    initializeBuildingAndPath(military_creator, mesh);
    initializeBuildingAndPath(production_creator, mesh);

    //Теперь попробуем вызвать функцию initializeBuildingAndPath с новым классом
    GeneralBuildingsCreator general_creator = GeneralBuildingsCreator();
    initializeBuildingAndPath(general_creator, mesh);

    return 0;
}