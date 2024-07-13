#include <vector>
#include <iostream>
#include <string>


using namespace std;

/** First lets start with a bad code which require usage of factory method
 * 1. This is a bad code because we explicitly tight to the Car and Bike classes in orderVehicle
 *    This means if we will change constructors we will be forced to rewrite orderVehicle 
 * 
 * 2. And then this code is not scalable because each and every new vehicle would cause changes in orderVehicle
 */

class Car {

private:
    string _producer;
    string _model;

public:
    Car(const string &producer, const string &model) {
        _producer = producer;
        _model = model; 
    }

    void drive() {
        cout << "Driving a " << _producer << " " << _model << endl;
    }
};

class Bike {

private:
    string _producer;
    string _model;

public:
    Bike(const string &producer, const string &model) {
        _producer = producer;
        _model = model; 
    }

    void ride() {
        cout << "Riding a " << _producer << " " << _model << endl;
    }
};

/** Now if are going to add new type of transport we will be in trouble
 * 1. Obviously we will have to implement it, but this is inevitable 
 * 2. We will add new else if condition in orderVehicles
 */

class Tram {

private:
    string _producer;
    string _model;

public:
    Tram(const string &producer, const string &model) {
        _producer = producer;
        _model = model; 
    }

    void go() {
        cout << "Going by a " << _producer << " " << _model << endl;
    }
};

class VehicleStore {

public:
    void* orderVehicle(const string& vehicleType, const string& make, const string& model) {
        if (vehicleType == "car") {
            return new Car(make, model);
        } else if (vehicleType == "bike") {
            return new Bike(make, model);
        } else if (vehicleType == "tram") {
            return new Tram(make, model);
        } else {
            throw invalid_argument("Unknown vehicle type");
        }
    }
};


int main()
{
    VehicleStore store;

    Car* car = static_cast<Car*>(store.orderVehicle("car", "Toyota", "Camry"));
    car->drive();
    delete car;

    Bike* bike = static_cast<Bike*>(store.orderVehicle("bike", "Yamaha", "FZ"));
    bike->ride();
    delete bike;

    Tram* tram = static_cast<Tram*>(store.orderVehicle("tram", "LIAZ", "FZ"));
    tram->go();
    delete tram;

    return 0;
}