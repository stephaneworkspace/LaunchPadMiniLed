//
// Created by Stéphane on 06.08.23.
//

#include "LedController.h"

int main() {
    LedController controller;
    controller.setBPM(180);
    while (true) {
        controller.runSequence();
    }
    return 0;
}