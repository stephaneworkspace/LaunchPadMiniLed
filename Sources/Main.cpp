//
// Created by Stéphane on 06.08.23.
//

#include "LedController.h"

int main() {
    LedController controller;
    controller.setBPM(180);
    controller.runSequence();
    return 0;
}