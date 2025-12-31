#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct BookItem {
    int b_id;
    string b_title;
    string b_author;
    bool available;
};

struct Member {
    int m_id;
    string m_name;
    int book_held_id; 
};

BookItem* book_arr = nullptr;
Member* member_arr = nullptr;
int n_books = 0;
int n_members = 0;

int getBookIdx(int id) {
    for (int i = 0; i < n_books; i++) {
        if (book_arr[i].b_id == id) return i;
    }
    return -1;
}

int getMemberIdx(int id) {
    for (int i = 0; i < n_members; i++) {
        if (member_arr[i].m_id == id) return i;
    }
    return -1;
}

void expandBookArr(int new_size) {
    BookItem* temp = new BookItem[new_size];
    int limit = (new_size < n_books) ? new_size : n_books;
    
    for (int i = 0; i < limit; i++) {
        temp[i] = book_arr[i];
    }
    
    if (book_arr != nullptr) {
        delete[] book_arr;
    }
    book_arr = temp;
}

void expandMemberArr(int new_size) {
    Member* temp = new Member[new_size];
    int limit = (new_size < n_members) ? new_size : n_members;

    for (int i = 0; i < limit; i++) {
        temp[i] = member_arr[i];
    }

    if (member_arr != nullptr) {
        delete[] member_arr;
    }
    member_arr = temp;
}

void save_data() {
    ofstream f_book("books.txt");
    for (int i = 0; i < n_books; i++) {
        f_book << book_arr[i].b_id << "|" << book_arr[i].b_title << "|" 
               << book_arr[i].b_author << "|" << book_arr[i].available << endl;
    }
    f_book.close();

    ofstream f_mem("users.txt");
    for (int i = 0; i < n_members; i++) {
        f_mem << member_arr[i].m_id << "|" << member_arr[i].m_name << "|" 
              << member_arr[i].book_held_id << endl;
    }
    f_mem.close();
    cout << "Data saved successfully.\n";
}

void load_and_view() {
    ifstream f_book("books.txt");
    if (f_book) {
        delete[] book_arr; 
        book_arr = nullptr;
        n_books = 0;
        
        int id; 
        string t, a, av, junk;
        
        while (f_book >> id) {
            getline(f_book, junk, '|');
            getline(f_book, t, '|');
            getline(f_book, a, '|');
            f_book >> av;
            
            expandBookArr(n_books + 1);
            book_arr[n_books].b_id = id;
            book_arr[n_books].b_title = t;
            book_arr[n_books].b_author = a;
            book_arr[n_books].available = (av == "1");
            n_books++;
        }
    }
    f_book.close();

    ifstream f_mem("users.txt");
    if (f_mem) {
        delete[] member_arr; 
        member_arr = nullptr;
        n_members = 0;

        int mid, held; 
        string name, junk;
        
        while (f_mem >> mid) {
            getline(f_mem, junk, '|');
            getline(f_mem, name, '|');
            f_mem >> held;

            expandMemberArr(n_members + 1);
            member_arr[n_members].m_id = mid;
            member_arr[n_members].m_name = name;
            member_arr[n_members].book_held_id = held;
            n_members++;
        }
    }
    f_mem.close();
    
    cout << "\n--- DATA LOADED FROM FILE ---\n";
    cout << "[BOOKS]\n";
    for(int i = 0; i < n_books; i++) {
        cout << "ID: " << book_arr[i].b_id << " | " << book_arr[i].b_title 
             << " | " << (book_arr[i].available ? "Available" : "Issued") << endl;
    }
    
    cout << "\n[USERS]\n";
    for(int i = 0; i < n_members; i++) {
        cout << "ID: " << member_arr[i].m_id << " | Name: " << member_arr[i].m_name 
             << " | Book Issued: " << member_arr[i].book_held_id << endl;
    }
    cout << "-----------------------------\n";
}

void add_new_book() {
    int id;
    cout << "Enter Book ID: "; cin >> id;
    if (getBookIdx(id) != -1) { 
        cout << "ID already exists.\n"; 
        return; 
    }

    expandBookArr(n_books + 1);
    
    book_arr[n_books].b_id = id;
    cin.ignore(); 
    cout << "Title: "; getline(cin, book_arr[n_books].b_title);
    cout << "Author: "; getline(cin, book_arr[n_books].b_author);
    book_arr[n_books].available = true;
    
    cout << "Book added.\n";
    n_books++;
}

