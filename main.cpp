#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <optional>

#include "Zutat.h"
#include "Cocktail.h"
#include "Kunde.h"
#include "CocktailFlatrate.h"
#include "ZutatenManager.h"
#include "InputValidation.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    // Liste aller Kunden (mit smart pointers für automatische Speicherverwaltung)
    std::vector<std::unique_ptr<Kunde>> kundenListe;
    std::optional<std::reference_wrapper<Kunde>> aktiverKunde = std::nullopt; // Der aktuell ausgewählte Kunde

    // Kundenanmeldung mit robuster Eingabevalidierung
    std::string vorname = InputValidation::readString("Geben Sie ihren Vornamen ein: ");
    std::string nachname = InputValidation::readString("Geben Sie ihren Nachnamen ein: ");
    int alter = InputValidation::readInt("Geben Sie Ihr Alter ein: ", 0, 150);

    // Erstelle neuen Kunden mit smart pointer und setze ihn als aktiv
    auto kunde = std::make_unique<Kunde>(vorname, nachname, alter);
    aktiverKunde = std::ref(*kunde);
    kundenListe.push_back(std::move(kunde));

    cout << "Hallo " << aktiverKunde->get().getVorname() << " " << aktiverKunde->get().getNachname()
         << ", willkommen im Studierendencafé der hda." << endl;

    bool running = true;
    while (running) {
        // Menüanzeige
        cout << "\nBitte treffen Sie Ihre Wahl:" << endl;
        cout << "c/C: Cocktail kaufen" << endl;
        cout << "r/R: Rechnung anschauen" << endl;
        cout << "a/A: Auf gut Glück (CocktailFlatrate)" << endl;
        cout << "n/N: Neuen Kunden anlegen" << endl;
        cout << "x/X: Café verlassen" << endl;
        
        char eingabe = InputValidation::readChar("Ihre Wahl: ", "crancranxCRANCRANX");

        switch (eingabe) {
        case 'c': {
            // Neuer Cocktail mit smart pointer
            auto cocktail = std::make_unique<Cocktail>();
            bool cocktailFertig = false;
            bool mindestensEineZutat = false;
            
            // Zugriff auf ZutatenManager für dynamische Zutatenanzeige
            ZutatenManager& zutatenManager = ZutatenManager::getInstance();

            while (!cocktailFertig) {
                // Dynamische Zutatenauswahl basierend auf Kundenalter
                zutatenManager.zeigeZutatenMenu(aktiverKunde->get().getAlter());

                int auswahl = InputValidation::readInt("Ihre Auswahl: ", 0, 
                    static_cast<int>(zutatenManager.getVerfuegbareZutaten().size()));

                if (auswahl == 0) {
                    if (mindestensEineZutat) {
                        cocktailFertig = true;
                    } else {
                        cout << "Bitte wählen Sie mindestens eine Zutat aus!" << endl;
                    }
                } else {
                    const Zutat* gewaehlteZutat = zutatenManager.getZutatByIndex(auswahl);
                    if (gewaehlteZutat != nullptr) {
                        // Altersprüfung für alkoholische Zutaten
                        if (!gewaehlteZutat->getAlkoholfrei() && aktiverKunde->get().getAlter() < 18) {
                            cout << "Sie sind leider zu jung für alkoholische Zutaten!" << endl;
                        } else {
                            cocktail->addZutat(*gewaehlteZutat);
                            mindestensEineZutat = true;
                        }
                    } else {
                        cout << "Ungültige Zutatennummer!" << endl;
                    }
                }
            }

            cocktail->display(); // Zeigt Cocktaildetails
            Cocktail::addToUmsatz(cocktail->berechneKosten());
            aktiverKunde->get().addCocktail(cocktail.release()); // Transfer ownership to Kunde

            break;
        }

        case 'a': {
            // Starte automatische Cocktail-Flatrate
            CocktailFlatrate flatrate;
            flatrate.starteFlatrate(aktiverKunde->get());
            break;
        }

        case 'n': {
            // Neuen Kunden anlegen und aktivieren
            cout << "Neuen Kunden anlegen:" << endl;
            std::string neuerVorname = InputValidation::readString("Vorname: ");
            std::string neuerNachname = InputValidation::readString("Nachname: ");
            int neuesAlter = InputValidation::readInt("Alter: ", 0, 150);

            auto neuerKunde = std::make_unique<Kunde>(neuerVorname, neuerNachname, neuesAlter);
            aktiverKunde = std::ref(*neuerKunde);
            kundenListe.push_back(std::move(neuerKunde));

            cout << "Hallo " << aktiverKunde->get().getVorname() << " " << aktiverKunde->get().getNachname()
                 << ", willkommen zurück im Studierendencafé!" << endl;
            break;
        }

        case 'r': {
            // Zeige Cocktails und Rechnung für aktiven Kunden
            aktiverKunde->get().printHistory();
            cout << "Gesamtkosten: " << aktiverKunde->get().berechneRechnung() << " Euro" << endl;
            break;
        }

        case 'x': {
            // Beenden
            cout << "Sie haben das Café verlassen." << endl;
            running = false;
            break;
        }

        default:
            cout << "Ungültige Auswahl." << endl;
            break;
        }
    }

    // Mit smart pointers ist keine manuelle Speicherbereinigung nötig
    // Die unique_ptr-Objekte werden automatisch aufgeräumt

    return 0;
}
