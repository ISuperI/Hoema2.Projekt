#include <iostream>
#include "CKomplex.h"
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

const double Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

CKomplex::CKomplex() : real(0), imag(0) {}

CKomplex::CKomplex(double a, double b) : real(a), imag(b) {}

CKomplex::CKomplex(double phi) : real(cos(phi)), imag(sin(phi)) {}

double CKomplex::re() const
{
    return real;
}
double CKomplex::im() const
{
    return imag;
}

CKomplex CKomplex::operator+(const CKomplex &other) const
{
    return CKomplex(real + other.real, imag + other.imag);
}
CKomplex CKomplex::operator*(const CKomplex &other) const
{
    return CKomplex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}
CKomplex CKomplex::operator*(double scalar) const
{
    return CKomplex(real * scalar, imag * scalar);
}

double CKomplex::abs() const
{
    return sqrt(real * real + imag * imag);
}

vector<CKomplex> werte_einlesen(const std::string dateiname)
{
    int i, N, idx;
    double re, im;
    vector<CKomplex> werte;
    // File oeffnen
    ifstream fp;
    fp.open(dateiname);
    fp >> N;
    // Werte-Vektor anlegen
    werte.resize(N);
    CKomplex null(0, 0);
    for (i = 0; i < N; i++)
        werte[i] = null;
    // Eintraege einlesen und im Werte-Vektor ablegen
    while (!fp.eof())
    {
        fp >> idx >> re >> im;
        CKomplex a(re, im);
        werte[idx] = a;
    }
    // File schliessen
    fp.close();

    return werte;
}

void werte_ausgeben(const std::string dateiname, vector<CKomplex> werte, double epsilon)
{
    int i;
    int N = werte.size();
    // File oeffnen
    ofstream fp;
    fp.open(dateiname);
    // Dimension in das File schreiben
    fp << N << endl;
    // Eintraege in das File schreiben
    fp.precision(10);
    for (i = 0; i < N; i++)
        if (werte[i].abs() > epsilon)
            fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
    // File schliessen
    fp.close();
}

vector<CKomplex> fourier_transformieren(const vector<CKomplex> &werte, bool Rueckwaerts)
{
    int Size = werte.size();
    vector<CKomplex> Ergebnis(Size);
    double vz = -1;
    if (Rueckwaerts == true)
    {
        vz = 1;
    }
    double ausgleich = 1.0 / sqrt(Size);

    for (int i = 0; i < Size; i++)
    {
        CKomplex summe(0, 0);
        for (int j = 0; j < Size; j++)
        {
            double winkel = vz * 2 * Pi * i * j / Size;
            CKomplex w(cos(winkel), sin(winkel));
            summe = summe + werte[j] * w;
        }

        Ergebnis[i] = summe * ausgleich;
    }

    return Ergebnis;
}

double max_abweichung(const vector<CKomplex> &original, const vector<CKomplex> &komprimmiert)
{
    double maxAbweichung = 0;

    for (unsigned int i = 0; i < original.size(); ++i)
    {
        double abweichung = (original[i] + (komprimmiert[i] * -1)).abs();
        if (abweichung > maxAbweichung)
        {
            maxAbweichung = abweichung;
        }
    }
    return maxAbweichung;
}

void datei_testen(const string &dateiname)
{
    cout << "Bei " << dateiname << endl;

    vector<CKomplex> werte = werte_einlesen(dateiname);
    vector<CKomplex> fourier_werte = fourier_transformieren(werte, false);

    string ausgabeDatei = "Z" + dateiname + "_komp_Standart" + ".txt";
    werte_ausgeben(ausgabeDatei, fourier_werte);

    vector<CKomplex> komprimm = werte_einlesen(ausgabeDatei);
    vector<CKomplex> fourier_werte_rueck = fourier_transformieren(komprimm, true);

    double abweichung = max_abweichung(werte, fourier_werte_rueck);

    cout << "Maximale Abweichung bei Standard-Epsilon: " << abweichung << endl;

    double epsilon[4] = {0.001, 0.01, 0.1, 1.0};

    for (int i = 0; i < 4; i++)
    {
        string ausgabeDatei = "Z" + dateiname + "komp" + to_string(epsilon[i]) + ".txt";
        werte_ausgeben(ausgabeDatei, fourier_werte, epsilon[i]);

        vector<CKomplex> komprimm = werte_einlesen(ausgabeDatei);
        vector<CKomplex> fourier_werte_rueck = fourier_transformieren(komprimm, true);

        double abweichung = max_abweichung(werte, fourier_werte_rueck);

        cout << "Maximale Abweichung bei epsilon=" << epsilon[i] << ": " << abweichung << endl;
    }
    cout << endl;
}
void bild_testen(const string &dateiname)
{
    double epsilon[5] = {1, 3, 10, 30, 100};
    vector<CKomplex> werte = werte_einlesen(dateiname);
    vector<CKomplex> fourier_werte = fourier_transformieren(werte, false);

    for (int i = 0; i < 5; i++)
    {
        vector<CKomplex> komprimmiert;

        for (unsigned int j = 0; j < fourier_werte.size(); j++)
        {
            CKomplex wert = fourier_werte[j];
            komprimmiert.push_back(wert);
        }
        vector<CKomplex> komprimm_eps = fourier_transformieren(komprimmiert, true);
        string ausgabeDatei = "Z" + dateiname + "komprimmiert" + to_string(epsilon[i]) + ".txt";

        werte_ausgeben(ausgabeDatei, komprimm_eps, epsilon[i]);
        cout << "Text-Bild Datei Nr: " << i + 1 << " generiert" << endl;
    }
    cout << "Alle Text-Bild Datein generiert" << endl;
}
