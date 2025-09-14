#include "ZutatenManager.h"
#include <iostream>

// Privater Konstruktor
ZutatenManager::ZutatenManager() {
    initialisiereZutaten();
}

// Singleton-Zugriff
ZutatenManager& ZutatenManager::getInstance() {
    static ZutatenManager instance;
    return instance;
}

// Initialisiert die verfügbaren Zutaten (zentrale Definition)
void ZutatenManager::initialisiereZutaten() {
    verfuegbareZutaten_ = {
        Zutat("Sahne", 0.99, true),
        Zutat("Ananassaft", 0.59, true), 
        Zutat("Wodka", 2.99, false),
        Zutat("Rum", 3.99, false),
        Zutat("Cola", 1.49, true)
    };
}

// Gibt alle verfügbaren Zutaten zurück
const std::vector<Zutat>& ZutatenManager::getVerfuegbareZutaten() const {
    return verfuegbareZutaten_;
}

// Gibt eine Zutat nach Index zurück (1-basiert)
const Zutat* ZutatenManager::getZutatByIndex(int index) const {
    if (index < 1 || index > static_cast<int>(verfuegbareZutaten_.size())) {
        return nullptr;
    }
    return &verfuegbareZutaten_[index - 1]; // Konvertierung zu 0-basiert
}

// Zeigt das Zutaten-Menü an, filtert Alkohol für Minderjährige
void ZutatenManager::zeigeZutatenMenu(int kundenAlter) const {
    std::cout << "Zutat hinzufügen (0 = fertig):" << std::endl;
    
    for (size_t i = 0; i < verfuegbareZutaten_.size(); ++i) {
        const Zutat& zutat = verfuegbareZutaten_[i];
        
        // Zeige nur alkoholfreie Zutaten für Minderjährige an
        if (kundenAlter < 18 && !zutat.getAlkoholfrei()) {
            continue;
        }
        
        std::cout << (i + 1) << " - " << zutat.getName() 
                  << " (" << zutat.getPreis() << " Euro)" << std::endl;
    }
}