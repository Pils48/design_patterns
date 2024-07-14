#include <iostream>
#include <memory>
#include <string>


/** First lets start with a bad code which require usage of factory method
 * 1. Similarly to factory method here we have a function renderUI which contains huge if statement
 *    which we will have to modify whenever new operation system appears 
 * 2. However, in contrast to the factory method example here we are creating the whole set of widgets related
 *    to the same operation system, Button and CheckBox, in particular. Someday we will try to add one more 
 *    widget and it is going to cause lots of troubles for us as all if statements will require modifications. 
 *    However even using Abstract Factory we can face with the same problem, meaning we will have to rewrite
 *    say createUI when we are introducing new widget. Again the structure with registry might make sense here 
 */

// Base class for buttons
class Button {
public:
    virtual void paint() const = 0;
    virtual ~Button() {}
};

// Windows button implementation
class WindowsButton : public Button {
public:
    void paint() const override {
        std::cout << "Rendering a button in a Windows style" << std::endl;
    }
};

// MacOS button implementation
class MacOSButton : public Button {
public:
    void paint() const override {
        std::cout << "Rendering a button in a MacOS style" << std::endl;
    }
};

// Base class for checkboxes
class Checkbox {
public:
    virtual void paint() const = 0;
    virtual ~Checkbox() {}
};

// Windows checkbox implementation
class WindowsCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "Rendering a checkbox in a Windows style" << std::endl;
    }
};

// MacOS checkbox implementation
class MacOSCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "Rendering a checkbox in a MacOS style" << std::endl;
    }
};

// We introducing new widget. It is going to be a disaster
class Slider {
public:
    virtual void paint() const = 0;
    virtual ~Slider() {}
};

// Windows checkbox implementation
class WindowsSlider : public Slider {
public:
    void paint() const override {
        std::cout << "Rendering a slider in a Windows style" << std::endl;
    }
};

// MacOS checkbox implementation
class MacOSSlider : public Slider {
public:
    void paint() const override {
        std::cout << "Rendering a slider in a MacOS style" << std::endl;
    }
};



// Client code to render UI elements
void renderUI(const std::string& osType) {
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;
    std::unique_ptr<Slider> slider;

    if (osType == "Windows") {
        button = std::make_unique<WindowsButton>();
        checkbox = std::make_unique<WindowsCheckbox>();
        // After adding new widget we have to change all written if statements
        slider = std::make_unique<WindowsSlider>();
    } else if (osType == "MacOS") {
        button = std::make_unique<MacOSButton>();
        checkbox = std::make_unique<MacOSCheckbox>();
        // After adding new widget we have to change all written if statements
        slider = std::make_unique<MacOSSlider>();
    } else if (osType == "LinuxOS") {
        // Here we are sneaking into renderUI for adding new OS support, bad for us
        // button = std::make_unique<MacOSButton>();
        // checkbox = std::make_unique<MacOSCheckbox>();
        // slider = std::make_unique<MacOSSlider>();
    } else {
        std::cerr << "Unknown OS type" << std::endl;
        return;
    }

    button->paint();
    checkbox->paint();
}

int main() {
    std::string osType = "Windows"; // or "MacOS"

    // Render UI for the specified OS type
    renderUI(osType);

    return 0;
}
