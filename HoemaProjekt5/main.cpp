#include "CZufall.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>

using namespace std;

int CZufall::wert(int a, int b)
{
    return rand() % (b - a + 1) + a;
}
void CZufall::initalisiere(int a)
{
    srand(a);
}
void CZufall::test(int a, int b, int N, bool falsch)
{
    int bereich = b - a + 1;
    int Ergebnis[bereich] = {0};
    for (int i = 0; i < N; i++)
    {
        if (falsch)
        {
            initalisiere(time(NULL));
        }
        int zufalls_wert = wert(a, b);
        Ergebnis[zufalls_wert - a]++;
    }
    for (int i = 0; i < bereich; i++)
    {
        if (Ergebnis[i] > 0)
            cout << "Die Zahl " << (i + a) << " wurde " << Ergebnis[i] << " mal geworfen." << endl;
    }
}

void CZufall::Ausgabe_a1()
{
    for (int i = 0; i < 5; i++)
    {
        initalisiere(10);
        test(3, 7, 10000, false);
        cout << endl;
    }
}
void CZufall::Ausgabe_b1()
{
    for (int i = 0; i < 5; i++)
    {
        initalisiere(i);
        test(3, 7, 10000, false);
        cout << endl;
    }
}
void CZufall::Ausgabe_c1()
{
    for (int i = 0; i < 5; i++)
    {
        Sleep(1000);
        initalisiere(time(NULL));
        test(3, 7, 10000, false);
        cout << endl;
    }
}
void CZufall::Ausgabe_d1()
{
    for (int i = 0; i < 5; i++)
    {
        Sleep(1000);
        initalisiere(i);
        test(3, 7, 10000, true);
        cout << endl;
    }
}
void CZufall::ZieheZufallszahl(int hauefigkeit[13])
{
    int Deck[51];

    for (int i = 0; i < 52; i++)
    {
        Deck[i] = i;
    }
    for (int i = 0; i < 52; i++)
    {
        int j = rand() % 52;
        swap(Deck[i], Deck[j]);
    }
    for (int i = 0; i < 7; i++)
    {
        int wert = Deck[i] % 13;
        hauefigkeit[wert]++;
    }
}
void CZufall::Pokerhand(int hauefigkeit[13])
{

    paare = 0;
    drillinge = 0;
    for (int i = 0; i < 13; i++)
    {

        if (hauefigkeit[i] >= 2)
        {
            paare++;
        }
        if (hauefigkeit[i] >= 4)
        {
            paare++;
        }
        if (hauefigkeit[i] >= 3)
        {
            drillinge++;
        }
    }
}
void test1()
{
    CZufall zufall;
    cout << "Test a1:" << endl;
    zufall.Ausgabe_a1();
    cout << "Test b1:" << endl;
    zufall.Ausgabe_b1();
    cout << "Test c1:" << endl;
    zufall.Ausgabe_c1();
    cout << "Test d1:" << endl;
    zufall.Ausgabe_d1();
}
void test2(int N)
{
    CZufall zufall;
    zufall.initalisiere(time(NULL));
    double paare_insgesamt = 0;
    double drillinge_insgesamt = 0;
    for (int i = 0; i < N; i++)
    {
        int hauefigkeit[13] = {0};
        zufall.ZieheZufallszahl(hauefigkeit);
        zufall.Pokerhand(hauefigkeit);
        if (zufall.getPaare() >= 2)
        {
            paare_insgesamt++;
        }
        if (zufall.getDrillinge() >= 1)
        {
            drillinge_insgesamt++;
        }
    }
    cout << "In " << N << " Pokerhaenden gab es: " << endl
         << paare_insgesamt << " Paare: " << paare_insgesamt * 100 / N << " %" << endl
         << drillinge_insgesamt << " Drillinge: " << drillinge_insgesamt * 100 / N << " %" << endl;
}
int main()
{
    test1();
    int N;
    cout << "Gib N ein: ";
    cin >> N;
    test2(N);

    system("pause");
    return 0;
}