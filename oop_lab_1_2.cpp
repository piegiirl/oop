#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Перечисляемый тип для определения типа книги
enum BookType
{
    Fiction,  // Художественная книга
    Technical // Техническая книга
};
// Класс для хранения информации о книге
class Book
{
public:
    // Конструктор с параметрами
    Book(string authorName, string bookTitle, BookType bookType)
    {
        // Проверяем, чтобы имя автора и название книги не были пустыми
        if (authorName.empty() || bookTitle.empty())
        {
            throw invalid_argument("The author's name and book title must not be empty.");
        }
        author = authorName;
        title = bookTitle;
        type = bookType;
    }
    // Метод для получения типа книги
    BookType getType()
    {
        return type;
    }

private:
    string author;
    string title;
    BookType type;
};
// Класс для управления библиотекой
class Library
{
private:
    vector<Book> books; // Вектор для хранения книг
public:
    // Метод для добавления книги в библиотеку
    void addBook(Book book)
    {
        books.push_back(book);
    }
    // Метод для вывода количества книг каждого типа
    void showBookCounts()
    {
        int fictionCount = 0;
        int technicalCount = 0;
        // Проходим по всем книгам и считаем количество каждого типа
        for (Book book : books)
        {
            switch (book.getType())
            {
            case Fiction:
                fictionCount++;
                break;
            case Technical:
                technicalCount++;
                break;
            }
        }
        // Выводим результат
        cout << "Number of fiction books: " << fictionCount << endl;
        cout << "Number of technical books:" << technicalCount << endl;
    }
};
int main()
{
    try
    {
        Library library; // Создаем объект библиотеки

        // Добавляем книги в библиотеку
        library.addBook(Book("Leo Tolstoy", "War and Peace", Fiction));
        library.addBook(Book("F. M. Dostoevsky", "Idiot", Fiction));
        library.addBook(Book("Kernighan and Ritchie", "C Programming Language", Technical));
        // Вызываем метод для вывода количества книг
        library.showBookCounts();
    }
    catch (exception &err)
    {
        cout << "Error: " << err.what() << endl;
    }
    return 0;
}
