#include "Kunde.h"
#include <iostream>

// Konstruktor: Initialisiert Vorname, Nachname und Alter eines Kunden
Kunde::Kunde(const std::string& vorname, const std::string& nachname, int alter)
    : vorname_(vorname), nachname_(nachname), alter_(alter) {}

// Destruktor: gibt alle dynamisch erzeugten Cocktails im Vektor frei
Kunde::~Kunde() {
    for (Cocktail* c : gekaufteCocktails_) {
        delete c; // Speicher auf dem Heap wird freigegeben
    }
}

// Gibt den Vornamen des Kunden zurück
std::string Kunde::getVorname() const {
    return vorname_;
}

// Gibt den Nachnamen des Kunden zurück
std::string Kunde::getNachname() const {
    return nachname_;
}

// Gibt das Alter des Kunden zurück
int Kunde::getAlter() const {
    return alter_;
}

// Fügt einen Cocktail zur Einkaufsliste des Kunden hinzu
// Der Cocktail muss vorher mit `new` erstellt worden sein
void Kunde::addCocktail(Cocktail* c) {
    gekaufteCocktails_.push_back(c);
}

// Gibt alle gekauften Cocktails des Kunden aus
void Kunde::printHistory() const {
    std::cout << "Kunde: " << vorname_ << " " << nachname_
              << " (Alter: " << alter_ << ")" << std::endl;
    std::cout << "Gekaufte Cocktails:" << std::endl;

    for (int i = 0; i < gekaufteCocktails_.size(); ++i) {
        std::cout << "- Cocktail " << (i + 1) << ":" << std::endl;
        gekaufteCocktails_[i]->display(); // zeigt Inhalt und Preis an
        std::cout << std::endl;
    }
}

// Berechnet die Gesamtsumme aller bisher gekauften Cocktails
double Kunde::berechneRechnung() const {
    double summe = 0.0;
    for (int i = 0; i < gekaufteCocktails_.size(); ++i) {
        summe += gekaufteCocktails_[i]->berechneKosten();
    }
    return summe;
}
