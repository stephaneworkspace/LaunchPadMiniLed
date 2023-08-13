//
// Created by Stéphane on 06.08.23.
//

#include "MidiController.h"

MidiController::MidiController() : showMessages(true)
{
    try {
        midiin = new RtMidiIn();
    }
    catch (RtMidiError &error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }

    // Créez un objet RtMidiOut pour l'envoi de messages
    midiout = new RtMidiOut();
    if (midiout->getPortCount() > 0) {
        // Ici, j'ouvre le premier port disponible. Vous pouvez choisir le port
        // spécifique que vous souhaitez.
        midiout->openPort(1);
    }
    else {
        // Gérer l'erreur si aucun port MIDI out n'est disponible
    }
}

MidiController::~MidiController()
{
    delete midiin;
    if (midiout) {
        if (midiout->isPortOpen()) {
            midiout->closePort();
        }
        delete midiout;
    }
}

bool MidiController::setup(int port)
{
    if (midiin->getPortCount() == 0) {
        std::cout << "Aucun appareil MIDI trouvé!" << std::endl;
        return false;
    }

    unsigned int nPorts = midiin->getPortCount();
    for (unsigned int i = 0; i < nPorts; i++) {
        std::cout << "Port " << i << ": " << midiin->getPortName(i)
                  << std::endl;
    }

    midiin->setCallback(&MidiController::mycallback, this);
    midiin->ignoreTypes(true, true, true);
    midiin->openPort(port);
    return true;
}

void MidiController::mycallback(double deltatime,
                                std::vector<unsigned char> *message,
                                void *userData)
{
    MidiController *controller = static_cast<MidiController *>(userData);
    controller->handleMidiMessage(deltatime, message);
}

void MidiController::setShowMessages(bool show) { showMessages = show; }

bool MidiController::getShowMessage() { return showMessages; }

void MidiController::sendNoteOn(int note, int velocity)
{
    std::vector<unsigned char> message;
    // Status byte pour note on message (canal 1)
    message.push_back(0x90);
    message.push_back(note);
    message.push_back(velocity);
    midiout->sendMessage(&message);
}

void MidiController::sendNoteOff(int note)
{
    std::vector<unsigned char> message;
    // Status byte pour note off message (canal 1)
    message.push_back(0x80);
    message.push_back(note);
    message.push_back(0);  // Velocity est généralement 0 pour note off
    midiout->sendMessage(&message);
}

void MidiController::handleMidiMessage(double deltatime,
                                       std::vector<unsigned char> *message)
{
    if (!showMessages) return;
    unsigned int nBytes = message->size();
    for (unsigned int i = 0; i < nBytes; i++) {
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    }
    if (nBytes > 0) std::cout << "stamp = " << deltatime << std::endl;
}
