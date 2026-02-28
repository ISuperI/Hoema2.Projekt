#pragma once
#include <iostream>
#include <vector>

class CMyVektor
{
private:
    std::vector<double> werte;

public:
    CMyVektor(int dim);
    int getDimension() const;
    double &operator()(int index);
    double operator()(int index) const;
    double laenge() const;
    void ausgabe() const;

    friend CMyVektor operator+(const CMyVektor &a, const CMyVektor &b);
    friend CMyVektor operator*(double lambda, const CMyVektor &a);
};
