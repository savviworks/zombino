/*
  Copyright (c) Martin Sawicki. All right reserved.

  This file is part of the Zombino project.

  Zombino is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Zombino is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Zombino.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef ARDUINO

#include <stdio.h>
#include "emulator_servo.h"

Servo::Servo() {
    this->pin = -1;
}

void Servo::attach(int pin) {
    this->attach(pin, 544, 2400);
}

void Servo::attach(int pin, int min, int max) {
    this->pin = pin;
    this->min = min;
    this->max = max;
}

void Servo::write(int value) {
    // TODO:
}

void Servo::writeMicroseconds(int value) {
    printf("Servo signal: %d\n", value);
}

bool Servo::attached() {
    return (this->pin > -1);
}

void Servo::detach() {
    this->pin = -1;
}

#endif