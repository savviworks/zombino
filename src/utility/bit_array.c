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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_array.h"

enum {
    BIT_ARRAY_SLOT_BYTES = sizeof(bit_array_slot_t),
    BIT_ARRAY_SLOT_BITS = sizeof(bit_array_slot_t) << 3
};

static BitArray bit_arrays_create(unsigned int bit_length) {
    unsigned int length = (bit_length - 1)/BIT_ARRAY_SLOT_BITS + 1;
    BitArray bit_array = calloc(1, sizeof(struct bit_array_s));
    bit_array->data = calloc(length, BIT_ARRAY_SLOT_BYTES);
    bit_array->bitLength = bit_length;
    return bit_array;
}

static BitArray bit_array_destroy(BitArray bit_array) {
    if (bit_array != NULL) {
        free(bit_array->data);
        bit_array->data = NULL;
        free(bit_array);
    }

    return NULL;
}

static unsigned char bit_array_set(BitArray bit_array, unsigned int bit_index, unsigned char value) {
    if (bit_array == NULL || bit_index >= bit_array->bitLength) {
        return 0; // Index out of bounds
    }

    const unsigned int slot_index = bit_index / BIT_ARRAY_SLOT_BITS;
    const unsigned int slot_bit = bit_index % BIT_ARRAY_SLOT_BITS;
    const unsigned long bit_mask = 1 << slot_bit;

    unsigned char curVal = (bit_array->data[slot_index] & bit_mask) ? 1 : 0; 
    if (value) {
        bit_array->data[slot_index] |= bit_mask;
    } else {
        bit_array->data[slot_index] &= ~bit_mask;
    }

    return curVal != value;
}

static unsigned char bit_array_get(BitArray bit_array, unsigned int bit_index) {
    if (bit_array == NULL || bit_index >= bit_array->bitLength) {
        return 0;
    }

    const unsigned int slot_index = bit_index / BIT_ARRAY_SLOT_BITS;
    const unsigned int slot_bit = bit_index % BIT_ARRAY_SLOT_BITS;
    const bit_array_slot_t bit_mask = 1 << slot_bit;

    return (bit_array->data[slot_index] & bit_mask) ? 1 : 0;
}

static BitArray bit_array_clear(BitArray bit_array) {
    if (bit_array != NULL) {
        unsigned int length = (bit_array->bitLength - 1)/BIT_ARRAY_SLOT_BITS + 1;
        memset(bit_array->data, 0, BIT_ARRAY_SLOT_BYTES * length);
    }

    return bit_array;    
}

struct bit_arrays_s BitArrays = {
    .clear = bit_array_clear,
    .create = bit_arrays_create,
    .destroy = bit_array_destroy,
    .get = bit_array_get,
    .set = bit_array_set
};
