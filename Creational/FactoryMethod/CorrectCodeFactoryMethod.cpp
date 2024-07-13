#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>


using namespace std;

/** So correct implementation:
 * 1. We need to create a hierarchy of Vehicles as we would like to operate with abstract Vehicle in factory
 * 2. Then we need to add VehicleStore class that will be playing the role of the class containing factory method createVehicle
 *    Two implementations is possible. The first one we add registry function in the class containing createVehicle and then call 
 *    create for specific implementations. Or we add classes implementing our VehicleStore and operate with them. 
 */

class Vehicle {
protected:
    string _producer;
    string _model;

public:
    Vehicle(const string &producer, const string &model) 
    : _producer(producer), _model(model) {}

    Vehicle(const Vehicle &other) = default;
};

class Car : public Vehicle {

public:
    Car(const string &producer, const string &model) 
    : Vehicle(producer, model) {}

    void drive() {
        cout << "Driving a " << _producer << " " << _model << endl;
    }
};

class Bike : public Vehicle {

public:
    Bike(const string &producer, const string &model) 
    : Vehicle(producer, model) {}

    void ride() {
        cout << "Riding a " << _producer << " " << _model << endl;
    }
};

class Tram : public Vehicle {

public:
    Tram(const string &producer, const string &model) 
    : Vehicle(producer, model) {}

    void go() {
        cout << "Going by a " << _producer << " " << _model << endl;
    }
};


// We can use kind of registry and do not overload the program with specific implementations of stores for every vehicle
class VehicleStoreRegistry {
    using createFunctionPtr = function<unique_ptr<Vehicle>(const string &producer, const string &model)>;
private:
    unordered_map<string, createFunctionPtr> vehicleRegistry;

public:
    VehicleStoreRegistry() {
        // Register vehicle types and their constructors
        registerVehicle("car", [](const string &producer, const string &model) { return make_unique<Car>(producer, model); });
        registerVehicle("bike", [](const string &producer, const string &model) { return make_unique<Bike>(producer, model); });
        // Add more vehicle types here as needed
        // registerVehicle("tram", [](const string &producer, const string &model) { return make_unique<Tram>(producer, model); });
    }

    // Factory method to create vehicles based on type
    unique_ptr<Vehicle> createVehicle(const string& type, const string &producer, const string &model) {
        auto it = vehicleRegistry.find(type);
        if (it != vehicleRegistry.end()) {
            return it->second(producer, model); // Call the registered constructor
        } else {
            cerr << "Invalid vehicle type: " << type << endl;
            return nullptr;
        }
    }

    // Register a vehicle type with its constructor
    void registerVehicle(const string& type, createFunctionPtr constructor) {
        vehicleRegistry[type] = constructor;
    }
};

// Now we add the second variant of factory method usage
class VehicleStore {

public:
    virtual Vehicle* createVehicle(const string &producer, const string &model) = 0;

};

class CarStore : VehicleStore {

public:
    Vehicle* createVehicle(const string &producer, const string &model) {
        return new Car(producer, model);
    }

};

class BikeStore : VehicleStore {

public:
    Vehicle* createVehicle(const string &producer, const string &model) {
        return new Bike(producer, model);
    }

};

class TramStore : VehicleStore {

public:
    Vehicle* createVehicle(const string &producer, const string &model) {
        return new Tram(producer, model);
    }

};




int main()
{
    // And we can create such store for any of the vehicle
    CarStore car_store;
    Car *car = static_cast<Car *>(car_store.createVehicle("toyota", "supra"));
    car->drive();
    delete car;

    // Usage of registry
    VehicleStoreRegistry store_with_registry;
    auto car_ptr = store_with_registry.createVehicle("car", "toyota", "supra");
}
