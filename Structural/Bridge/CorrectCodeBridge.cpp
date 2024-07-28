#include <iostream>
#include <memory>


// First we need to define renderer class hierarchy
class Renderer {
public:
    virtual void renderCircle() const = 0;
    virtual void renderSquare() const = 0;
    virtual void renderTriangle() const = 0;
    virtual ~Renderer() = default;
};

class VectorRenderer : public Renderer {
public:
    void renderCircle() const override {
        std::cout << "Drawing Circle in Vector format" << std::endl;
    }

    void renderSquare() const override {
        std::cout << "Drawing Square in Vector format" << std::endl;
    }

    // But still if we need to add more shapes we are chaning code here
    void renderTriangle() const override {
        std::cout << "Drawing Triangle in Vector format" << std::endl;
    }
};

class RasterRenderer : public Renderer {
public:
    void renderCircle() const override {
        std::cout << "Drawing Circle in Raster format" << std::endl;
    }

    void renderSquare() const override {
        std::cout << "Drawing Square in Raster format" << std::endl;
    }
    
    // But still if we need to add more shapes we are chaning code here
    void renderTriangle() const override {
        std::cout << "Drawing Square in Raster format" << std::endl;
    }
};

// Base Shape class
class Shape {
public:
    Shape(std::shared_ptr<Renderer> renderer) : renderer(renderer) {}
    virtual void draw() const = 0;
    virtual ~Shape() = default;

protected:
    std::shared_ptr<Renderer> renderer;
};

// Concrete Shape classes
class Circle : public Shape {
public:
    Circle(std::shared_ptr<Renderer> renderer) : Shape(renderer) {}

    void draw() const override {
        renderer->renderCircle();
    }
};

class Square : public Shape {
public:
    Square(std::shared_ptr<Renderer> renderer) : Shape(renderer) {}

    void draw() const override {
        renderer->renderSquare();
    }
};

class Triangle : public Shape {
   public:
    Triangle(std::shared_ptr<Renderer> renderer) : Shape(renderer) {}

    void draw() const override {
        renderer->renderTriangle(); // Here we need to be sure that renderer does contain this drawing method
    } 
};

// Client code
int main() {
    std::shared_ptr<Renderer> vectorRenderer = std::make_shared<VectorRenderer>();
    std::shared_ptr<Renderer> rasterRenderer = std::make_shared<RasterRenderer>();

    Shape* shapes[] = {
        new Circle(vectorRenderer),
        new Circle(rasterRenderer),
        new Square(vectorRenderer),
        new Square(rasterRenderer)
    };

    for (const auto& shape : shapes) {
        shape->draw();
    }

    for (const auto& shape : shapes) {
        delete shape;
    }

    return 0;
}