void edit_book() {
    int id; 
    cout << "Enter Book ID to update: "; cin >> id;
    int idx = getBookIdx(id);
    
    if (idx == -1) { 
        cout << "Not found.\n"; 
        return; 
    }

    cin.ignore();
    cout << "New Title: "; getline(cin, book_arr[idx].b_title);
    cout << "New Author: "; getline(cin, book_arr[idx].b_author);
    cout << "Details updated.\n";
}

void remove_book() {
    int id; 
    cout << "Enter Book ID to delete: "; cin >> id;
    int idx = getBookIdx(id);
    
    if (idx == -1) { 
        cout << "Not found.\n"; 
        return; 
    }

    BookItem* temp = new BookItem[n_books - 1];
    int k = 0;
    for (int i = 0; i < n_books; i++) {
        if (i == idx) continue;
        temp[k++] = book_arr[i];
    }
    
    delete[] book_arr;
    book_arr = temp;
    n_books--;
    cout << "Book deleted.\n";
}

void find_book() {
    int id; 
    cout << "Enter Book ID: "; cin >> id;
    int idx = getBookIdx(id);
    
    if (idx != -1) {
        cout << "Found: " << book_arr[idx].b_title << " by " << book_arr[idx].b_author << endl;
    } else {
        cout << "Not found.\n";
    }
}

void add_member() {
    int id; 
    cout << "User ID: "; cin >> id;
    
    expandMemberArr(n_members + 1);
    member_arr[n_members].m_id = id;
    cin.ignore();
    cout << "Name: "; getline(cin, member_arr[n_members].m_name);
    member_arr[n_members].book_held_id = -1;
    n_members++;
    cout << "User registered.\n";
}

void issue_item() {
    int uid, bid;
    cout << "User ID: "; cin >> uid;
    cout << "Book ID: "; cin >> bid;

    int u_idx = getMemberIdx(uid);
    int b_idx = getBookIdx(bid);

    if (u_idx == -1 || b_idx == -1) { 
        cout << "Invalid IDs.\n"; 
        return; 
    }
    
    if (!book_arr[b_idx].available) { 
        cout << "Book not available.\n"; 
        return; 
    }
    
    if (member_arr[u_idx].book_held_id != -1) { 
        cout << "User already has a book.\n"; 
        return; 
    }

    book_arr[b_idx].available = false;
    member_arr[u_idx].book_held_id = bid;
    cout << "Book issued.\n";
}

void return_item() {
    int uid, bid;
    cout << "User ID: "; cin >> uid;
    cout << "Book ID: "; cin >> bid;

    int u_idx = getMemberIdx(uid);
    int b_idx = getBookIdx(bid);

    if (u_idx != -1 && member_arr[u_idx].book_held_id == bid) {
        int days;
        cout << "Days overdue (0 for none): "; cin >> days;
        if (days > 0) {
            cout << "Fine: $" << days * 2 << endl;
        }

        book_arr[b_idx].available = true;
        member_arr[u_idx].book_held_id = -1;
        cout << "Book returned.\n";
    } else {
        cout << "Error in returning.\n";
    }
}

void show_all() {
    cout << "\n--- Library Books ---\n";
    for (int i = 0; i < n_books; i++) {
        cout << "ID: " << book_arr[i].b_id << " | " << book_arr[i].b_title << " | " 
             << (book_arr[i].available ? "Available" : "Issued") << endl;
    }
}

int main() {
    int op;
    do {
        cout << "\n1. Add Book\n2. Update Book\n3. Delete Book\n4. Search Book\n5. Register User\n6. Issue Book\n7. Return Book\n8. Display All\n9. Save Records\n10. Load Records\n11. Exit\n";
        cout << "Select: ";
        cin >> op;
        switch (op) {
            case 1: add_new_book(); break;
            case 2: edit_book(); break;
            case 3: remove_book(); break;
            case 4: find_book(); break;
            case 5: add_member(); break;
            case 6: issue_item(); break;
            case 7: return_item(); break;
            case 8: show_all(); break;
            case 9: save_data(); break;
            case 10: load_and_view(); break;
            case 11: cout << "Exiting..."; break;
            default: cout << "Invalid.\n";
        }
    } while (op != 11);

    delete[] book_arr;
    delete[] member_arr;
    
    return 0;
}