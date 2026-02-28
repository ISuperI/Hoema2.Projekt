#pragma once
#include <iostream>
#include "CMyVektor.h"

using namespace std;

class C_DGLSolver
{
private:
    CMyVektor (*fDGLSystem)(CMyVektor y, double x);
    double (*fDGLnterOrdnung)(CMyVektor y, double x);
    bool hoehere_Ordnung = false;

public:
    C_DGLSolver(CMyVektor (*fDGLSystem)(CMyVektor y, double x));
    C_DGLSolver(double (*fDGLnterOrdnung)(CMyVektor y, double x));
    
    CMyVektor ableitungen(CMyVektor y, double x);
    void euler_Verfahren(CMyVektor &y, double x_Start, double x_Ende, int anzahl_Schritte, bool ausgabe);
    void heun_Verfahren(CMyVektor &y, double x_Start, double x_Ende, int anzahl_Schritte, bool ausgabe);
};