#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
#define NOMINMAX
#include <windows.h> 
using namespace std;

// Клас «Нерухомість»
class Nerukhomist
{
private:
    string name;
    double area;
    string rentEnd;

public:
    // Конструктор ініціалізації з параметрами
    Nerukhomist(string n, double a, string r) : name(n), area(a), rentEnd(r) {}

    // Метод для введення/зміни даних користувачем
    void Input()
    {
        cout << "\n\n- Введіть назву нерухомості: ";
        getline(cin, name);

        // Введення площі з обробкою винятків
        while (true) {
            cout << "- Введіть площу (м2): ";
            try {
                cin >> area;
                if (cin.fail() || area <= 0) {
                    throw runtime_error("Площа повинна бути додатнім дійсним числом.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Помилка вводу", MB_OK | MB_ICONERROR);
            }
        }

        // Введення дати з обробкою винятків
        while (true) {
            cout << "- Введіть дату завершення договору (РРРР-ММ-ДД): ";
            try {
                cin >> rentEnd;
                if (rentEnd.length() != 10 || rentEnd[4] != '-' || rentEnd[7] != '-') {
                    throw runtime_error("Неправильний формат дати. Очікується РРРР-ММ-ДД.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break; 
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Помилка вводу", MB_OK | MB_ICONERROR);
            }
        }
    }

    // Метод для виведення вмісту об'єкту на екран
    void Output() const
    {
        cout << fixed << setprecision(2);
        cout << "\n Назва - " << name
            << "\n Площа - " << area << " м2"
            << "\n Договір до - " << rentEnd;
    }

    // Метод для обчислення суми продажу
    double calculateSalePrice(double pricePerSqm) const
    {
        if (pricePerSqm <= 0) {
            throw runtime_error("Ціна за квадратний метр має бути додатною.");
        }
        return area * pricePerSqm;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Nerukhomist myRealEstate("Квартира в с. Нові Кривотули", 75.5, "2026-05-20");

    cout << "== Початкові дані об'єкта 'Нерухомість':" << endl;
    myRealEstate.Output();

    myRealEstate.Input();

    cout << "\n\n== Оновлені дані об'єкта 'Нерухомість':" << endl;
    myRealEstate.Output();

    while (true) {
        try {
            double price_input;
            cout << "\n\nВведіть ціну за м2 для розрахунку вартості: ";
            cin >> price_input;
            if (cin.fail()) {
                throw runtime_error("Ціна повинна бути числом.");
            }
            double totalPrice = myRealEstate.calculateSalePrice(price_input);
            cout << "Орієнтовна вартість продажу: "
                << fixed << setprecision(2) << totalPrice << " USDT " << endl;
            break;
        }
        catch (const runtime_error& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            MessageBoxA(NULL, e.what(), "Помилка розрахунку", MB_OK | MB_ICONERROR);
        }
    }

    cout << endl << endl;
    system("pause");
    return 0;
}