#include <iostream>
#include <string>


using namespace std;

// Receiver: Text editor operations
// TextEditor class
class TextEditor {
public:
    void insertText(const std::string& text) {
        std::cout << "Inserted text: " << text << std::endl;
    }

    void deleteText(const std::string& text) {
        std::cout << "Deleted text: " << text << std::endl;
    }

    void formatText(const std::string& format) {
        std::cout << "Formatted text: " << format << std::endl;
    }

    void insertImage(const std::string& imagePath) {
        std::cout << "Inserted image from: " << imagePath << std::endl;
    }

    void saveDocument(const std::string& fileName) {
        std::cout << "Document saved as: " << fileName << std::endl;
    }
};

// Client: User interaction with commands

int main() {
    // Create text editor instance
    TextEditor textEditor;

    // Issue commands (without Command pattern implementation)
    textEditor.insertText("Hello, Command Pattern!");
    textEditor.formatText("Bold");
    textEditor.insertImage("/path/to/image.png");
    textEditor.saveDocument("document.txt");

    // Client continues with more operations...

    return 0;
}
