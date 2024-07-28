#include <iostream>
#include <vector>
#include <string>

typedef struct VeryHeavySprite {
    struct Point {
        double x;
        double y;
    };
    Point points[1024 * 1024];
} ObjectiveForFlyweight;

// Tree class
class Tree {
public:
    Tree(const std::string& type, int x, int y, int height)
        : type(type), x(x), y(y), height(height) {}

    void draw() const {
        std::cout << "Tree of type " << type << " at (" << x << ", " << y << ") with height " << height << std::endl;
    }

private:
    ObjectiveForFlyweight sprite; // 8MB per each object
    std::string type;
    int x;
    int y;
    int height;
};

// Forest class
class Forest {
public:
    void plantTree(const std::string& type, int x, int y, int height) {
        trees.emplace_back(type, x, y, height);
    }

    void draw() const {
        for (const auto& tree : trees) {
            tree.draw();
        }
    }

private:
    std::vector<Tree> trees;
};

// Client code
int main() {
    Forest forest;

    forest.plantTree("Oak", 1, 2, 100);
    forest.plantTree("Pine", 2, 3, 80);
    forest.plantTree("Oak", 3, 4, 120);
    forest.plantTree("Pine", 4, 5, 90);
    forest.plantTree("Oak", 5, 6, 110);

    forest.draw();

    return 0;
}
