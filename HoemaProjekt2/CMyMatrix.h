#pragma once
#include <vector>
#include "../HoemaProjekt2/CMyVektor.h"

class CMyMatrix
{
private:
    int Dimension_Zeile;
    int Dimension_Spalte;
    std::vector<double> Eintrag;

public:
    CMyMatrix(int Dimension_Zeile, int Dimension_Spalte);
    int getDimensionZeile() const;
    int getDimensionSpalte() const;
    double getEintrag(int zeile, int spalte) const;
    void setEintrag(int zeile, int spalte, double wert);
    CMyMatrix invers();
};

CMyVektor operator*(CMyMatrix A, CMyVektor x);
CMyMatrix jacobi(CMyVektor x, CMyVektor (*funktion)(CMyVektor x));
void newtonVerfahren(CMyVektor x, CMyVektor (*funktion)(CMyVektor));
