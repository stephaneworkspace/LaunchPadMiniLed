//
// Created by ubuntu on 06.08.23.
//

#include "LaunchControl.h"

#include <iostream>

LaunchControl::LaunchControl()
{
    potards.push_back(Potard(21, "Potard A1"));
    potards.push_back(Potard(22, "Potard A2"));
    potards.push_back(Potard(23, "Potard A3"));
    potards.push_back(Potard(24, "Potard A4"));
    potards.push_back(Potard(25, "Potard A5"));
    potards.push_back(Potard(26, "Potard A6"));
    potards.push_back(Potard(27, "Potard A7"));
    potards.push_back(Potard(28, "Potard A8"));
    potards.push_back(Potard(41, "Potard B1"));
    potards.push_back(Potard(42, "Potard B2"));
    potards.push_back(Potard(43, "Potard B3"));
    potards.push_back(Potard(44, "Potard B4"));
    potards.push_back(Potard(45, "Potard B5"));
    potards.push_back(Potard(46, "Potard B6"));
    potards.push_back(Potard(47, "Potard B7"));
    potards.push_back(Potard(48, "Potard B8"));
}

LaunchControl::~LaunchControl()
{
    // Vous pouvez nettoyer les ressources spécifiques à LaunchControl ici si
    // nécessaire
}

void LaunchControl::handleMidiMessage(double deltatime,
                                      std::vector<unsigned char> *message)
{
    // Potards

    if (message->size() == 3 &&
        (*message)[0] ==
            186) {  // Assurez-vous que c'est un message de contrôle
        int controlNumber = (*message)[1];
        int value = (*message)[2];

        for (const Potard &potard : potards) {
            if (potard.getMidiNumber() == controlNumber) {
                std::cout << potard.getLabel() << " | " << (value / 127.0) * 100
                          << "%"
                          << " |" << std::endl;
                // return;
                break;
            }
        }
    }

    // Ici, vous pouvez ajouter des fonctionnalités spécifiques pour traiter les
    // messages MIDI pour LaunchControl. Par exemple, allumer/éteindre des LEDs,
    // gérer des pads spécifiques, etc.

    if (!getShowMessage()) return;

    unsigned int nBytes = message->size();
    for (unsigned int i = 0; i < nBytes; i++) {
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    }
    if (nBytes > 0) {
        std::cout << "stamp = " << deltatime << std::endl;
    }
}
