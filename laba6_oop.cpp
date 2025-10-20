#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
#define NOMINMAX
#include <windows.h> 
using namespace std;

// ���� ������������
class Nerukhomist
{
private:
    string name;
    double area;
    string rentEnd;

public:
    // ����������� ����������� � �����������
    Nerukhomist(string n, double a, string r) : name(n), area(a), rentEnd(r) {}

    // ����� ��� ��������/���� ����� ������������
    void Input()
    {
        cout << "\n\n- ������ ����� ����������: ";
        getline(cin, name);

        // �������� ����� � �������� �������
        while (true) {
            cout << "- ������ ����� (�2): ";
            try {
                cin >> area;
                if (cin.fail() || area <= 0) {
                    throw runtime_error("����� ������� ���� ������� ������ ������.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "������� �����", MB_OK | MB_ICONERROR);
            }
        }

        // �������� ���� � �������� �������
        while (true) {
            cout << "- ������ ���� ���������� �������� (����-��-��): ";
            try {
                cin >> rentEnd;
                if (rentEnd.length() != 10 || rentEnd[4] != '-' || rentEnd[7] != '-') {
                    throw runtime_error("������������ ������ ����. ��������� ����-��-��.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break; 
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "������� �����", MB_OK | MB_ICONERROR);
            }
        }
    }

    // ����� ��� ��������� ����� ��'���� �� �����
    void Output() const
    {
        cout << fixed << setprecision(2);
        cout << "\n ����� - " << name
            << "\n ����� - " << area << " �2"
            << "\n ������ �� - " << rentEnd;
    }

    // ����� ��� ���������� ���� �������
    double calculateSalePrice(double pricePerSqm) const
    {
        if (pricePerSqm <= 0) {
            throw runtime_error("ֳ�� �� ���������� ���� �� ���� ��������.");
        }
        return area * pricePerSqm;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Nerukhomist myRealEstate("�������� � �. ��� ���������", 75.5, "2026-05-20");

    cout << "== �������� ��� ��'���� '����������':" << endl;
    myRealEstate.Output();

    myRealEstate.Input();

    cout << "\n\n== ������� ��� ��'���� '����������':" << endl;
    myRealEstate.Output();

    while (true) {
        try {
            double price_input;
            cout << "\n\n������ ���� �� �2 ��� ���������� �������: ";
            cin >> price_input;
            if (cin.fail()) {
                throw runtime_error("ֳ�� ������� ���� ������.");
            }
            double totalPrice = myRealEstate.calculateSalePrice(price_input);
            cout << "�������� ������� �������: "
                << fixed << setprecision(2) << totalPrice << " USDT " << endl;
            break;
        }
        catch (const runtime_error& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            MessageBoxA(NULL, e.what(), "������� ����������", MB_OK | MB_ICONERROR);
        }
    }

    cout << endl << endl;
    system("pause");
    return 0;
}