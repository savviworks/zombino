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
#include "tree.h"

static Tree trees_create(void *value) {
    Tree tree = calloc(1, sizeof(struct tree_s));
    tree->value = value;
    tree->firstChild = NULL;
    tree->nextSibling = NULL;
    tree->parent = NULL;
    return tree;
}

static Tree tree_insertChild(Tree parent, void *value) {
    Tree child = trees_create(value);
    child->parent = parent;
    if (parent != NULL) {
        child->nextSibling = parent->firstChild;
        parent->firstChild = child;
    }

    return child;
}

static Tree tree_destroy(Tree tree) {
    if (tree != NULL) {
        // TODO destroy children
        free(tree);
    }

    return NULL;
}

trees Trees = {
    .create = trees_create,
    .insertChild = tree_insertChild,
    .destroy = tree_destroy
};
