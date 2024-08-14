// Develop a system to manage books, borrowers, and
// transactions in a library.
// Book Database: Store book information (title, author, ISBN) in a
// database.
// Book Search: Allow users to search for books based on title, author, or
// ISBN.
// Book Checkout: Enable librarians to check out books to borrowers.
// Book Return: Record book returns and update availability status.
// Fine Calculation: Implement a fine calculation system for overdue
// books.
// User Interface: Design a user-friendly interface for easy interaction.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;
    bool isAvailable;

    Book(string t, string a) : title(t), author(a), isAvailable(true) {}
};

class Borrower {
public:
    string name;
    vector<Book> borrowedBooks;

    Borrower(string n) : name(n) {}
};

class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;

public:
    void addBook(const string &title, const string &author) {
        books.push_back(Book(title, author));
        cout << "Book added: " << title << " by " << author << endl;
    }

    void addBorrower(const string &name) {
        borrowers.push_back(Borrower(name));
        cout << "Borrower added: " << name << endl;
    }

    void checkoutBook(const string &title, const string &borrowerName) {
        Book* book = findBook(title);
        Borrower* borrower = findBorrower(borrowerName);

        if (book && borrower && book->isAvailable) {
            borrower->borrowedBooks.push_back(*book);
            book->isAvailable = false;
            cout << borrowerName << " checked out " << title << endl;
        } else {
            cout << "Book not available or borrower not found." << endl;
        }
    }

    void returnBook(const string &title, const string &borrowerName) {
        Borrower* borrower = findBorrower(borrowerName);

        if (borrower) {
            for (auto it = borrower->borrowedBooks.begin(); it != borrower->borrowedBooks.end(); ++it) {
                if (it->title == title) {
                    it->isAvailable = true;
                    borrower->borrowedBooks.erase(it);
                    cout << borrowerName << " returned " << title << endl;
                    return;
                }
            }
        }
        cout << "Book not found in borrower's list." << endl;
    }

private:
    Book* findBook(const string &title) {
        for (auto &book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;
    }

    Borrower* findBorrower(const string &name) {
        for (auto &borrower : borrowers) {
            if (borrower.name == name) {
                return &borrower;
            }
        }
        return nullptr;
    }
};

int main() {
    Library library;

    library.addBook("1984", "George Orwell");
    library.addBook("To Kill a Mockingbird", "Harper Lee");

    library.addBorrower("John Doe");
    library.addBorrower("Jane Doe");

    library.checkoutBook("1984", "John Doe");
    library.returnBook("1984", "John Doe");

    return 0;
}
