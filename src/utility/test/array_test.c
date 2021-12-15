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
#include <assert.h>
#include <stdio.h>
#include "../array.h"

void testArray() {
    printf("--- %s ---\n", __func__);
    Array array = Arrays.create(10);
    assert(10 == array->size);
    array->data[0] = 'a';
    assert(array->data[0] == 'a');
    Arrays.clear(array);
    assert(array->data[0] == '\0');
    array = Arrays.destroy(array);
    assert(array == NULL);
}
