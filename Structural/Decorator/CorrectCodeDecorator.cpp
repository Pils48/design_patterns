#include <iostream>
#include <memory>
#include <string>

// Component interface
class TextEditor {
public:
    virtual void display() const = 0;
    virtual ~TextEditor() = default;
};

// ConcreteComponent
class BasicTextEditor : public TextEditor {
public:
    void display() const override {
        std::cout << "Displaying basic text editor" << std::endl;
    }
};

// Decorator
class TextEditorDecorator : public TextEditor {
protected:
    std::shared_ptr<TextEditor> editor;
public:
    TextEditorDecorator(std::shared_ptr<TextEditor> editor) : editor(editor) {}
    void display() const override {
        editor->display();
    }
};

// ConcreteDecorators
class SpellCheckDecorator : public TextEditorDecorator {
public:
    SpellCheckDecorator(std::shared_ptr<TextEditor> editor) : TextEditorDecorator(editor) {}
    void display() const override {
        TextEditorDecorator::display();
        std::cout << "Spell checking enabled" << std::endl;
    }
};

class AutoSaveDecorator : public TextEditorDecorator {
public:
    AutoSaveDecorator(std::shared_ptr<TextEditor> editor) : TextEditorDecorator(editor) {}
    void display() const override {
        TextEditorDecorator::display();
        std::cout << "Auto-save enabled" << std::endl;
    }
};

// Client code
int main() {
    std::shared_ptr<TextEditor> editor = std::make_shared<BasicTextEditor>();
    editor->display();
    std::cout << std::endl;

    std::shared_ptr<TextEditor> spellCheckEditor = std::make_shared<SpellCheckDecorator>(editor);
    spellCheckEditor->display();
    std::cout << std::endl;

    std::shared_ptr<TextEditor> autoSaveEditor = std::make_shared<AutoSaveDecorator>(spellCheckEditor);
    autoSaveEditor->display();
    std::cout << std::endl;

    // And now thanks to decorator we can pass already modified editor to further modifiers 
    std::shared_ptr<TextEditor> fullFeaturedEditor = std::make_shared<SpellCheckDecorator>(autoSaveEditor); 
    fullFeaturedEditor->display();

    return 0;
}
