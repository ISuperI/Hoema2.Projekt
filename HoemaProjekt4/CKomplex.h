#pragma once
#include <vector>
#include <string>

class CKomplex
{
private:
    double real;
    double imag;

public:
    CKomplex();
    CKomplex(double a, double b);
    CKomplex(double phi);
    double re() const;
    double im() const;

    CKomplex operator+(const CKomplex &other) const;
    CKomplex operator*(const CKomplex &other) const;
    CKomplex operator*(double scalar) const;

    double abs() const;
};

std::vector<CKomplex> werte_einlesen(const std::string dateiname);
void werte_ausgeben(const std::string dateiname, std::vector<CKomplex> werte, double epsilon = -1);
std::vector<CKomplex> fourier_transformieren(const std::vector<CKomplex> &werte, bool rueckwaerts);
double max_abweichung(const std::vector<CKomplex> &original, const std::vector<CKomplex> &rekonstruiert);
void datei_testen(const std::string &dateiname);
void bild_testen(const std::string &dateiname);