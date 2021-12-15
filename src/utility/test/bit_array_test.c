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
#include <assert.h>

#include "../bit_array.h"

static void testBitLength(unsigned int bit_length) {
    printf("--- %s ---\n", __func__);

    // Create bit array
    BitArray bits = BitArrays.create(bit_length);
    assert(bits);
    assert(bit_length == bits->bitLength);

    // Check bits are 0 by default
    for (unsigned int i = 0; i < bit_length; i++) {
        assert(!BitArrays.get(bits, i));
    }

    // Set first bit
    assert(BitArrays.set(bits, 0, 1));
    assert(BitArrays.get(bits, 0));

    // Reset first bit
    assert(BitArrays.set(bits, 0, 0));
    assert(!BitArrays.get(bits, 0));

    // Set last bit
    assert(BitArrays.set(bits, bit_length - 1, 1));
    assert(BitArrays.get(bits, bit_length - 1));

    // Reset last bit
    assert(BitArrays.set(bits, bit_length - 1, 0));
    assert(!BitArrays.get(bits, bit_length - 1));

    // Test bit pairs
    for(unsigned int i = 0; i < bit_length - 1; i++) {
        // Set pair of bits
        BitArrays.set(bits, i, 1);
        BitArrays.set(bits, i+1, 1);
        if (i > 0)
            assert(!BitArrays.get(bits, i - 1));
        assert(BitArrays.get(bits, i));
        assert(BitArrays.get(bits, i+1));
        if (i < bit_length - 2)
            assert(!BitArrays.get(bits, i+2));

        // Reset second of consecutive set bits
        BitArrays.set(bits, i+1, 0);
        if (i > 0)
            assert(!BitArrays.get(bits, i - 1));
        assert(BitArrays.get(bits, i));
        assert(!BitArrays.get(bits, i+1));
        if (i < bit_length - 2)
            assert(!BitArrays.get(bits, i+2));

        BitArrays.set(bits, i, 0);
        assert(!BitArrays.get(bits, i));
    }

    // Test clearing
    assert(BitArrays.set(bits, 0, 1));
    assert(BitArrays.set(bits, bit_length - 1, 1));
    assert(BitArrays.get(bits, 0));
    assert(BitArrays.get(bits, bit_length - 1));
    assert(BitArrays.clear(bits));
    for (int i = 0; i < bit_length; i++) {
        assert(!BitArrays.get(bits, i));
    }

    // Test setting already set
    assert(BitArrays.set(bits, 0, 1));
    assert(!BitArrays.set(bits, 0, 1));
    assert(BitArrays.set(bits, 0, 0));
    assert(!BitArrays.set(bits, 0, 0));

    // Destroy bit array
    bits = BitArrays.destroy(bits);
    assert(!bits);
}

void testBitArray() {
    printf("--- %s ---\n", __func__);
    testBitLength(12);
    testBitLength(70);
}
