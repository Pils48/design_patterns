#include <iostream>


/** Class Explosion: For every new shape or rendering context, a new class needs to be created. 
 * This leads to a proliferation of classes (VectorCircle, RasterCircle, VectorSquare, RasterSquare, etc.).
 * Lack of Extensibility: Adding a new shape or rendering context requires changes in multiple places 
 * and the addition of multiple new classes, making the system hard to extend and maintain.
 * Tight Coupling: The shape classes are tightly coupled to their rendering implementations, which violates the Single Responsibility Principle. 
 * */


// Base Shape class
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Concrete Shape classes
class VectorCircle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle in Vector format" << std::endl;
    }
};

class RasterCircle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle in Raster format" << std::endl;
    }
};

class VectorSquare : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Square in Vector format" << std::endl;
    }
};

class RasterSquare : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Square in Raster format" << std::endl;
    }
};

// Client code
int main() {
    Shape* shapes[] = {
        new VectorCircle(),
        new RasterCircle(),
        new VectorSquare(),
        new RasterSquare()
    };

    for (const auto& shape : shapes) {
        shape->draw();
    }

    for (const auto& shape : shapes) {
        delete shape;
    }

    return 0;
}
