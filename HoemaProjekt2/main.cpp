#include "CMyMatrix.h"
#include "CMyVektor.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

CMyMatrix::CMyMatrix(int Dimension_Zeile, int Dimension_Spalte)
    : Dimension_Zeile(Dimension_Zeile), Dimension_Spalte(Dimension_Spalte),
      Eintrag(Dimension_Zeile * Dimension_Spalte, 0.0) {}

int CMyMatrix::getDimensionZeile() const
{
    return Dimension_Zeile;
}
int CMyMatrix::getDimensionSpalte() const
{
    return Dimension_Spalte;
}
double CMyMatrix::getEintrag(int zeile, int spalte) const
{
    return Eintrag[zeile * Dimension_Spalte + spalte];
}
void CMyMatrix::setEintrag(int zeile, int spalte, double wert)
{
    Eintrag[zeile * Dimension_Spalte + spalte] = wert;
}

CMyMatrix CMyMatrix::invers()
{
    if (Dimension_Zeile == 2 && Dimension_Spalte == 2)
    {
        CMyMatrix inverse(2, 2);

        double a = getEintrag(0, 0);
        double b = getEintrag(0, 1);
        double c = getEintrag(1, 0);
        double d = getEintrag(1, 1);
        double determinante = a * d - b * c;
        if (determinante == 0)
        {
            cout << "Fehler: Die Determinante darf nicht 0 sein" << endl;
            return CMyMatrix(2, 2);
        }
        inverse.setEintrag(0, 0, d / determinante);
        inverse.setEintrag(0, 1, -b / determinante);
        inverse.setEintrag(1, 0, -c / determinante);
        inverse.setEintrag(1, 1, a / determinante);
        return inverse;
    }
    else
    {
        cout << "Fehler: Matrize muss 2x2 groß sein" << endl;
        return CMyMatrix(0, 0);
    }
}

CMyVektor operator*(CMyMatrix A, CMyVektor x)
{
    if (A.getDimensionSpalte() != x.getDimension())
    {
        cout << "Matrize und Vektor dürfen nicht unterschiedliche Dimensionen haben" << endl;
        return CMyVektor(0);
    }
    CMyVektor ergebnis(A.getDimensionZeile());

    for (int i = 0; i < A.getDimensionZeile(); i++)
    {
        double summe = 0;
        for (int j = 0; j < A.getDimensionSpalte(); j++)
        {
            summe += A.getEintrag(i, j) * x(j);
        }
        ergebnis(i) = summe;
    }

    return ergebnis;
}

CMyMatrix jacobi(CMyVektor x, CMyVektor (*funktion)(CMyVektor x))
{
    int dimension = x.getDimension();
    int dimension_funktion = funktion(x).getDimension();
    CMyMatrix jacobi(dimension_funktion, dimension);
    double h = 1e-4;

    for (int i = 0; i < dimension; i++)
    {
        CMyVektor x_neu = x;
        x_neu(i) += h;

        CMyVektor funktion_neu = funktion(x_neu);
        CMyVektor funktion_x = funktion(x);

        for (int j = 0; j < dimension_funktion; j++)
        {
            jacobi.setEintrag(j, i, (funktion_neu(j) - funktion_x(j)) / h);
        }
    }
    return jacobi;
}

void newtonVerfahren(CMyVektor x, CMyVektor (*funktion)(CMyVektor))
{
    const double toleranz = 1e-5;
    const int max_Schritte = 50;
    int schritt = 0;

    while (schritt < max_Schritte)
    {
        CMyVektor funktion_x = funktion(x);
        double funktionslaenge = funktion_x.laenge();
        if (funktionslaenge < toleranz)
            break;

        CMyMatrix Matrix = jacobi(x, funktion);
        CMyMatrix Matrix_invertiert = Matrix.invers();

        CMyVektor delta = Matrix_invertiert * funktion_x;

        cout << "Schritt " << schritt << endl;
        cout << "x = ";
        x.ausgabe();
        cout << "f(x) = ";
        funktion_x.ausgabe();
        cout << "||f(x)|| = " << funktionslaenge << endl;

        x = x + (-1.0) * delta;
        schritt++;
    }
    if (schritt == max_Schritte)
    {
        cout << endl
             << endl;
        cout << "Ende wegen Schrittanzahl = 50 bei" << endl;
    }
    else
    {
        cout << endl
             << endl;
        cout << "Ende wegen ||grad f(x)||<1e-5 bei " << endl;
    }

    cout << "Ergebnis nach " << schritt << " Schritten:\n";
    cout << "x = ";
    x.ausgabe();
    cout << "f(x) = ";
    funktion(x).ausgabe();
}

CMyVektor f(CMyVektor x)
{
    CMyVektor Ergebnis(3);

    double x1 = x(0);
    double x2 = x(1);
    double x3 = x(2);
    double x4 = x(3);

    Ergebnis(0) = x1 * x2 * exp(x3);
    Ergebnis(1) = x2 * x3 * x4;
    Ergebnis(2) = x1;

    return Ergebnis;
}

CMyVektor g(CMyVektor x)
{
    CMyVektor Ergebnis(2);
    double x1 = x(0);
    double x2 = x(1);
    Ergebnis(0) = pow(x1, 3) * pow(x2, 3) - 2 * x2;
    Ergebnis(1) = x1 - 2;
    return Ergebnis;
}

int main()
{

    CMyVektor x(4);
    x(0) = 1;
    x(1) = 2;
    x(2) = 0;
    x(3) = 3;

    CMyMatrix F = jacobi(x, f);

    cout << "Matix:" << endl;
    for (int i = 0; i < F.getDimensionZeile(); ++i)
    {
        for (int j = 0; j < F.getDimensionSpalte(); ++j)
        {
            cout << F.getEintrag(i, j) << endl;
        }
        cout << endl;
    }

    CMyVektor startwert(2);
    startwert(0) = 1;
    startwert(1) = 1;

    newtonVerfahren(startwert, g);

    system("pause");
    return 0;
}