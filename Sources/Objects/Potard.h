//
// Created by Stéphane on 06.08.23.
//

#pragma once

#include <string>

class Potard {
private:
    int midiNumber;     // Numéro de contrôleur MIDI
    std::string label;  // Label (nom) du potard

public:
    Potard(int midiNum, const std::string& lbl);

    int getMidiNumber() const;
    const std::string& getLabel() const;
};
