#pragma once
#include <cstdlib>
#include <time.h>

class CZufall
{
private:
    int paare = 0;
    int drillinge = 0;

public:
    int getPaare() const { return paare; }
    int getDrillinge() const { return drillinge; }

    int wert(int a, int b);
    void initalisiere(int a);
    void test(int a, int b, int N, bool falsch);

    void Ausgabe_a1();
    void Ausgabe_b1();
    void Ausgabe_c1();
    void Ausgabe_d1();

    void ZieheZufallszahl(int hauefigkeit[13]);
    void Pokerhand(int hauefigkeit[13]);
};
void test1();
void test2(int N);