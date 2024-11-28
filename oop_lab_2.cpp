#include <iostream>
#include <string>
using namespace std;

class Publication
{
protected:
    string title;
    float price;

public:
    void getdata()
    {
        cout << "Введите название: ";
        cin.clear();
        getline(cin, title);
        cout << "Введите цену: ";
        cin >> price;
    }
    void putdata() const
    {
        cout << "Название: " << title << endl;
        cout << "Цена: " << price << endl;
    }
    string getTitle() const
    {
        return title;
    }
};
class Sales
{
protected:
    float sales[3];

public:
    void getdata()
    {
        for (int i = 0; i < 3; ++i)
        {
            cout << "Введите продажу за " << i + 1 << "-й месяц: ";
            cin >> sales[i];
        }
    }
    void putdata() const
    {
        for (int i = 0; i < 3; ++i)
        {
            cout << "Продажи за " << i + 1 << "-й месяц: " << sales[i] << endl;
        }
    }
};
class Book : public Publication, public Sales
{
private:
    int pageCount;

public:
    void getdata()
    {
        Publication::getdata();
        cout << "Введите количество страниц: ";
        cin >> pageCount;
        Sales::getdata();
    }
    void putdata() const
    {
        Publication::putdata();
        cout << "Количество страниц: " << pageCount << endl;
        Sales::putdata();
    }
};
class Type : public Publication, public Sales
{
private:
    float playTime;

public:
    void getdata()
    {
        Publication::getdata();
        cout << "Введите время записи в минутах: ";
        cin >> playTime;
        Sales::getdata();
    }
    void putdata() const
    {
        Publication::putdata();
        cout << "Время записи: " << playTime << " минут" << endl;
        Sales::putdata();
    }
    float getPlayTime() const
    {
        return playTime;
    }
};
bool isAudioMatchingBook(const Book &book, const Type &type)
{
    return book.getTitle() == type.getTitle();
}
int main()
{
    Book myBook;
    Type myType;
    system("chcp 1251");
    cout << "Введите данные для книги:" << endl;
    myBook.getdata();
    cin.ignore(); // Добавлено для очистки буфера перед вводом данных для аудиозаписи

    cout << "\nВведите данные для аудио записи:" << endl;
    myType.getdata();
    cout << "\nВывод данных о книге:" << endl;
    myBook.putdata();
    cout << "\nВывод данных о аудио записи:" << endl;
    myType.putdata();
    if (isAudioMatchingBook(myBook, myType))
    {
        cout << "\nАудио соответствует книге." << endl;
    }
    else
    {
        cout << "\nАудио не соответствует книге." << endl;
    }
    return 0;
}
