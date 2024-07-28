#include <iostream>
#include <vector>
#include <string>


/** 
 * Inconsistency: Employees and departments are treated separately. If the company structure changes frequently, 
 * the management of employees and departments will be complex and inconsistent.
 * Code Duplication: Methods for adding and printing are duplicated across employees and departments, leading to redundancy.
 * Scalability: Adding new types of organizational units will require significant changes to the existing code. */

// Employee class
class Employee {
public:
    Employee(const std::string& name, const std::string& position) 
        : name(name), position(position) {}

    std::string getName() const {
        return name;
    }

    std::string getPosition() const {
        return position;
    }

    void print() const {
        std::cout << "Employee: " << name << ", Position: " << position << std::endl;
    }

private:
    std::string name;
    std::string position;
};

// Department class
class Department {
public:
    Department(const std::string& name) : name(name) {}

    void addEmployee(const Employee& employee) {
        employees.push_back(employee);
    }

    void addDepartment(const Department& department) {
        departments.push_back(department);
    }

    void print() const {
        std::cout << "Department: " << name << std::endl;
        for (const auto& employee : employees) {
            employee.print();
        }
        for (const auto& department : departments) {
            department.print();
        }
    }

private:
    std::string name;
    std::vector<Employee> employees;
    std::vector<Department> departments;
};

// Client code
int main() {
    Employee emp1("John Doe", "Developer");
    Employee emp2("Jane Smith", "Manager");

    Department dept1("Development");
    dept1.addEmployee(emp1);

    Department dept2("Management");
   
