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
#include <string.h>
#include <stdlib.h>

#include "array.h"

static Array arrays_create(int size) {
    Array array = calloc(1, sizeof(struct array_s));
    array->data = calloc(size, sizeof(char));
    array->size = size;
    return array;
}

static Array array_destroy(Array array) {
    if (array != NULL) {
        if (array->data != NULL) {
            free(array->data);
            array->data = NULL;
        }

        free(array);
    }

    return NULL;
}

static void array_clear(Array array) {
    if (array != NULL && array->data != NULL) {
        memset(array->data, '\0', array->size * sizeof(char));
    }
}

arrays_t Arrays = {
    .create = arrays_create,
    .destroy = array_destroy,
    .clear = array_clear
};
