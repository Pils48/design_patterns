#include <iostream>
#include <string>


/** 
 * Resource-Intensive Initialization: The image is loaded from disk as soon as the Image object is created, which might be unnecessary if the image is not displayed immediately.
 * Lack of Control: The client has no control over when the image is loaded, leading to potential performance issues if many images are created but not used immediately.
 */

// Image class that represents a large image file
class Image {
public:
    Image(const std::string& filename) : filename(filename) {
        loadImageFromDisk();
    }

    void display() const {
        std::cout << "Displaying " << filename << std::endl;
    }

private:
    std::string filename;

    void loadImageFromDisk() {
        std::cout << "Loading " << filename << " from disk..." << std::endl;
        // Simulate a delay in loading the image
    }
};

// Client code
int main() {
    // Create an image object
    Image image("large_image.jpg");

    // Perform other operations...

    // Display the image
    image.display();

    return 0;
}
