#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>  
using namespace std;

// Базовый класс - деталь
class Detail
{
protected:
    string name;
    int id;

    // Конструкторы
public:
    Detail(string n, int i) : name(n), id(i) {}
    Detail() : name(""), id(0) {}

    virtual void print() const
    { // Виртуальный метод для полиморфизма
        cout << "Деталь: " << name << " (ID: " << id << ")" << endl;
    }

    virtual ~Detail() {} // Виртуальный деструктор
};

// Производный класс - сборка
class Assembly : public Detail
{
protected:
    int detailsCount;

public:
    // Конструкторы 
    Assembly(string n, int i, int count) : Detail(n, i), detailsCount(count) {}
    Assembly(string n, int i) : Detail(n, i), detailsCount(rand() % 9 + 2) {} // Случайное количество деталей

    void print() const override
    { // Переопределение виртуального метода
        cout << "Сборка: " << name << " (ID: " << id << "), количество деталей: "
             << detailsCount << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian"); 
    srand(static_cast<unsigned>(time(0))); 

    // Создаем вектор указателей на базовый класс
    vector<Detail *> storage;

    // Создаем несколько объектов и добавляем их в вектор
    storage.push_back(new Detail("Шпонка", 1));
    storage.push_back(new Detail("Гребной винт", 2));
    storage.push_back(new Detail("Коленчатый вал", 3));
    storage.push_back(new Assembly("Двигатель", 4)); 

    // Выводим информацию о всех объектах
    cout << "Содержимое хранилища:" << endl;
    for (const auto &item : storage)
    {
        item->print();
    }

    // Освобождаем память
    for (const auto &item : storage)
    {
        delete item;
    }

    return 0;
}
