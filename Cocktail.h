#ifndef COCKTAIL_H
#define COCKTAIL_H

#include "Zutat.h"
#include <vector>

// Die Klasse Cocktail repräsentiert ein Getränk aus mehreren Zutaten.
// Sie verwaltet die enthaltenen Zutaten und berechnet z. B. Preis und Alkoholgehalt.
class Cocktail {
private:
    std::vector<Zutat> zutaten_;     // Liste aller Zutaten im Cocktail

    // Aufgabe 2: speichert den Gesamtumsatz aller verkauften Cocktails (statisch für alle Instanzen)
    static double gesamtUmsatz_;

public:
    // Fügt dem Cocktail eine Zutat hinzu
    void addZutat(const Zutat& zutat);

    // Gibt true zurück, wenn alle Zutaten alkoholfrei sind
    bool istAlkoholfrei() const;

    // Berechnet die Gesamtkosten aller Zutaten im Cocktail
    double berechneKosten() const;

    // Gibt alle enthaltenen Zutaten und Infos zum Cocktail auf der Konsole aus
    void display() const;

    // Aufgabe 2: Gibt den aktuellen Gesamtumsatz aller Cocktails zurück
    static double getGesamtUmsatz();

    Cocktail();                    // Standardkonstruktor
    Cocktail(const Cocktail& other); // Kopierkonstruktor – zählt zum Umsatz
    ~Cocktail();                   // Optional: Destruktor (falls Speicherbereinigung nötig)

    // Aufgabe 2: Addiert einen Betrag zum Gesamtumsatz (z. B. nach Verkauf)
    static void addToUmsatz(double betrag);
};

#endif // COCKTAIL_H
