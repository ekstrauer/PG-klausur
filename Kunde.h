#ifndef KUNDE_H
#define KUNDE_H

#include <string>
#include <vector>
#include "Cocktail.h"

// Die Klasse Kunde speichert persönliche Daten und gekaufte Cocktails.
class Kunde {
private:
    std::string vorname_;   // Vorname des Kunden
    std::string nachname_;  // Nachname des Kunden
    int alter_;             // Alter des Kunden

    // Liste von Zeigern auf gekaufte Cocktails (dynamisch im Heap angelegt)
    std::vector<Cocktail*> gekaufteCocktails_;

public:
    // Konstruktor: erstellt einen Kunden mit Vorname, Nachname und Alter
    Kunde(const std::string& vorname, const std::string& nachname, int alter);

    // Destruktor: gibt alle dynamisch erzeugten Cocktails frei
    ~Kunde();

    // Getter-Methoden für die Kundendaten
    std::string getVorname() const;
    std::string getNachname() const;
    int getAlter() const;

    // Fügt einen Cocktail zur Liste hinzu (Cocktail wird als Zeiger übergeben)
    void addCocktail(Cocktail* c);

    // Gibt alle bisher gekauften Cocktails in der Konsole aus
    void printHistory() const;

    // Berechnet den Gesamtpreis aller gekauften Cocktails
    double berechneRechnung() const;

    // Hinweis: Methode invite() ist laut Aufgabenstellung nicht erforderlich
};

#endif // KUNDE_H
