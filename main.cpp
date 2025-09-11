#include <iostream>
#include <string>
#include <vector>

#include "Zutat.h"
#include "Cocktail.h"
#include "Kunde.h"
#include "CocktailFlatrate.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    // Liste aller Kunden (für spätere Speicherfreigabe / Verwaltung)
    std::vector<Kunde*> kundenListe;
    Kunde* aktiverKunde = nullptr; // Der aktuell ausgewählte Kunde

    // Kundenanmeldung
    std::string vorname;
    std::string nachname;
    int alter;
    cout << "Geben Sie ihren Vornamen ein:" << endl;
    cin >> vorname;
    cout << "Geben Sie ihren Nachnamen ein:" << endl;
    cin >> nachname;
    cout << "Geben Sie Ihr Alter ein:" << endl;
    cin >> alter;

    // Erstelle neuen Kunden dynamisch und setze ihn als aktiv
    Kunde* kunde = new Kunde(vorname, nachname, alter);
    kundenListe.push_back(kunde);
    aktiverKunde = kunde;

    cout << "Hallo " << aktiverKunde->getVorname() << " " << aktiverKunde->getNachname()
         << ", willkommen im Studierendencafé der hda." << endl;

    bool running = true;
    while (running) {
        // Menüanzeige
        char eingabe;
        cout << "\nBitte treffen Sie Ihre Wahl:" << endl;
        cout << "c/C: Cocktail kaufen" << endl;
        cout << "r/R: Rechnung anschauen" << endl;
        cout << "a/A: Auf gut Glück (CocktailFlatrate)" << endl;
        cout << "n/N: Neuen Kunden anlegen" << endl;
        cout << "x/X: Café verlassen" << endl;
        cin >> eingabe;

        switch (eingabe) {
        case 'c':
        case 'C': {
            // Neuer Cocktail (dynamisch)
            Cocktail* cocktail = new Cocktail();
            bool cocktailFertig = false;
            bool mindestensEineZutat = false;

            while (!cocktailFertig) {
                // Zutatenauswahl anzeigen
                cout << "Zutat hinzufügen (0 = fertig):" << endl;
                cout << "1 - Sahne (0.99 Euro)" << endl;
                cout << "2 - Ananassaft (0.59 Euro)" << endl;
                cout << "3 - Wodka (2.99 Euro)" << endl;
                cout << "4 - Rum (3.99 Euro)" << endl;
                cout << "5 - Cola (1.49 Euro)" << endl;

                int auswahl;
                cin >> auswahl;

                switch (auswahl) {
                case 1:
                    cocktail->addZutat(Zutat("Sahne", 0.99, true));
                    mindestensEineZutat = true;
                    break;
                case 2:
                    cocktail->addZutat(Zutat("Ananassaft", 0.59, true));
                    mindestensEineZutat = true;
                    break;
                case 3:
                    if (aktiverKunde->getAlter() >= 18) {
                        cocktail->addZutat(Zutat("Wodka", 2.99, false));
                        mindestensEineZutat = true;
                    } else {
                        cout << "Sie sind leider zu jung!" << endl;
                    }
                    break;
                case 4:
                    if (aktiverKunde->getAlter() >= 18) {
                        cocktail->addZutat(Zutat("Rum", 3.99, false));
                        mindestensEineZutat = true;
                    } else {
                        cout << "Kein Alkohol für Minderjährige!" << endl;
                    }
                    break;
                case 5:
                    cocktail->addZutat(Zutat("Cola", 1.49, true));
                    mindestensEineZutat = true;
                    break;
                case 0:
                    if (mindestensEineZutat) {
                        cocktailFertig = true;
                    } else {
                        cout << "Bitte wählen Sie mindestens eine Zutat aus!" << endl;
                    }
                    break;
                default:
                    cout << "Ungültige Eingabe!" << endl;
                    break;
                }
            }

            cocktail->display(); // Zeigt Cocktaildetails
            aktiverKunde->addCocktail(cocktail);
            Cocktail::addToUmsatz(cocktail->berechneKosten());

            break;
        }

        case 'a':
        case 'A': {
            // Starte automatische Cocktail-Flatrate
            CocktailFlatrate flatrate;
            flatrate.starteFlatrate(*aktiverKunde);
            break;
        }

        case 'n':
        case 'N': {
            // Neuen Kunden anlegen und aktivieren
            cout << "Neuen Kunden anlegen:" << endl;
            cout << "Vorname: ";
            cin >> vorname;
            cout << "Nachname: ";
            cin >> nachname;
            cout << "Alter: ";
            cin >> alter;

            Kunde* neuerKunde = new Kunde(vorname, nachname, alter);
            kundenListe.push_back(neuerKunde);
            aktiverKunde = neuerKunde;

            cout << "Hallo " << aktiverKunde->getVorname() << " " << aktiverKunde->getNachname()
                 << ", willkommen zurück im Studierendencafé!" << endl;
            break;
        }

        case 'r':
        case 'R': {
            // Zeige Cocktails und Rechnung für aktiven Kunden
            aktiverKunde->printHistory();
            cout << "Gesamtkosten: " << aktiverKunde->berechneRechnung() << " Euro" << endl;
            break;
        }

        case 'x':
        case 'X': {
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

    // Speicherbereinigung: Alle Kunden löschen
    for (Kunde* k : kundenListe) {
        delete k;
    }

    return 0;
}
