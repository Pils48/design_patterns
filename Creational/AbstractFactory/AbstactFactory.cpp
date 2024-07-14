#include <iostream>
#include <memory>
#include <string>


/** First lets start with a bad code which require usage of factory method
 * 1. In order to demonstrate the AbstractFactory pattern we need to transfer renderUI function
 *    into the class UI which will be creating all nessacery widgets for the same OS. Essentially 
 *    this is vehicle store from previous example but with several factory methods
 * 2. By the way another option to handle the problem could be organizing all the widgets into one UI class
 *    and then instancing UI with one factory method. But this is not so flexible
 */

using namespace std;

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
        cout << "Rendering a button in a Windows style" << endl;
    }
};

// MacOS button implementation
class MacOSButton : public Button {
public:
    void paint() const override {
        cout << "Rendering a button in a MacOS style" << endl;
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
        cout << "Rendering a checkbox in a Windows style" << endl;
    }
};

// MacOS checkbox implementation
class MacOSCheckbox : public Checkbox {
public:
    void paint() const override {
        cout << "Rendering a checkbox in a MacOS style" << endl;
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
        cout << "Rendering a slider in a Windows style" << endl;
    }
};

// MacOS checkbox implementation
class MacOSSlider : public Slider {
public:
    void paint() const override {
        cout << "Rendering a slider in a MacOS style" << endl;
    }
};

using ButtonPtr = unique_ptr<Button>;
using CheckboxPtr = unique_ptr<Checkbox>;
using SliderPtr = unique_ptr<Slider>;

// This UIFactory class is our Abstract Factory 
class UIFactory {

public:
    virtual ButtonPtr createButton() const = 0;

    virtual CheckboxPtr createCheckbox() const = 0;

    virtual SliderPtr createSlider() const = 0;

    // If we will need more widgets unfortunately this class does not follow Open/Close principle registry is needed
};

class WindowsUIFactory : public UIFactory {

public:
    ButtonPtr createButton() const override {
        return make_unique<WindowsButton>();
    }

    CheckboxPtr createCheckbox() const override {
        return make_unique<WindowsCheckbox>();
    }

    SliderPtr createSlider() const override {
        return make_unique<WindowsSlider>();
    }
    // If we will need more widgets unfortunately this class does not follow Open/Close principle registry is needed
};

class MacOSUIFactory : public UIFactory {

public:
    ButtonPtr createButton() const override {
        return make_unique<MacOSButton>();
    }

    CheckboxPtr createCheckbox() const override {
        return make_unique<MacOSCheckbox>();
    }

    SliderPtr createSlider() const override {
        return make_unique<MacOSSlider>();
    }
    // If we will need more widgets unfortunately this class does not follow Open/Close principle registry is needed
};

// I am not implementing this class because I am exhausted to write the same code))
// Generally as I can understand this is exactly why we need meta classes
// class LinuxUIFactory : UIFactory {

// public:
//     public:
//     ButtonPtr createButton() override {
//         return make_unique<LinuxButton>();
//     }

//     CheckboxPtr createCheckbox() override {
//         return make_unique<LinuxCheckbox>();
//     }

//     SliderPtr createSlider() override {
//         return make_unique<LinuxSlider>();
//     }

//     // If we will need more widgets unfortunately this class does not follow Open/Close principle registry is needed
// };

// Client code to render UI elements
// Now we can pass an abstract factory right here
void renderUI(const UIFactory &ui_factory) {
    ButtonPtr button;
    CheckboxPtr checkbox;
    SliderPtr slider;

    button = ui_factory.createButton();
    checkbox = ui_factory.createCheckbox();
    slider = ui_factory.createSlider();
    // And again if we have new widget we are in trouble

    button->paint();
    checkbox->paint();
    slider->paint();
}

int main() {
    WindowsUIFactory windows_factory = WindowsUIFactory();
    MacOSUIFactory macos_factory = MacOSUIFactory();
    // LinuxUIFactory linux_factory = LinuxUIFactory();

    renderUI(windows_factory);
    renderUI(macos_factory);
    
    return 0;
}
