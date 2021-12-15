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
#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

typedef unsigned long bit_array_slot_t;

#ifdef __cplusplus
extern "C"{
#endif

typedef struct bit_array_s {
    bit_array_slot_t *data;
    unsigned int bitLength;
} *BitArray;

struct bit_arrays_s {
    BitArray (*create)(unsigned int bit_length);
    BitArray (*destroy)(BitArray bit_array);
    unsigned char (*get)(BitArray bit_array, unsigned int bit_index);
    BitArray (*clear)(BitArray bit_array);
    unsigned char (*set)(BitArray bit_array, unsigned int bit_index, unsigned char value);
};

extern struct bit_arrays_s BitArrays;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
