//
// Created by Stéphane on 06.08.23.
//

#include "../MidiController.h"
#include "../Objects/Potard.h"

using namespace std;

class LaunchControl : public MidiController {
public:
    // Constructeur, destructeur, etc.
    LaunchControl();
    virtual ~LaunchControl();

    // Méthodes spécifiques à Launch Control
    void setButtonColor(int button, int color);

    // Implémentation de la méthode de gestion des messages MIDI pour Launch
    // Control
    void handleMidiMessage(double deltatime,
                           std::vector<unsigned char> *message) override;

private:
    vector<Potard> potards;
};
