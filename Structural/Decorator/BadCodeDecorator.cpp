#include <iostream>
#include <string>

/**
 * Class Explosion: For every new feature combination, a new subclass is required. This quickly becomes unmanageable.
 * Lack of Flexibility: If you want to add a new feature or a new combination of features, you have to create new classes.
 * Tight Coupling: The features are tightly coupled with the text editor, making the system hard to extend and maintain.
 */

class TextEditor {
public:
    virtual void display() const = 0;
    virtual ~TextEditor() = default;
};

class BasicTextEditor : public TextEditor {
public:
    void display() const override {
        std::cout << "Displaying basic text editor" << std::endl;
    }
};

class SpellCheckTextEditor : public BasicTextEditor {
public:
    void display() const override {
        BasicTextEditor::display();
        std::cout << "Spell checking enabled" << std::endl;
    }
};

class AutoSaveTextEditor : public BasicTextEditor {
public:
    void display() const override {
        BasicTextEditor::display();
        std::cout << "Auto-save enabled" << std::endl;
    }
};

class SpellCheckAutoSaveTextEditor : public BasicTextEditor {
public:
    void display() const override {
        BasicTextEditor::display();
        std::cout << "Spell checking enabled" << std::endl;
        std::cout << "Auto-save enabled" << std::endl;
    }
};

// Client code
int main() {
    TextEditor* editor1 = new BasicTextEditor();
    TextEditor* editor2 = new SpellCheckTextEditor();
    TextEditor* editor3 = new AutoSaveTextEditor();
    TextEditor* editor4 = new SpellCheckAutoSaveTextEditor();

    editor1->display();
    std::cout << std::endl;

    editor2->display();
    std::cout << std::endl;

    editor3->display();
    std::cout << std::endl;

    editor4->display();
    std::cout << std::endl;

    delete editor1;
    delete editor2;
    delete editor3;
    delete editor4;

    return 0;
}
