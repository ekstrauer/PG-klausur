#ifndef ZUTATENMANAGER_H
#define ZUTATENMANAGER_H

#include "Zutat.h"
#include <vector>

// Singleton-Klasse für die Verwaltung aller verfügbaren Zutaten
// Stellt eine zentrale Quelle für Zutaten bereit, um Duplikation zu vermeiden
class ZutatenManager {
private:
    std::vector<Zutat> verfuegbareZutaten_;
    
    // Privater Konstruktor für Singleton-Pattern
    ZutatenManager();
    
    // Initialisiert die verfügbaren Zutaten
    void initialisiereZutaten();

public:
    // Singleton-Zugriff
    static ZutatenManager& getInstance();
    
    // Gibt alle verfügbaren Zutaten zurück
    const std::vector<Zutat>& getVerfuegbareZutaten() const;
    
    // Gibt eine Zutat nach Index zurück (1-basiert für Benutzeroberfläche)
    const Zutat* getZutatByIndex(int index) const;
    
    // Zeigt alle verfügbaren Zutaten mit Nummern an
    void zeigeZutatenMenu(int kundenAlter) const;
    
    // Verhindere Kopieren und Zuweisen
    ZutatenManager(const ZutatenManager&) = delete;
    ZutatenManager& operator=(const ZutatenManager&) = delete;
};

#endif // ZUTATENMANAGER_H