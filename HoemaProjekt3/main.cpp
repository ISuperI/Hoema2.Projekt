#include <iostream>
#include "CMyVektor.h"
#include "C_DGLSolver.h"
#include <cmath>
using namespace std;

C_DGLSolver::C_DGLSolver(CMyVektor (*fDGLSystem)(CMyVektor y, double x))
{
    this->fDGLSystem = fDGLSystem;
    hoehere_Ordnung = false;
}

C_DGLSolver::C_DGLSolver(double (*fDGLnterOrdnung)(CMyVektor y, double x))
{
    this->fDGLnterOrdnung = fDGLnterOrdnung;
    hoehere_Ordnung = true;
}

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{
    if (hoehere_Ordnung)
    {
        int dim = y.getDimension();
        CMyVektor ergebnis(dim);
        for (int i = 0; i < dim - 1; i++)
        {
            ergebnis(i) = y(i + 1);
        }
        ergebnis(dim - 1) = fDGLnterOrdnung(y, x);
        return ergebnis;
    }
    else
    {
        return fDGLSystem(y, x);
    }
}
void C_DGLSolver::euler_Verfahren(CMyVektor &y, double x_Start, double x_Ende, int anzahl_Schritte, bool Ausgabe)
{
    double h = (x_Ende - x_Start) / anzahl_Schritte;
    double x = x_Start;

    if (Ausgabe == true)
    {
        cout << "Euler-Verfahren:" << endl;
    }

    for (int i = 0; i <= anzahl_Schritte; i++)
    {
        if (i == anzahl_Schritte)
        {
            if (Ausgabe == true)
            {
                cout << endl
                     << "Ende bei " << endl
                     << "x = " << x << endl
                     << "y = ";
                y.ausgabe();
            }
        }
        else
        {
            CMyVektor y_diff = ableitungen(y, x);

            if (Ausgabe == true)
            {
                cout << endl
                     << "Schritt: " << i << endl
                     << "x = " << x << endl
                     << "y = ";
                y.ausgabe();
                cout << "y' = ";
                y_diff.ausgabe();
            }

            y = y + h * y_diff;
            x += h;
        }
    }
}

void C_DGLSolver::heun_Verfahren(CMyVektor &y, double x_Start, double x_Ende, int anzahl_Schritte, bool Ausgabe)
{
    double h = (x_Ende - x_Start) / anzahl_Schritte;
    double x = x_Start;

    if (Ausgabe == true)
    {
        cout << "Heun-Verfahren:" << endl;
    }

    for (int i = 0; i <= anzahl_Schritte; i++)
    {
        if (i == anzahl_Schritte)
        {
            if (Ausgabe == true)
            {
                cout << endl
                     << "Ende bei " << endl
                     << "x = " << x << endl
                     << "y = ";
                y.ausgabe();
            }
        }
        else
        {
            CMyVektor y_diff = ableitungen(y, x);
            CMyVektor y_Test = y + h * y_diff;
            CMyVektor y_diff_Test = ableitungen(y_Test, x + h);
            CMyVektor y_Mittel = 0.5 * (y_diff + y_diff_Test);

            if (Ausgabe == true)
            {
                cout << endl
                     << "Schritt: " << i << endl
                     << "x = " << x << endl
                     << "y = ";
                y.ausgabe();
                cout << "y' = ";
                y_diff.ausgabe();
                cout << "y_Test = ";
                y_Test.ausgabe();
                cout << "y_Test' = ";
                y_diff_Test.ausgabe();
                cout << "y_Mittel = ";
                y_Mittel.ausgabe();
            }

            y = y + h * y_Mittel;
            x += h;
        }
    }
}

CMyVektor fSystem(CMyVektor y, double x)
{
    CMyVektor ergebnis(2);
    ergebnis(0) = 2 * y(1) - x * y(0);
    ergebnis(1) = y(0) * y(1) - 2 * x * x * x;
    return ergebnis;
}

double GDL3(CMyVektor y, double x)
{
    return 2 * x * y(1) * y(2) + 2 * y(0) * y(0) * y(1);
}

int main()
{
    int eingabe = 0;
    do
    {
        cout << "1 fuer DGL mit Euler-Verfahren" << endl
             << "2 fuer DGL mit Heun-Verfahren" << endl
             << "3 fuer DGL mit hoeherer Ordnung" << endl;
        cin >> eingabe;
        if (eingabe < 1 || eingabe > 3)
        {
            cin.clear();
            cin.ignore(99, '\n');
            cout << "Bitte gebe eine Zahl zwischen 1 und 3 ein!" << endl;
        }
    } while (eingabe < 1 || eingabe > 3);

    if (eingabe == 1 || eingabe == 2)
    {
        CMyVektor y(2);
        y(0) = 0;
        y(1) = 1;

        C_DGLSolver solver(fSystem);
        if (eingabe == 1)
        {
            solver.euler_Verfahren(y, 0, 2, 100, true);
        }
        else
        {
            solver.heun_Verfahren(y, 0, 2, 100, true);
        }
    }
    else if (eingabe == 3)
    {
        double x_start = 1.0;
        double x_ende = 2.0;
        double y_exakt = 0.5;

        int schritte_array[] = {10, 100, 1000, 10000};
        double abweichung_euler[4] = {0};
        double abweichung_heun[4] = {0};

        for (int i = 0; 4 > i; i++)
        {
            CMyVektor y_euler(3);
            y_euler(0) = 1;
            y_euler(1) = -1;
            y_euler(2) = 2;
            C_DGLSolver solver_euler(GDL3);
            solver_euler.euler_Verfahren(y_euler, x_start, x_ende, schritte_array[i], false);
            abweichung_euler[i] = y_euler(0) - y_exakt;

            CMyVektor y_heun(3);
            y_heun(0) = 1;
            y_heun(1) = -1;
            y_heun(2) = 2;
            C_DGLSolver solver_heun(GDL3);
            solver_heun.heun_Verfahren(y_heun, x_start, x_ende, schritte_array[i], false);
            abweichung_heun[i] = y_heun(0) - y_exakt;
            cout << "Abweichung bei Euler bei " << schritte_array[i] << " Schritten: " << abweichung_euler[i] << endl;
            cout << "Abweichung bei Heun bei " << schritte_array[i] << " Schritten: " << abweichung_heun[i] << endl;
        }
    }
    system("pause");
    return 0;
}