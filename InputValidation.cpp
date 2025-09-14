#include "InputValidation.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>

// Liest eine validierte Ganzzahl
int InputValidation::readInt(const std::string& prompt, int minValue, int maxValue) {
    int value;
    
    while (true) {
        std::cout << prompt;
        
        if (std::cin >> value) {
            if (value >= minValue && value <= maxValue) {
                clearInput(); // Restliche Eingabe löschen
                return value;
            } else {
                std::cout << "Eingabe muss zwischen " << minValue 
                          << " und " << maxValue << " liegen." << std::endl;
            }
        } else {
            std::cout << "Ungültige Eingabe. Bitte geben Sie eine Zahl ein." << std::endl;
            clearInput();
        }
    }
}

// Liest ein validiertes Zeichen
char InputValidation::readChar(const std::string& prompt, const std::string& allowedChars) {
    char input;
    
    while (true) {
        std::cout << prompt;
        
        if (std::cin >> input) {
            // Konvertiere zu Kleinbuchstaben für einheitliche Vergleiche
            char lowerInput = std::tolower(input);
            
            // Prüfe ob das Zeichen in der erlaubten Liste ist
            bool found = false;
            for (char allowed : allowedChars) {
                if (lowerInput == std::tolower(allowed)) {
                    clearInput();
                    return lowerInput;
                }
            }
            
            if (!found) {
                std::cout << "Ungültige Eingabe. Erlaubte Zeichen: " << allowedChars << std::endl;
            }
        } else {
            std::cout << "Ungültige Eingabe. Bitte geben Sie ein einzelnes Zeichen ein." << std::endl;
            clearInput();
        }
    }
}

// Liest einen String
std::string InputValidation::readString(const std::string& prompt) {
    std::string input;
    
    std::cout << prompt;
    std::cin >> input;
    clearInput();
    
    return input;
}

// Bereinigt den Eingabestream nach fehlerhafter Eingabe
void InputValidation::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}