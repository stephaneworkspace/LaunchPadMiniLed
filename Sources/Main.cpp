//
// Created by Stéphane on 06.08.23.
//

#include "Include/LedController.h"

int main() {
    LedController controller;
    controller.setBPM(180);
    while (true) {
        controller.runSequence();
    }
    return 0;
}