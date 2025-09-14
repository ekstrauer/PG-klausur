#ifndef COCKTAILFLATRATE_H
#define COCKTAILFLATRATE_H

#include "Kunde.h"
#include "Zutat.h"
#include <vector>
#include <random>

// Die Klasse CocktailFlatrate erzeugt zufällige Cocktails,
// bis ein bestimmter Mindestumsatz (z. B. 30 €) erreicht ist.
class CocktailFlatrate {
private:
    // Liste aller möglichen Zutaten für Zufallscocktails
    std::vector<Zutat> zutaten_;
    
    // Moderne C++ Zufallszahlengenerierung
    std::random_device rd_;
    std::mt19937 gen_;

    // Initialisiert die verfügbaren Zutaten (einmalig im Konstruktor)
    void initalisiereZutaten();

public:
    // Konstruktor: bereitet Zutatenauswahl vor und initialisiert Zufall
    CocktailFlatrate();

    // Startet die Flatrate für einen Kunden (generiert zufällige Cocktails)
    void starteFlatrate(Kunde& kunde);
};

#endif // COCKTAILFLATRATE_H
