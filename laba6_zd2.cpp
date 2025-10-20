#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
#define NOMINMAX
#include <windows.h>

using namespace std;

class RealEstate
{
private:
    string address;
    double area;
    int roomCount;
    bool isCommercial;
    double price;
    string ownerName;
    int yearBuilt;

public:
    // Конструктор
    RealEstate() : area(0), roomCount(0), isCommercial(false), price(0), yearBuilt(0) {}

    void Input()
    {
        cout << "\n--- Початок введення даних про об'єкт ---\n";

        // Адреса
        cout << "Введіть адресу: ";
        getline(cin, address);
        if (address.empty()) {
            throw runtime_error("Адреса не може бути порожньою.");
        }

        // Площа
        while (true) {
            cout << "Введіть площу (м2): ";
            try {
                cin >> area;
                if (cin.fail() || area <= 0) {
                    throw runtime_error("Площа повинна бути додатнім дійсним числом.");
                }
                break;
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Помилка вводу", MB_OK | MB_ICONERROR);
            }
        }

        // Кількість кімнат
        while (true) {
            cout << "Введіть кількість кімнат: ";
            try {
                cin >> roomCount;
                if (cin.fail() || roomCount <= 0) {
                    throw runtime_error("Кількість кімнат повинна бути додатнім цілим числом.");
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

        // Тип нерухомості
        while (true) {
            cout << "Це комерційна нерухомість? (1 - так, 0 - ні): ";
            try {
                int commercialInput;
                cin >> commercialInput;
                if (cin.fail() || (commercialInput != 0 && commercialInput != 1)) {
                    throw runtime_error("Введіть 1 (так) або 0 (ні).");
                }
                isCommercial = (commercialInput == 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Помилка вводу", MB_OK | MB_ICONERROR);
            }
        }

        // Ціна
        while (true) {
            cout << "Введіть ціну (в $): ";
            try {
                cin >> price;
                if (cin.fail() || price <= 0) {
                    throw runtime_error("Ціна повинна бути додатнім числом.");
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

        // Ім'я власника
        cout << "Введіть ім'я власника: ";
        getline(cin, ownerName);
        if (ownerName.empty()) {
            throw runtime_error("Ім'я власника не може бути порожнім.");
        }

        // Рік побудови
        while (true) {
            cout << "Введіть рік побудови: ";
            try {
                cin >> yearBuilt;
                if (cin.fail() || yearBuilt < 1800 || yearBuilt > 2025) {
                    throw runtime_error("Рік побудови має бути реалістичним (напр., 1800-2025).");
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
        cout << "\n--- Об'єкт нерухомості ---\n"
            << "Адреса: " << address << "\n"
            << "Власник: " << ownerName << "\n"
            << "Тип: " << (isCommercial ? "Комерційна" : "Житлова") << "\n"
            << "Площа: " << fixed << setprecision(2) << area << " м2\n"
            << "Кількість кімнат: " << roomCount << "\n"
            << "Рік побудови: " << yearBuilt << "\n"
            << "Вартість: $" << fixed << setprecision(2) << price << "\n"
            << "---------------------------------\n";
    }

    // Метод для оновлення ціни на вказаний відсоток
    void updatePrice(double percentage)
    {
        if (percentage < -100) {
            cout << "ПОМИЛКА: Неможливо зменшити ціну більше ніж на 100%.\n";
            return;
        }
        double changeFactor = 1.0 + (percentage / 100.0);
        price *= changeFactor;
        cout << "\n Ціну успішно " << (percentage >= 0 ? "збільшено" : "зменшено")
            << " на " << abs(percentage) << "%.\n";
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 1. Створити об'єкт розробленого класу
    RealEstate myProperty;

    // 2. Забезпечити ввід даних
    myProperty.Input();

    cout << "\nОб'єкт успішно створено. Початкові дані:";
    myProperty.Output();

    // 3. Провести дії, представлені розробленим методом
    double percentage = 0;
    cout << "\n--- Дія: Оновлення ціни ---\n";

    // Окремий блок валідації для вводу відсотка
    while (true) {
        cout << "Введіть відсоток, на який треба змінити ціну (напр., 10 або -5): ";
        try {
            cin >> percentage;
            if (cin.fail()) {
                throw runtime_error("Відсоток має бути числом.");
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

    myProperty.updatePrice(percentage);

    // 4. Вивести результати на екран
    cout << "Оновлені дані об'єкта:";
    myProperty.Output();

    cout << endl;
    system("pause");
    return 0;
}