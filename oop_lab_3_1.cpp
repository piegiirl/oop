#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Базовый класс - деталь
class Detail
{
protected:
    string name;
    int id;
    // конструкторы в protected
    Detail(string n, int i) : name(n), id(i) {}
    Detail() : name(""), id(0) {}
public:
    virtual void print() const
    { // виртуальный метод для полиморфизма
        cout << "Деталь: " << name << " (ID: " << id << ")" << endl;
    }
    virtual ~Detail() {} // виртуальный деструктор
    // шаблонная дружественная функция для создания объектов
    template <typename T>
    friend T *createObject(string n, int i);
};
// Производный класс - сборка
class Assembly : public Detail
{
protected:
    int detailsCount;
    Assembly(string n, int i, int count) : Detail(n, i), detailsCount(count) {}
    Assembly() : Detail(), detailsCount(0) {}
public:
    void print() const override
    { // переопределение виртуального метода
        cout << "Сборка: " << name << " (ID: " << id << "), количество деталей: "
             << detailsCount << endl;
    }
    template <typename T>
    friend T *createObject(string n, int i); // та же дружественная функция
};
// Шаблонная функция для создания объектов
template <typename T>
T *createObject(string n, int i)
{
    if constexpr (is_same_v<T, Detail>)
    {
        return new Detail(n, i);
    }
    else if constexpr (is_same_v<T, Assembly>)
    {
        // для простоты задаем случайное количество деталей от 2 до 10
        return new Assembly(n, i, rand() % 9 + 2);
    }
    return nullptr;
}
int main()
{
    setlocale(LC_ALL, "Russian"); // для русского языка в консоли
    srand(static_cast<unsigned>(time(0)));
    // создаем вектор указателей на базовый класс
    vector<Detail *> storage;
    // создаем несколько объектов и добавляем их в вектор
    storage.push_back(createObject<Detail>("Шпонка", 1));
    storage.push_back(createObject<Detail>("Гребной винт", 2));
    storage.push_back(createObject<Detail>("Коленчатый вал", 3));
    storage.push_back(createObject<Assembly>("Двигатель", 4));
    // выводим информацию о всех объектах
    cout << "Содержимое хранилища:" << endl;
    for (const auto &item : storage)
    {
        item->print();
    }
}
