//
// Created by Stéphane on 06.08.23.
//

#include <signal.h>

#include <atomic>
#include <chrono>
#include <thread>

#include <vector>
#include <iostream>

#include "Devices/LaunchControl.h"
#include "MidiController.h"

std::atomic<bool> done(false);

// Gestionnaire de signal pour CTRL+C
void signalHandler(int signum) { done = true; }
/*
int main() {
    RtMidiOut *midiout = 0;

    try {
        midiout = new RtMidiOut();
    } catch (RtMidiError &error) {
        error.printMessage();
        return 0;
    }

    // Cherchez le Launchpad Mini parmi les ports disponibles.
    unsigned int ports = midiout->getPortCount();
    int launchpadPort = -1;
    for (unsigned int i = 0; i < ports; i++) {
        std::string portName = midiout->getPortName(i);
        if (portName.find("Launchpad Mini") != std::string::npos) {
            launchpadPort = i;
            break;
        }
    }

    if (launchpadPort == -1) {
        std::cout << "Launchpad Mini non trouvé!" << std::endl;
        delete midiout;
        return 0;
    }

    // Ouvrez le port MIDI pour le Launchpad Mini.
    midiout->openPort(launchpadPort);

    // Envoyez un message pour allumer une LED.
    // Comme dans l'exemple Python, nous utilisons une note avec une vélocité.
    // Vous devrez peut-être ajuster le numéro de note et la vélocité.
    std::vector<unsigned char> message;
    message.push_back(144); // Note on
    message.push_back(60);  // Note number
    message.push_back(127); // Velocity
    midiout->sendMessage(&message);

    delete midiout;
    return 0;
}
*/

int main() {
    RtMidiOut *midiout = 0;

    try {
        midiout = new RtMidiOut();
    } catch (RtMidiError &error) {
        error.printMessage();
        return 0;
    }

    unsigned int ports = midiout->getPortCount();
    int launchpadPort = -1;
    for (unsigned int i = 0; i < ports; i++) {
        std::string portName = midiout->getPortName(i);
        if (portName.find("Launchpad Mini") != std::string::npos) {
            launchpadPort = i;
            break;
        }
    }

    if (launchpadPort == -1) {
        std::cout << "Launchpad Mini non trouvé!" << std::endl;
        delete midiout;
        return 0;
    }

    midiout->openPort(launchpadPort);

    // Tableau 2D prérempli avec les codes LED
    int ledGrid[8][8] = {
            {0, 1, 2, 3, 4, 5, 6, 7},
            {16, 17, 18, 19, 20, 21, 22, 23},
            {32, 33, 34, 35, 36, 37, 38, 39},
            {48, 49, 50, 51, 52, 53, 54, 55},
            {64, 65, 66, 67, 68, 69, 70, 71},
            {80, 81, 82, 83, 84, 85, 86, 87},
            {96, 97, 98, 99, 100, 101, 102, 103},
            {112, 113, 114, 115, 116, 117, 118, 119}
    };

    std::vector<unsigned char> message;
    message.push_back(144); // Note on
    message.push_back(0);   // Placeholder pour le numéro de note
    message.push_back(127); // Velocity

    int previousLed = -1;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            // Éteindre la LED précédente
            if (previousLed != -1) {
                message[1] = previousLed;
                message[2] = 0; // Vélocité à 0 pour éteindre
                midiout->sendMessage(&message);
            }

            // Allumer la LED actuelle
            message[1] = ledGrid[row][col];
            message[2] = 127; // Vélocité pour allumer
            midiout->sendMessage(&message);

            previousLed = ledGrid[row][col];

            std::this_thread::sleep_for(std::chrono::milliseconds (100));
        }
    }

    // Éteindre la dernière LED
    if (previousLed != -1) {
        message[1] = previousLed;
        message[2] = 0; // Vélocité à 0 pour éteindre
        midiout->sendMessage(&message);
    }

    delete midiout;
    return 0;
}

/*
int main()
{
    // Pour de l'appareil
    const int PORT = 10;
    const bool SHOW_MESSAGE = true;

    signal(SIGINT, signalHandler);

    MidiController controller;
    controller.setShowMessages(SHOW_MESSAGE);
    if (!controller.setup(PORT))
    {
        std::cout << "Erreur lors de la configuration du contrôleur MIDI." <<
std::endl; return 1;
    }
    while (!done)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Programme terminé." << std::endl;

    return 0;
}
 */
/*
int main()
{
    // Pour de l'appareil
    const int PORT = 1;
    const bool SHOW_MESSAGE = false;

    signal(SIGINT, signalHandler);

    LaunchControl
        controller;  // Utilisez LaunchControl plutôt que MidiController
    controller.setShowMessages(SHOW_MESSAGE);
    if (!controller.setup(PORT)) {
        std::cout << "Erreur lors de la configuration du contrôleur MIDI."
                  << std::endl;
        return 1;
    }

    while (!done) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Programme terminé." << std::endl;

    return 0;
}
*/