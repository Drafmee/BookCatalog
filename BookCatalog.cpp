#include <iostream>
#include <vector>
#include <string>

class Author {
public:
    Author(const std::string& name, int birthYear) : name(name), birthYear(birthYear) {}

    void displayInfo() {
        std::cout << "Author: " << name << ", Birth Year: " << birthYear << std::endl;
    }

    void changeName(const std::string& newName) {
        name = newName;
    }

    void changeBirthYear(int newYear) {
        birthYear = newYear;
    }
    const std::string& getAuthorName() {
        return name;
    }
    const int getAuthorBirthYear(){
        return birthYear;
    }
private:
    std::string name;
    int birthYear;
};

class Book {
public:
    Book(const std::string& title, int year, Author* author) : title(title), year(year){
        this->addAuthor(author);
    }

    void changeTitle(const std::string& newTitle) {
        title = newTitle;
    }

    void changeYear(int newYear) {
        year = newYear;
    }

    void changeAuthor(Author* authorToRemove, Author* newAuthor) {
        for (auto it = authors.begin(); it != authors.end(); ++it) {
            if (*it == authorToRemove) {
                *it = newAuthor;
                break;
            }
        }       
    }

    void addAuthor(Author* newAuthor) {
        authors.push_back(newAuthor);
    }

    void removeAuthor(Author* authorToRemove) {
        for (auto it = authors.begin(); it != authors.end(); ++it) {
            if (*it == authorToRemove) {
                authors.erase(it);
                break;
            }
        }
    }

    const std::string& getTitle() {
        return title;
    }

    const std::vector<Author*>& getAuthors() {
        return authors;
    }
    const int getBookYear() {
        return year;
    }

private:
    std::string title;
    int year;
    std::vector<Author*> authors;
};

class Library {
public:
    void addBook(Book* book) {
        books.push_back(book);

    }

    void removeBook(Book* book) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (*it == book) {
                books.erase(it);
                break;
            }
        }
    }

    void addAuthor(Book* book, Author* author) {
        book->addAuthor(author);
    }

    void changeAuthor(Book* book, Author* authorToRemove, Author* newAuthor) {
        book->changeAuthor(authorToRemove, newAuthor);
    }



   void removeAuthor2(Author* author) {
       std::vector<Book*> booksToRemove;

       for (auto it = books.begin(); it != books.end(); ) {
           bool authorFound = false;
           std::vector<Author*> authors = (*it)->getAuthors();
           // Remove the author from the book
           for (auto it1 = authors.begin(); it1 != authors.end(); ) {
               if (*it1 == author) {
                   it1 = authors.erase(it1); 
                   authorFound = true;
               }
               else {
                   ++it1;
               }
           }
           // Remove the book if the author was found
           if (authorFound) {
               booksToRemove.push_back(*it);
               it = books.erase(it); 
           }
           else {
               ++it;
           }
       }

       // Delete the books to remove
       for (Book* book : booksToRemove) {
           delete book;
       }

       // Finally, delete the author
       delete author;
   }



   
    void showBooks() {
        for (const auto& book : books) {
            std::cout << "Book Title: " << book->getTitle() << std::endl;
            std::cout << "Authors: ";
            for (const auto& author : book->getAuthors()) {
                std::cout << author->getAuthorName() << " ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }

    void findBooksByAuthor(const std::string& authorName) {
        std::vector<Book*> booksByAuthor;
        for (const auto& book : books) {
            for (const auto& author : book->getAuthors()) {
                if (author->getAuthorName() == authorName) {
                    booksByAuthor.push_back(book);
                    break;
                }
            }
        }
        for (const auto& book : booksByAuthor) {
            std::cout << "Book Title: " << book->getTitle() << std::endl;          
        }
    }

    void ChangeBookTitle(Book* book, const std::string& NewTitle) {
        book->changeTitle(NewTitle);
    }

    void ChangeBookYear(Book* book, const int NewYear) {
        book->changeYear(NewYear);
    }

private:
    std::vector<Book*> books;    
};

int main() {
    //Create Library
    Library library;
    //Create some authors
    Author* authorX = new Author("X", 1980);
    Author* authorY = new Author("Y", 1975);
    Author* authorZ = new Author("Z", 1990);

    //Create some books
    Book* bookA = new Book ("A", 2000, authorX);
    Book* bookB = new Book("B", 2005, authorY);
    Book* bookC = new Book("C", 2010, authorZ);

    //Add books to Library
    library.addBook(bookA);
    library.addBook(bookB);
    library.addBook(bookC);
    
    //Changing author of book A from X to Y
    library.changeAuthor(bookA, authorX, authorY);
  
    //Changing book B title
    library.ChangeBookTitle(bookB, "New Title B");

    //Create 5 books of author Z 2 of wich in coop with author Y
    for (int i = 0; i < 5; i++) {
        Book* newBook = new Book("New Book " + std::to_string(i), 2022, authorZ);
        if (i < 2) {
            newBook->addAuthor(authorY);
        }
        library.addBook(newBook);
    }
    //showing all Books 
    library.showBooks();
   
   
    //Removing author Z
    library.removeAuthor2(authorZ); 
    
    

   library.showBooks();

   

}