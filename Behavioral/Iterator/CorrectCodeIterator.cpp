#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Book class
class Book {
public:
    Book(const std::string& title) : title(title) {}

    const std::string& getTitle() const {
        return title;
    }

private:
    std::string title;
};

// Iterator interface
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual Book next() = 0;
};

// Concrete Iterator for the Library class
class LibraryIterator : public Iterator {
public:
    LibraryIterator(const std::vector<Book>& books) : books(books), position(0) {}

    bool hasNext() const override {
        return position < books.size();
    }

    Book next() override {
        return books[position++];
    }

private:
    std::vector<Book> books;
    size_t position;
};

// Aggregate interface
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator> createIterator() const = 0;
};

// Library class that holds a collection of books
class Library : public Aggregate {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    std::unique_ptr<Iterator> createIterator() const override {
        return std::make_unique<LibraryIterator>(books);
    }

private:
    std::vector<Book> books;
};

// Client code
int main() {
    Library library;
    library.addBook(Book("The Catcher in the Rye"));
    library.addBook(Book("To Kill a Mockingbird"));
    library.addBook(Book("1984"));

    std::unique_ptr<Iterator> iterator = library.createIterator();
    while (iterator->hasNext()) {
        Book book = iterator->next();
        std::cout << book.getTitle() << std::endl;
    }

    return 0;
}
