#include <iostream>
#include <vector>
#include <string>

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

// Library class that holds a collection of books
class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    const std::vector<Book>& getBooks() const {
        return books;
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

    const std::vector<Book>& books = library.getBooks();
    for (size_t i = 0; i < books.size(); ++i) {
        std::cout << books[i].getTitle() << std::endl;
    }

    return 0;
}
