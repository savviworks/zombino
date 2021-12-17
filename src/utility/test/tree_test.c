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

#include "../tree.h"

void testTree() {
    printf("--- %s ---\n", __func__);
    Tree tree = Trees.create("a");
    assert("a" == tree->value);
    assert(NULL == tree->parent);
    assert(NULL == tree->firstChild);
    assert(NULL == tree->nextSibling);

    Tree child = Trees.insertChild(tree, "a.1");
    assert(child->value == "a.1");
    assert(child->parent == tree);
    assert(child->firstChild == NULL);
    assert(child->nextSibling == NULL);
    assert(tree->firstChild == child);
    tree = Trees.destroy(tree);
    assert (NULL == tree);
}
