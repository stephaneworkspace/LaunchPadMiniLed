//
// Created by Stéphane on 06.08.23.
//

#ifndef MIDI_CONTROLLER_H
#define MIDI_CONTROLLER_H

#include <iostream>
#include <vector>

#include "RtMidi.h"

class MidiController {
public:
    MidiController();
    ~MidiController();

    bool setup(int port);

    static void mycallback(double deltatime,
                           std::vector<unsigned char> *message, void *userData);

    void setShowMessages(bool show);
    virtual bool getShowMessage();

    // Méthodes communes à tous les appareils MIDI
    virtual void sendNoteOn(int note, int velocity);
    virtual void sendNoteOff(int note);

private:
    RtMidiIn *midiin;
    RtMidiOut *midiout;
    bool showMessages;

    virtual void handleMidiMessage(double deltatime,
                                   std::vector<unsigned char> *message);
};

#endif  // MIDI_CONTROLLER_H
