#include "Zutat.h"
#include "Cocktail.h"
#include <iostream>

// Fügt eine neue Zutat zur Zutatenliste hinzu
void Cocktail::addZutat(const Zutat& zutat) {
    zutaten_.push_back(zutat);
}

// Prüft, ob alle Zutaten alkoholfrei sind
bool Cocktail::istAlkoholfrei() const {
    for (int i = 0; i < zutaten_.size(); ++i) {
        if (!zutaten_[i].getAlkoholfrei()) {
            return false;
        }
    }
    return true;
}

// Berechnet die Gesamtkosten aller enthaltenen Zutaten
double Cocktail::berechneKosten() const {
    double summe = 0;
    for (int i = 0; i < zutaten_.size(); ++i) {
        summe += zutaten_[i].getPreis();
    }
    return summe;
}

// Gibt alle Zutaten und Infos zum Cocktail aus
void Cocktail::display() const {
    std::cout << "Deine Zutaten: " << std::endl;
    for (int i = 0; i < zutaten_.size(); ++i) {
        std::cout << "Name: " << zutaten_[i].getName()
        << ", (Preis: " << zutaten_[i].getPreis() << ") " << std::endl;
    }
    std::cout << "Gesamtpreis: " << berechneKosten() << " Euro" << std::endl;
    std::cout << "Alkoholfrei: " << (istAlkoholfrei() ? "Ja" : "Nein") << std::endl;
}

// ==============================
// Aufgabe 2: Gesamtumsatz zählen
// ==============================

// Statische Variable initialisieren
double Cocktail::gesamtUmsatz_ = 0.0;

// Gibt den aktuellen Gesamtumsatz zurück
double Cocktail::getGesamtUmsatz() {
    return gesamtUmsatz_;
}

// Konstruktor: erzeugt einen leeren Cocktail
Cocktail::Cocktail() {
    // Kein Umsatz, da keine Zutaten
}

// Kopierkonstruktor: kopiert Zutaten und zählt den Umsatz
Cocktail::Cocktail(const Cocktail& other) : zutaten_(other.zutaten_) {
    gesamtUmsatz_ += berechneKosten();
}

// Destruktor: zieht die Kosten des Cocktails vom Umsatz ab
Cocktail::~Cocktail() {
    gesamtUmsatz_ -= berechneKosten();
}

// Fügt manuell einen Betrag zum Gesamtumsatz hinzu (z. B. für Zufalls-Cocktails)
void Cocktail::addToUmsatz(double betrag) {
    gesamtUmsatz_ += betrag;
}
