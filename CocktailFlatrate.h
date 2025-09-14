#ifndef COCKTAILFLATRATE_H
#define COCKTAILFLATRATE_H

#include "Kunde.h"

// Die Klasse CocktailFlatrate erzeugt zufällige Cocktails,
// bis ein bestimmter Mindestumsatz (z. B. 30 €) erreicht ist.
class CocktailFlatrate {
public:
    // Konstruktor: bereitet Zufallszahlengenerator vor
    CocktailFlatrate();

    // Startet die Flatrate für einen Kunden (generiert zufällige Cocktails)
    void starteFlatrate(Kunde& kunde);
};

#endif // COCKTAILFLATRATE_H
