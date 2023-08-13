//
// Created by Stéphane on 06.08.23.
//

#include <signal.h>

#include <atomic>
#include <chrono>
#include <thread>

#include "Devices/LaunchControl.h"
#include "MidiController.h"

std::atomic<bool> done(false);

// Gestionnaire de signal pour CTRL+C
void signalHandler(int signum) { done = true; }

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