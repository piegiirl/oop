#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>

class Base
{
protected:
    int value;

public:
    Base() : value(rand() % 100)
    {
        std::cout << "Вызван конструктор базового класса. Значение: " << value << std::endl;
    }

    virtual ~Base()
    {
        std::cout << "Вызван деструктор базового класса. Значение: " << value << std::endl;
    }

    virtual void showInfo() const
    {
        std::cout << "Базовый класс со значением: " << value << std::endl;
    }

    virtual Base *clone() const
    {
        return new Base(*this);
    }
};

class Derived : public Base
{
    std::string name;

public:
    Derived() : name("Объект-" + std::to_string(rand() % 1000))
    {
        std::cout << "Вызван конструктор производного класса. Имя: " << name << std::endl;
    }

    ~Derived() override
    {
        std::cout << "Вызван деструктор производного класса. Имя: " << name << std::endl;
    }

    void showInfo() const override
    {
        std::cout << "Производный класс со значением: " << value << " и именем: " << name << std::endl;
    }

    Base *clone() const override
    {
        return new Derived(*this);
    }
};

class Storage
{
    std::vector<std::unique_ptr<Base>> objects;

public:
    void add(Base *obj)
    {
        objects.push_back(std::unique_ptr<Base>(obj));
    }

    size_t size() const
    {
        return objects.size();
    }

    void showAll() const
    {
        for (const auto &obj : objects)
        {
            obj->showInfo();
        }
    }
};

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    Storage storage;

    const int numObjects = 5;
    std::cout << "\nСоздание объектов:\n";
    for (int i = 0; i < numObjects; ++i)
    {
        Base *obj;
        if (rand() % 2 == 0)
        {
            obj = new Base();
        }
        else
        {
            obj = new Derived();
        }
        storage.add(obj->clone());
        delete obj;
    }

    storage.showAll();

    return 0;
}
