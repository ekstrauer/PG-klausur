#ifndef ZUTAT_H
#define ZUTAT_H

#include <string>

// Repräsentiert eine Cocktail-Zutat mit Name, Preis und Alkoholstatus.
class Zutat {
private:
    std::string name_;        // Name der Zutat
    double preis_;            // Preis in Euro
    bool alkoholfrei_;        // true, wenn alkoholfrei

public:
    Zutat(const std::string& name, double preis, bool alkoholfrei); // Konstruktor

    double getPreis() const;         // Gibt den Preis zurück
    std::string getName() const;     // Gibt den Namen zurück
    bool getAlkoholfrei() const;     // true, wenn alkoholfrei
};

#endif // ZUTAT_H
