#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Component interface
class OrganizationComponent {
public:
    virtual void print() const = 0;
    virtual void add(std::shared_ptr<OrganizationComponent> component) {}
    virtual ~OrganizationComponent() = default;
};

// Leaf class
class Employee : public OrganizationComponent {
public:
    Employee(const std::string& name, const std::string& position) 
        : name(name), position(position) {}

    void print() const override {
        std::cout << "Employee: " << name << ", Position: " << position << std::endl;
    }

private:
    std::string name;
    std::string position;
};

// Composite class
class Department : public OrganizationComponent {
public:
    Department(const std::string& name) : name(name) {}

    void add(std::shared_ptr<OrganizationComponent> component) override {
        components.push_back(component);
    }

    void print() const override {
        std::cout << "Department: " << name << std::endl;
        for (const auto& component : components) {
            component->print();
        }
    }

private:
    std::string name;
    std::vector<std::shared_ptr<OrganizationComponent>> components;
};

// Client code
int main() {
    auto emp1 = std::make_shared<Employee>("John Doe", "Developer");
    auto emp2 = std::make_shared<Employee>("Jane Smith", "Manager");

    auto dept1 = std::make_shared<Department>("Development");
    dept1->add(emp1);

    auto dept2 = std::make_shared<Department>("Management");
    dept2->add(emp2);

    auto company = std::make_shared<Department>("Company");
    company->add(dept1);
    company->add(dept2);

    company->print();

    return 0;
}
