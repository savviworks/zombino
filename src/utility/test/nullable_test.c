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
#include "../nullable.h"

#define _BITS 9
static void testNullableVariable() {
    printf("--- %s ---\n", __func__);
    const unsigned int testVal = 254;

    // Test initialization
    struct { NULLABLE(_BITS, field); } test = { NULL_BIT(_BITS) };
    assert(NULL_BIT(_BITS) == test.field);

    // Test setting
    test.field = testVal;
    assert(NULL_BIT(_BITS) != test.field);
    assert(test.field == testVal);

}

static void testNullable8() {
    printf("--- %s ---\n", __func__);

    const unsigned int testVal = 254;

    // Test initialization
    struct { NULLABLE(8, field); } test = {NULL_8}, test2 = {NULL_8};
    assert(NULL_8 == test.field);

    // Test setting
    test.field = testVal;
    assert(NULL_8 != test.field);
    assert(test.field == testVal);

    // Test nullifying
    test.field = NULL_8;
    assert(NULL_8 == test.field);

    // Test setting with another null field
    test.field = testVal;
    assert(NULL_8 != test.field);
    assert(NULL_8 == test2.field);
    test.field = test2.field;
    assert(NULL_8 == test2.field);

    // Test nullable check for values
    assert(IS_NULLABLE_8(testVal));
    assert(IS_NULLABLE_8(NULL_8));
    assert(!IS_NULLABLE_8(257));
}

void testNullable() {
    testNullable8();
    testNullableVariable();
}