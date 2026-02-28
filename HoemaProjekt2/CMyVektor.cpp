#include <iostream>
#include <vector>
#include "CMyVektor.h"
#include <cmath>

using namespace std;

CMyVektor::CMyVektor(int dim) : werte(dim, 0.0) {}

int CMyVektor::getDimension() const
{
    return werte.size();
}

double &CMyVektor::operator()(int index)
{
    return werte.at(index);
}

double CMyVektor::operator()(int index) const
{
    return werte.at(index);
}

double CMyVektor::laenge() const
{
    double laenge = 0;

    for (int i = 0; i < getDimension(); i++)
        laenge += werte[i] * werte[i];
    return sqrt(laenge);
}

void CMyVektor::ausgabe() const
{
    cout << "( ";
    for (int i = 0; i < getDimension(); ++i)
    {
        cout << werte[i];
        if (i < getDimension() - 1)
            cout << "; ";
    }
    cout << " )" << endl;
}

CMyVektor operator+(const CMyVektor &a, const CMyVektor &b)
{
    if (a.getDimension() != b.getDimension())
    {
        cout << "Fehler: Vektoren haben unterschiedliche Dimensionen!" << endl;
    }
    CMyVektor ergebnis(a.getDimension());

    for (int i = 0; i < a.getDimension(); i++)
        ergebnis(i) = a(i) + b(i);
    return ergebnis;
}

CMyVektor operator*(double lambda, const CMyVektor &a)
{
    CMyVektor ergebnis(a.getDimension());
    for (int i = 0; i < a.getDimension(); i++)
        ergebnis(i) = lambda * a(i);
    return ergebnis;
}