//
// Created by Stéphane on 13.08.23.
//

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "RtMidi.h"
#include <vector>

class LedController {
public:
    LedController();
    ~LedController();

    void setBPM(float bpm);
    void runSequence();

private:
    RtMidiOut *midiout;
    std::vector<unsigned char> message;
    const int ledGrid[8][8];
    float delayTime;

    int findLaunchpadPort();
};

#endif
