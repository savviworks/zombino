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
#ifndef ZOMBINO_H
#define ZOMBINO_H

// TODO: This needs to be replaced with something from Arduino libraries
enum MAX_PINS {
    MAX_PINS = 32
};

enum {
  ZOMBINO_ARGS_MAX = 6,
  ZOMBINO_BUFFER_SIZE = 64,
  PIN_OUT_MIN = 0,
  PIN_OUT_MAX = (1 << 8) - 1,
  PIN_OUT_MID = (PIN_OUT_MIN + PIN_OUT_MAX) >> 1,
  PIN_TONE_MIN = 40,
  PIN_TONE_MAX = 15000,
  PIN_TONE_MID = (PIN_TONE_MAX + PIN_TONE_MIN) >> 1,
  PIN_SERVO_MIN = 1500,
  PIN_SERVO_MAX = 2500,
  PIN_SERVO_MID = (PIN_SERVO_MIN + PIN_SERVO_MAX) >> 1,
  PIN_IN_MIN = 0,
  PIN_IN_MAX = (1 << 10)-1,
  PIN_IN_MID = (PIN_IN_MIN + PIN_IN_MAX) >> 1
};

struct zombino_s {
  void (*setup)();
  void (*loop)();
};

extern struct zombino_s Zombino;

int splitTokens(char text[], char *tokens[], int tokensMax, char delim);

#endif
