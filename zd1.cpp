#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
#define NOMINMAX
#include <windows.h> 
using namespace std;

class Nerukhomist
{
private:
    string name;
    double area;
    string rentEnd;

public:
    Nerukhomist(string n, double a, string r) : name(n), area(a), rentEnd(r) {}

    void Input()
    {
        cout << "\n\n- Ââåä³òü íàçâó íåðóõîìîñò³: ";
        getline(cin, name);

        while (true) {
            cout << "- Ââåä³òü ïëîùó (ì2): ";
            try {
                cin >> area;
                if (cin.fail() || area <= 0) {
                    throw runtime_error("Ïëîùà ïîâèííà áóòè äîäàòí³ì ä³éñíèì ÷èñëîì.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Ïîìèëêà ââîäó", MB_OK | MB_ICONERROR);
            }
        }

        while (true) {
            cout << "- Ââåä³òü äàòó çàâåðøåííÿ äîãîâîðó (ÐÐÐÐ-ÌÌ-ÄÄ): ";
            try {
                cin >> rentEnd;
                if (rentEnd.length() != 10 || rentEnd[4] != '-' || rentEnd[7] != '-') {
                    throw runtime_error("Íåïðàâèëüíèé ôîðìàò äàòè. Î÷³êóºòüñÿ ÐÐÐÐ-ÌÌ-ÄÄ.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break; 
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Ïîìèëêà ââîäó", MB_OK | MB_ICONERROR);
            }
        }
    }

    void Output() const
    {
        cout << fixed << setprecision(2);
        cout << "\n Íàçâà - " << name
            << "\n Ïëîùà - " << area << " ì2"
            << "\n Äîãîâ³ð äî - " << rentEnd;
    }

    double calculateSalePrice(double pricePerSqm) const
    {
        if (pricePerSqm <= 0) {
            throw runtime_error("Ö³íà çà êâàäðàòíèé ìåòð ìàº áóòè äîäàòíîþ.");
        }
        return area * pricePerSqm;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Nerukhomist myRealEstate("Êâàðòèðà â ñ. Íîâ³ Êðèâîòóëè", 75.5, "2026-05-20");

    cout << "== Ïî÷àòêîâ³ äàí³ îá'ºêòà 'Íåðóõîì³ñòü':" << endl;
    myRealEstate.Output();

    myRealEstate.Input();

    cout << "\n\n== Îíîâëåí³ äàí³ îá'ºêòà 'Íåðóõîì³ñòü':" << endl;
    myRealEstate.Output();

    while (true) {
        try {
            double price_input;
            cout << "\n\nÂâåä³òü ö³íó çà ì2 äëÿ ðîçðàõóíêó âàðòîñò³: ";
            cin >> price_input;
            if (cin.fail()) {
                throw runtime_error("Ö³íà ïîâèííà áóòè ÷èñëîì.");
            }
            double totalPrice = myRealEstate.calculateSalePrice(price_input);
            cout << "Îð³ºíòîâíà âàðò³ñòü ïðîäàæó: "
                << fixed << setprecision(2) << totalPrice << " USDT " << endl;
            break;
        }
        catch (const runtime_error& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            MessageBoxA(NULL, e.what(), "Ïîìèëêà ðîçðàõóíêó", MB_OK | MB_ICONERROR);
        }
    }

    cout << endl << endl;
    system("pause");
    return 0;

}
