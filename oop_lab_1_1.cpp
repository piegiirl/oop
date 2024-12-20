#include <iostream>
#include <random>
using namespace std;

int main()
{
    cout << "Введите длину массива n: ";
    int n;
    cin >> n;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);
    cout << "Полученный массив: ";
    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
    {
        arr[i] = dist(gen);
        cout << arr[i] << ' ';
    }
    cout << endl;
    // Вывод адреса начала массива
    intptr_t base_address = reinterpret_cast<intptr_t>(&arr[0]);
    cout << "Адрес начала массива: " << &arr[0] << endl;
    // Вывод расстояния каждого элемента от начала массива
    cout << "Расстояние каждого элемента от начала массива с кастами:" << endl;
    for (int i = 0; i < n; ++i)
    {
        intptr_t element_address = reinterpret_cast<intptr_t>(&arr[i]);
        cout << "Элемент " << i << ": адрес = " << &arr[i] << ", расстояние = " << (element_address - base_address) << " байт" << endl;
    }
    cout << "Расстояние каждого элемента от начала массива без кастов:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Элемент " << i << ": адрес = " << &arr[i] << ", расстояние = " << (sizeof arr[0])*(&arr[i] - &arr[0]) << " байт" << endl;
    }
    delete[] arr;
    return 0;
}
