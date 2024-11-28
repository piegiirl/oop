#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <cmath>

// Базовый класс для всех ошибок доступа
class BaseError
{
public:
    virtual const char *what() const noexcept = 0; // Чисто виртуальная функция
    virtual ~BaseError() {}
};

// Класс для ошибки доступа к памяти
class MemoryError : public BaseError
{
public:
    const char *what() const noexcept override
    {
        return "Ошибка доступа к памяти";
    }
};

// Класс для математической ошибки
class MathError : public BaseError
{
public:
    const char *what() const noexcept override
    {
        return "Математическая ошибка";
    }
};

// Класс для ошибки деления на ноль
class DivisionByZeroError : public MathError
{
public:
    const char *what() const noexcept override
    {
        return "Ошибка: деление на ноль";
    }
};

// Класс для ошибки извлечения квадратного корня из отрицательного числа
class NegativeSquareRootError : public std::runtime_error
{
public:
    NegativeSquareRootError() : std::runtime_error("Ошибка: Извлечение квадратного корня из отрицательного числа") {}
};

// Класс для ошибки переполнения
class OverflowError : public MathError
{
public:
    const char *what() const noexcept override
    {
        return "Ошибка: переполнение";
    }
};

// Шаблонный класс для хранения массива указателей на объекты
template <typename T>
class PointerArray
{
private:
    std::vector<T *> arr; // Вектор для хранения указателей на объекты
public:
    // Конструктор
    PointerArray(size_t size)
    {
        arr.resize(size);
    }

    // Деструктор для очистки памяти
    ~PointerArray()
    {
        clear();
    }

    // Метод для очистки памяти, который можно вызывать при необходимости
    void clear()
    {
        for (auto ptr : arr)
        {
            delete ptr; // Освобождаем память для каждого указателя
        }
        arr.clear(); // Очищаем вектор
    }

    // Оператор [] для доступа к элементам массива
    T *&operator[](size_t index)
    {
        if (index >= arr.size())
        {
            throw std::out_of_range("Индекс вне диапазона!"); // Исключение при выходе за пределы массива
        }
        return arr[index];
    }

    // Метод для получения размера массива
    size_t size() const
    {
        return arr.size();
    }
};

class Divider
{
public:
    double divide(double a, double b)
    {
        if (b == 0)
        {
            throw DivisionByZeroError(); // Если делитель равен 0, вызывается исключение
        }
        return a / b;
    }
};
class SquareRootCalculator
{
public:
    double safeSquareRoot(double a)
    {
        if (a < 0)
        {
            throw NegativeSquareRootError(); // Если число отрицательное, вызывается исключение
        }
        return std::sqrt(a);
    }
};

int main()
{
    setlocale(LC_ALL, "ru-RU");
    Divider divider;
    SquareRootCalculator squareRootCalculator;

    try
    {
        double result1 = divider.divide(10, 0);
        std::cout << "Результат деления: " << result1 << std::endl;
    }
    catch (const DivisionByZeroError &e)
    {
        std::cerr << e.what() << std::endl; // Обработка исключения деления на ноль
    }

    try
    {
        double result3 = squareRootCalculator.safeSquareRoot(-9);
        std::cout << "Квадратный корень: " << result3 << std::endl;
    }
    catch (const NegativeSquareRootError &e)
    {
        std::cerr << e.what() << std::endl; // Обработка исключения извлечения квадратного корня
    }

    // Пример работы с PointerArray
    try
    {
        PointerArray<int> arr(5); // Создаем массив из 5 указателей на int
        arr[0] = new int(10);
        arr[1] = new int(20);
        int value = *arr[5];
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl; // Обработка исключения для PointerArray
    }
    return 0;
}
