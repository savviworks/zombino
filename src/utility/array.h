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
#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct array_s {
    char *data;
    int size;
} *Array;

typedef struct {
    Array (*create)(int size);
    Array (*destroy)(Array array) __attribute__((nonnull));
    void (*clear)(Array array) __attribute__((nonnull));
} arrays_t;

extern arrays_t Arrays;

#ifdef __cplusplus
} //extern "C"{
#endif

#endif
