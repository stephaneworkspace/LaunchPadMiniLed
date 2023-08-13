//
// Created by Stéphane on 13.08.23.
//
#include "Include/LedController.h"
#include <iostream>
#include <thread>
#include <chrono>

LedController::LedController() :
        midiout(nullptr),
        ledGrid{
                {0, 1, 2, 3, 4, 5, 6, 7},
                {16, 17, 18, 19, 20, 21, 22, 23},
                {32, 33, 34, 35, 36, 37, 38, 39},
                {48, 49, 50, 51, 52, 53, 54, 55},
                {64, 65, 66, 67, 68, 69, 70, 71},
                {80, 81, 82, 83, 84, 85, 86, 87},
                {96, 97, 98, 99, 100, 101, 102, 103},
                {112, 113, 114, 115, 116, 117, 118, 119}
        }
{
    // Initialization du MIDI out
    midiout = new RtMidiOut();

    int port = findLaunchpadPort();
    if (port != -1) {
        midiout->openPort(port);
    } else {
        std::cerr << "Launchpad Mini non trouvé!" << std::endl;
        delete midiout;
        midiout = nullptr;
    }

    // Configuration initiale des messages
    message.push_back(144);
    message.push_back(0);
    message.push_back(127);
}

LedController::~LedController() {
    delete midiout;
}

void LedController::setBPM(float bpm) {
    delayTime = (60.0f / bpm) * 1000 / 8;  // Conversion BPM en millisecondes pour chaque 1/8 de bar
}

int LedController::findLaunchpadPort() {
    unsigned int ports = midiout->getPortCount();
    for (unsigned int i = 0; i < ports; i++) {
        std::string portName = midiout->getPortName(i);
        if (portName.find("Launchpad Mini") != std::string::npos) {
            return i;
        }
    }
    return -1;
}

void LedController::runSequence() {
    if (!midiout) return;  // Si midiout n'est pas initialisé, quitter

    // Placez ici un commentaire pour jouer le son en boucle
    // Jouer le son en boucle

    int previousLed = -1;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            // Éteindre la LED précédente
            if (previousLed != -1) {
                message[1] = previousLed;
                message[2] = 0;
                midiout->sendMessage(&message);
            }

            // Allumer la LED actuelle
            message[1] = ledGrid[row][col];
            message[2] = 127;
            midiout->sendMessage(&message);

            previousLed = ledGrid[row][col];
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delayTime)));
        }
    }

    // Éteindre la dernière LED
    if (previousLed != -1) {
        message[1] = previousLed;
        message[2] = 0;
        midiout->sendMessage(&message);
    }
}
