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
#include "queue.h"

static Queue queues_create(int size) {
    Queue queue = calloc(1, sizeof(struct queue_s));
    queue->data = calloc(size, sizeof(char));
    queue->itemCount = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->size = size;
    return queue;
}

static Queue queue_destroy(Queue queue) {
    if (queue != NULL) {
        if(queue->data != NULL) {
            free(queue->data);
            queue->data = NULL;
        }

        free(queue);
    }

    return NULL;
}

static char queue_peek(Queue queue) {
    return (queue != NULL) ? queue->data[queue->front] : 0;
}

static char queue_isFull(Queue queue) {
    return (queue != NULL) ? queue->itemCount == queue->size : 1;
}

static char queue_add(Queue queue, char item) {
    if (queue_isFull(queue)) {
        return 0;
    }

    if (queue->rear == queue->size - 1) {
        queue->rear = -1;
    }

    queue->rear++;
    queue->data[queue->rear] = item;
    queue->itemCount++;
    return 1;
}

static char queue_remove(Queue queue) {
    if (queue == NULL) {
        return 0;
    } else if (queue->itemCount == 0) {
        return 0;
    }

    char item = queue->data[queue->front];
	queue->front++;

    if(queue->front == queue->size) {
        queue->front = 0;
    }

    queue->itemCount--;
    return item;
}

static Queue queue_clear(Queue queue) {
    if (queue == NULL || queue->data == NULL) {
        return queue;
    }

    int i = 0;
    for (char *d = queue->data; i < queue->size; i++, d++) {
        *d = 0;
    }

    queue->front = 0;
    queue->rear = -1;
    queue->itemCount = 0;
    return queue;
}

queues_t Queues = {
    .create = queues_create,
    .destroy = queue_destroy,
    .add = queue_add,
    .isFull = queue_isFull,
    .peek = queue_peek,
    .remove = queue_remove,
    .clear = queue_clear
};
