# Library Management System
A console-based application developed in C++ to handle essential library operations. This system manages book records and user details using custom data structures and manual memory management.

## Overview
This project implements a dynamic storage system where the size of the database (books and users) adjusts automatically at runtime. Instead of using standard containers like `std::vector`, this system uses raw pointers and dynamic arrays (`new` and `delete`) to demonstrate a deeper understanding of memory allocation and pointer arithmetic in C++.

## Features
### Book Management
* **Add Books:** Input details including ID, title, and author.
* **Search:** Find books by ID.
* **Update & Delete:** Modify existing records or remove them from the system.
* **Dynamic Resizing:** The array grows automatically as new books are added.

### User & Circulation
* **User Registration:** Register members with unique IDs.
* **Issue Books:** Link a specific book ID to a user ID, updating availability status.
* **Return Books:** Process returns and calculate fines for overdue items.

### File Handling
* **Data Persistence:** All records are saved to `books.txt` and `users.txt` upon request.
* **Load Functionality:** Data can be reloaded from files into the system memory, restoring the previous state.

## Technical Details
* **Language:** C++
* **Memory Management:** Manual dynamic allocation (Heap memory).
* **Data Structures:** Structs for `BookItem` and `Member`.
* **File I/O:** Usage of `fstream` for reading and writing text files.

## How to Run
1.  Clone the repository or download the source code.
2.  Compile the program using a C++ compiler (e.g., g++):
    ```bash
    g++ main.cpp -o library_system
    ```
3.  Run the executable:
    ```bash
    ./library_system
    ```

## Usage Note
Ensure that `books.txt` and `users.txt` are in the same directory as the executable if you are loading existing data. If the files do not exist, the program will create them when you save for the first time.
