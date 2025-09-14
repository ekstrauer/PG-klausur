#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include <string>
#include <climits>

// Utility-Klasse für robuste Eingabevalidierung
class InputValidation {
public:
    // Validiert und liest eine Ganzzahl mit Min-/Max-Grenzen
    static int readInt(const std::string& prompt, int minValue = INT_MIN, int maxValue = INT_MAX);
    
    // Validiert und liest ein einzelnes Zeichen aus erlaubten Optionen
    static char readChar(const std::string& prompt, const std::string& allowedChars);
    
    // Liest einen String (für Namen etc.)
    static std::string readString(const std::string& prompt);
    
private:
    // Hilfsmethode um cin-Stream nach fehlerhafter Eingabe zu bereinigen
    static void clearInput();
};

#endif // INPUTVALIDATION_H