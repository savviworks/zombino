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
#ifndef EMULATOR_SERVO_H
#define EMULATOR_SERVO_H

#include <stdio.h>
#ifndef ARDUINO
class Servo {
    public:
        Servo();
        void attach(int pin);
        void attach(int pin, int min, int max);
        void write(int value);
        void writeMicroseconds(int value);
        bool attached();
        void detach();
    private:
        int pin;
        int min;
        int max;
};
#endif
#endif