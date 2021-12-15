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
#include "list.h"

static ListIterator list_iterator_remove(ListIterator iter) {
    if (iter == NULL || iter->current == NULL) {
        // Can't remove because nothing fetched yet
    } else if (iter->current == iter->list->first) {
        // Removing head of list
        iter->list->first = iter->current->next;
        iter->previous = NULL;
        if (iter->current == iter->list->last) {
            iter->list->last = NULL;
        }

        free(iter->current);
        iter->current = NULL;
        iter->list->size--;
    } else if (iter->previous != NULL) {
        // Removing from middle of list
        iter->previous->next = iter->current->next;
        if (iter->current == iter->list->last) {
            iter->list->last = NULL;
        }

        free(iter->current);
        iter->current = iter->previous;
        iter->previous = NULL;
        iter->list->size--;
    } else {
        // Already removed as there is no previous item 
    }

    return iter;
}

static ListIterator list_iterator_destroy(ListIterator iter) {
    if (iter != NULL) {
        free(iter);
    }

    return NULL;
}

static unsigned char list_iterator_hasNext(ListIterator iter) {
    if (iter == NULL || iter->list == NULL) {
        return 0;
    } else if (iter->current != NULL) {
        return iter->current->next != NULL;
    } else if (iter->previous != NULL) {
        return iter->previous->next != NULL;
    } else {
        return iter->list->first != NULL;
    }
}

static void *list_iterator_next(ListIterator iter) {
    if (iter == NULL) {
        return NULL;
    } else if (iter->current != NULL) {
        // Middle of list
        iter->previous = iter->current;
        iter->current = iter->current->next;
    } else {
        // Head of list
        iter->current = iter->list->first;
        iter->previous = NULL;
    }

    return iter->current->item;
}

static ListIterator list_iterator_reset(ListIterator iter) {
    if (iter != NULL && iter->list != NULL) {
        iter->current = NULL;
        iter->previous = NULL;
    }

    return iter;
}

static ListIterator list_iter(List list) {
    if (list == NULL) {
        return NULL;
    }

    ListIterator iter = calloc(1, sizeof(struct list_iterator_s));
    iter->list = list;
    iter = list_iterator_reset(iter);
    return iter;
}

static void *list_remove(List list, void *item) {
    if (list == NULL) {
        return NULL;
    }

    ListItem prev_li = NULL;
    for (ListItem li = list->first; li != NULL; prev_li = li, li = li->next) {
        if (li->item != item) {
            continue;
        } else {
            ListItem next = li->next;
            void *item = li->item;
            list->size--;
            if (next == NULL)
                list->last = NULL;

            if (prev_li == NULL) {
                list->first = next;
            } else {
                prev_li->next = next;
            }

            // TODO: free(li);
            li = NULL;

            return item;
        }
    }

    return NULL;
}

static void list_addFirst(List list, void *item) {
    if (list == NULL) {
        return;
    }

    ListItem li = calloc(1, sizeof(struct list_item_s));
    li->item = item;
    li->next = list->first;
    list->first = li;
    list->size++;
}

static void list_add(List list, void *item) {
    if (list == NULL) {
        return;
    }

    ListItem li = calloc(1, sizeof(struct list_item_s));
    li->item = item;
    li->next = NULL;

    if (list->last != NULL) {
        list->last->next = li;
    }

    list->last = li;

    if (list->first == NULL) {
        list->first = li;
    }

    list->size++;
}

static List lists_create() {
    List list = calloc(1, sizeof(struct list_s));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

static List list_destroy(List list) {
    if (list != NULL) {
        if (list->first != NULL) {
            if (list->last != list->first) {
                free(list->last);
            }

            // TODO: free all members
            free(list->first);
            list->first = NULL;
            list->last = NULL;
        }

        free(list);
    }

    return NULL;
}

void *list_item(List list, int index) {
    if (list == NULL) {
        return NULL;
    }

    int i = 0;
    ListItem li = NULL;
    for (li = list->first; li != NULL && i < index; li = li->next, i++);
    if (li == NULL) {
        return NULL;
    } else if (i == index) {
        return li->item;
    } else {
        return NULL;
    }
}

lists_t Lists = {
    .add = list_add,
    .addFirst = list_addFirst,
    .create = lists_create,
    .destroy = list_destroy,
    .remove = list_remove,
    .item = list_item,
    .iterHasNext = list_iterator_hasNext,
    .iterNext = list_iterator_next,
    .iterDestroy = list_iterator_destroy,
    .iter = list_iter,
    .iterReset = list_iterator_reset,
    .iterRemove = list_iterator_remove
};
