//
// Created by ubuntu on 06.08.23.
//

#include "Potard.h"

Potard::Potard(int midiNum, const std::string& lbl)
    : midiNumber(midiNum), label(lbl)
{
}

int Potard::getMidiNumber() const { return midiNumber; }

const std::string& Potard::getLabel() const { return label; }
