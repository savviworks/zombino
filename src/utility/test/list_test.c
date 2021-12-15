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
#include <string.h>

#include "../list.h"

void testAddFirst() {
    List list = Lists.create();
    assert(list);
    Lists.addFirst(list, "b");
    assert(list->size == 1);
    Lists.addFirst(list, "a");
    assert(list->size == 2);
    assert(!strcmp(Lists.item(list, 0), "a"));
    assert(!strcmp(Lists.item(list, 1), "b"));
}

void testList() {
    printf("--- %s ---\n", __func__);
    char *value;

    // Test creation
    List list = Lists.create();

    // Test adding
    Lists.add(list, "one");
    Lists.add(list, "two");
    Lists.add(list, "three");
    assert(list->size == 3);

    // Test indexing
    value = Lists.item(list, 0);
    assert(!strcmp("one", value));
    value = Lists.item(list, 1);
    assert(!strcmp("two", value));
    value = Lists.item(list, 2);
    assert(!strcmp("three", value));
    value = Lists.item(list, 4);
    assert(NULL == value);

    // Test iterating
    ListIterator iter = Lists.iter(list);
    int i = 0;
    while (Lists.iterHasNext(iter)) {
        i++;
        char *item = Lists.iterNext(iter);
        assert(NULL != item);
    }

    assert(i == list->size);
    
    // Test iterator reset
    iter = Lists.iterReset(iter);
    i = 0;
    while (Lists.iterHasNext(iter)) {
        i++;
        char *item = Lists.iterNext(iter);
        assert(NULL != item);
    }

    assert(i == list->size);
    iter = Lists.iterDestroy(iter);

    // Test removing
    value = Lists.remove(list, "two");
    assert(list->size == 2);
    assert(!strcmp(value, "two"));
    value = Lists.remove(list, "one");
    assert(list->size == 1);
    assert(!strcmp(value, "one"));
    value = Lists.remove(list, "three");
    assert(list->size == 0);
    assert(!strcmp(value, "three"));

    // Test iterator-based removal
    Lists.add(list, "first");
    Lists.add(list, "two");
    Lists.add(list, "middle");
    Lists.add(list, "middle2");
    Lists.add(list, "ignore");
    Lists.add(list, "add");
    Lists.add(list, "beforeLast");
    int expectedSize = list->size;
    iter = Lists.iter(list);
    while(Lists.iterHasNext(iter)) {
        char *value = Lists.iterNext(iter);
        printf("\t%s\n", value);
        if (!strcmp(value, "first") ||
            !strcmp(value, "middle") ||
            !strcmp(value, "last") ||
            !strcmp(value, "beforeLast") ||
            !strcmp(value, "middle2") ||
            !strcmp(value, "add")) {
            Lists.iterRemove(iter);
            expectedSize--;
            assert(expectedSize == list->size);
        }

        if (!strcmp(value, "add")) {
            // Add after removing
            Lists.add(list, "last");
            expectedSize++;
            assert(expectedSize == list->size);
        }
    }

    iter = Lists.iterDestroy(iter);

    // Test destroying
    list = Lists.destroy(list);
    assert(NULL == list);

    testAddFirst();
}
