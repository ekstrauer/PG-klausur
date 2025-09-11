#include "Zutat.h"

// Konstruktor: Initialisiert eine Zutat mit Name, Preis und Alkoholstatus.
Zutat::Zutat(const std::string& name, double preis, bool alkoholfrei)
    : name_(name), preis_(preis), alkoholfrei_(alkoholfrei) {}

// Gibt den Preis der Zutat zurück.
double Zutat::getPreis() const {
    return preis_;
}

// Gibt den Namen der Zutat zurück.
std::string Zutat::getName() const {
    return name_;
}

// Gibt zurück, ob die Zutat alkoholfrei ist.
bool Zutat::getAlkoholfrei() const {
    return alkoholfrei_;
}
