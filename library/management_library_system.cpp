#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    Book* next;
};

class Library {
private:
    Book* head;

public:
    Library() {
        head = nullptr;
    }

    void addBook(int id, string title, string author) {
        Book* newBook = new Book{id, title, author, nullptr};
        if (!head) {
            head = newBook;
        } else {
            Book* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newBook;
        }
        cout << "Book added successfully.\n";
    }

    void displayBooks() {
        if (!head) {
            cout << "Library is empty.\n";
            return;
        }
        Book* temp = head;
        cout << "\nBooks in Library:\n";
        while (temp) {
            cout << "ID: " << temp->id << ", Title: " << temp->title << ", Author: " << temp->author << endl;
            temp = temp->next;
        }
    }

    void searchBook(int id) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Book Found: Title: " << temp->title << ", Author: " << temp->author << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    void removeBook(int id) {
        if (!head) {
            cout << "Library is empty.\n";
            return;
        }
        if (head->id == id) {
            Book* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Book removed.\n";
            return;
        }

        Book* current = head;
        Book* prev = nullptr;
        while (current && current->id != id) {
            prev = current;
            current = current->next;
        }

        if (!current) {
            cout << "Book not found.\n";
        } else {
            prev->next = current->next;
            delete current;
            cout << "Book removed.\n";
        }
    }
};

int main() {
    Library lib;
    int choice, id;
    string title, author;

    do {
        cout << "\nLibrary Management System:\n";
        cout << "1. Add Book\n2. Display Books\n3. Search Book\n4. Remove Book\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Book ID, Title, Author: ";
                cin >> id;
                cin.ignore();
                getline(cin, title);
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                lib.displayBooks();
                break;
            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;
                lib.searchBook(id);
                break;
            case 4:
                cout << "Enter Book ID to remove: ";
                cin >> id;
                lib.removeBook(id);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 5);

    return 0;
}
