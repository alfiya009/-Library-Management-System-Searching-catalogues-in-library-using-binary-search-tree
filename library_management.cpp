// Due to the large and complex nature of the Java code, this is a partial C++ translation to get you started.
// It implements the basic structure: Student class, BST for book catalog, and skeleton for admin and user login.

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    string name;
    int id_no;
    string stream;
    string book1, book2;
    int book_no = 0;

    Student(string n, int id, string s) : name(n), id_no(id), stream(s) {}
};

struct Node {
    string key;
    Node *left, *right;
    Node(string val) : key(val), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;

    Node* insertRec(Node* root, string key) {
        if (!root) return new Node(key);
        if (key < root->key) root->left = insertRec(root->left, key);
        else if (key > root->key) root->right = insertRec(root->right, key);
        return root;
    }

    bool containsRec(Node* root, string key) {
        if (!root) return false;
        if (key == root->key) return true;
        return key < root->key ? containsRec(root->left, key) : containsRec(root->right, key);
    }

    void inorderRec(Node* root) {
        if (!root) return;
        inorderRec(root->left);
        cout << root->key << " ";
        inorderRec(root->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(string key) {
        root = insertRec(root, key);
    }

    bool contains(string key) {
        return containsRec(root, key);
    }

    void printInOrder() {
        inorderRec(root);
        cout << endl;
    }
};

int main() {
    vector<Student> students = {
        Student("Rajvi", 1741078, "B.Tech-ICT"),
        Student("Krushna", 1741086, "B.Tech-ICT"),
        Student("Kalagee", 1741052, "B.Tech-ICT")
    };

    BST bookTree;
    map<string, pair<int, int>> bookInventory; // book -> {total, available}

    string admin_id = "dsa@1", admin_pwd = "abc123";
    int choice;

    while (true) {
        cout << "\n1. Librarian Login\n2. User Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string uid, pwd;
            cout << "Enter UserId: "; cin >> uid;
            cout << "Enter Password: "; cin >> pwd;

            if (uid == admin_id && pwd == admin_pwd) {
                cout << "Login successful\n";
                int opt;
                while (true) {
                    cout << "\n1. Add Book\n2. Delete Book\n3. View Books\n4. Exit\nEnter choice: ";
                    cin >> opt;
                    if (opt == 1) {
                        string name;
                        int qty;
                        cout << "Book name: "; cin >> name;
                        cout << "Quantity: "; cin >> qty;
                        bookTree.insert(name);
                        bookInventory[name] = {qty, qty};
                    } else if (opt == 3) {
                        for (auto& b : bookInventory) {
                            cout << "Book: " << b.first << ", Total: " << b.second.first << ", Available: " << b.second.second << endl;
                        }
                    } else if (opt == 4) break;
                }
            } else {
                cout << "Invalid credentials.\n";
            }

        } else if (choice == 2) {
            int id; string book;
            cout << "Enter Student ID: "; cin >> id;
            auto it = find_if(students.begin(), students.end(), [&](Student& s) { return s.id_no == id; });

            if (it != students.end()) {
                cout << "Enter book name to issue: "; cin >> book;
                if (bookTree.contains(book) && bookInventory[book].second > 0) {
                    if (it->book_no < 2) {
                        (it->book1.empty() ? it->book1 : it->book2) = book;
                        it->book_no++;
                        bookInventory[book].second--;
                        cout << "Book issued successfully.\n";
                    } else cout << "Can't issue more than 2 books.\n";
                } else cout << "Book unavailable.\n";
            } else {
                cout << "Invalid ID.\n";
            }

        } else if (choice == 3) break;
    }

    return 0;
}
