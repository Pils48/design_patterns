#include <iostream>
#include <vector>
#include <string>
#include <memory>


using namespace std;

typedef struct VeryHeavySprite {
    VeryHeavySprite() {
        points.reserve(1000);
    }

    struct Point {
        double x;
        double y;
    };

    vector<Point> points;
} ObjectiveForFlyweight;

// Tree class
class Tree {
public:
    Tree(const string& type, int x, int y, int height, const ObjectiveForFlyweight& sprite)
        : type(type), x(x), y(y), height(height) {
            _sprite = make_shared<ObjectiveForFlyweight>(sprite);
        }

    void draw() const {
        cout << "Tree of type " << type << " at (" << x << ", " << y << ") with height " << height << endl;
    }

private:
    shared_ptr<ObjectiveForFlyweight> _sprite; // 8MB per each object
    string type;
    int x;
    int y;
    int height;
};

// Forest class
class Forest {
public:
    void plantTree(const string& type, int x, int y, int height, int sprite_id) {
        trees.push_back(Tree(type, x, y, height, staticSprites[sprite_id]));
    }

    void draw() const {
        for (const auto& tree : trees) {
            tree.draw();
        }
    }

    void addSprite(const ObjectiveForFlyweight&& sprite) {
        staticSprites.push_back(sprite);
    }

private:
    vector<Tree> trees;
    vector<ObjectiveForFlyweight> staticSprites; // Now all contexts will refer to these flyweights objects
};

// Client code
int main() {
    Forest forest;
    ObjectiveForFlyweight sprite_1;
    forest.addSprite(move(sprite_1));

    forest.plantTree("Oak", 1, 2, 100, 0);
    forest.plantTree("Pine", 2, 3, 80, 0);
    forest.plantTree("Oak", 3, 4, 120, 0);
    forest.plantTree("Pine", 4, 5, 90, 0);
    forest.plantTree("Oak", 5, 6, 110, 0);

    forest.draw();

    return 0;
}
