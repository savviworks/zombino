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
#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct list_item_s {
    void *item;
    struct list_item_s *next;
} *ListItem;

typedef struct list_s {
    ListItem first;
    ListItem last;
    int size;
} *List;

typedef struct list_iterator_s {
    List list;
    ListItem current;
    ListItem previous;
} *ListIterator;

typedef struct {
    // List lifetime
    List (*create)();
    List (*destroy)(List list) __attribute__((nonnull));

    // List manipulation
    void (*add)(List list, void *item) __attribute__((nonnull (1)));
    void (*addFirst)(List list, void *item) __attribute__((nonnull (1)));
    void *(*remove)(List list, void *item) __attribute__((nonnull (1)));
    void *(*item)(List list, int i) __attribute__((nonnull (1)));

    // Iterator API
    ListIterator (*iter)(List list) __attribute__((nonnull (1)));
    unsigned char (*iterHasNext)(ListIterator iter) __attribute__((nonnull (1)));
    void *(*iterNext)(ListIterator iter) __attribute__((nonnull (1)));
    ListIterator (*iterRemove)(ListIterator iter) __attribute__((nonnull (1)));
    ListIterator (*iterDestroy)(ListIterator iter) __attribute__((nonnull (1)));
    ListIterator (*iterReset)(ListIterator iter) __attribute__((nonnull (1)));
} lists_t;

extern lists_t Lists;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
