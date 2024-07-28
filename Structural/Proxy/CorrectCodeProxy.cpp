#include <iostream>
#include <string>
#include <memory>

// Image interface
// Proxy and real image have common interface, proxy just checking whether it is needed to create an instance
class IImage {
public:
    virtual void display() const = 0;
    virtual ~IImage() = default;
};

// RealImage class that represents a large image file
class RealImage : public IImage {
public:
    RealImage(const std::string& filename) : filename(filename) {
        loadImageFromDisk();
    }

    void display() const override {
        std::cout << "Displaying " << filename << std::endl;
    }

private:
    std::string filename;

    void loadImageFromDisk() {
        std::cout << "Loading " << filename << " from disk..." << std::endl;
        // Simulate a delay in loading the image
    }
};

// ProxyImage class that controls access to RealImage
class ProxyImage : public IImage {
public:
    ProxyImage(const std::string& filename) : filename(filename), realImage(nullptr) {}

    void display() const override {
        if (!realImage) {
            realImage = std::make_unique<RealImage>(filename);
        }
        realImage->display();
    }

private:
    std::string filename;
    mutable std::unique_ptr<RealImage> realImage;
};

// Client code
int main() {
    // Create a proxy image object
    ProxyImage image("large_image.jpg");

    // Perform other operations...

    // Display the image
    image.display(); // Image is loaded from disk only when display is called

    return 0;
}
