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
#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct tree_s {
    struct tree_s *firstChild;
    struct tree_s *nextSibling;
    struct tree_s *parent;
    void *value;
} * Tree;

typedef struct {
    Tree (*create)(void *value);
    Tree (*destroy)(Tree tree) __attribute__((nonnull));
    Tree (*insertChild)(Tree tree, void *value) __attribute__((nonnull (1)));
} trees;

extern trees Trees;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
