#include "CocktailFlatrate.h"
#include "Cocktail.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Konstruktor: Initialisiert Zufallszahlengenerator und Zutatenliste
CocktailFlatrate::CocktailFlatrate() {
    srand(time(0));              // Zufallszahlen initialisieren
    initalisiereZutaten();       // Liste mit verfügbaren Zutaten vorbereiten
}

// Erstellt eine feste Auswahl an Zutaten für die Zufallscocktails
void CocktailFlatrate::initalisiereZutaten() {
    zutaten_ =  {
        Zutat("Sahne", 0.99, true),
        Zutat("Ananassaft", 0.59, true),
        Zutat("Wodka", 2.99, false),
        Zutat("Rum", 3.99, false),
        Zutat("Cola", 1.49, true)
    };
}

// Startet die Cocktail-Flatrate für einen Kunden
// Fügt zufällige Cocktails hinzu, bis mindestens 30€ erreicht sind
void CocktailFlatrate::starteFlatrate(Kunde& kunde) {
    double grenze = 30.0;   // Zielpreis für die Flatrate
    double gesamt = 0.0;    // bisheriger Gesamtwert

    // Schleife: solange Gesamtwert unter Zielgrenze bleibt
    while (gesamt < grenze) {
        Cocktail* zufallscocktail = new Cocktail();
        int hinzugefuegt = 0;

        // Füge 3 zufällige Zutaten hinzu (nur alkoholfrei bei U18)
        while (hinzugefuegt < 3) {
            int i = rand() % zutaten_.size();
            Zutat z = zutaten_[i];

            if (kunde.getAlter() < 18 && !z.getAlkoholfrei()) {
                continue; // Alkohol bei Minderjährigen vermeiden
            }

            zufallscocktail->addZutat(z);
            hinzugefuegt++;
        }

        // Preis berechnen und zum Gesamtwert addieren
        double preis = zufallscocktail->berechneKosten();
        gesamt += preis;

        // Ausgabe des erstellten Cocktails
        std::cout << "Zufalls-Cocktail:" << std::endl;
        zufallscocktail->display();
        std::cout << std::endl;

        // Cocktail dem Kunden zuweisen und Umsatz erhöhen
        kunde.addCocktail(zufallscocktail);
        Cocktail::addToUmsatz(preis);
    }

    std::cout << "Flatrate beendet. Gesamtpreis: " << gesamt << " Euro\n";
}
