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
#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct queue_s {
    char *data;
    volatile int size;
    volatile int front;
    volatile int rear;
    volatile int itemCount;
} *Queue;

typedef struct {
    Queue (*create)(int size);
    Queue (*destroy)(Queue queue) __attribute__((nonnull));
    char (*peek)(Queue queue) __attribute__((nonnull));
    char (*isFull)(Queue queue) __attribute__((nonnull));
    char (*add)(Queue queue, char item) __attribute__((nonnull (1)));
    char (*remove)(Queue queue) __attribute__((nonnull));
    Queue (*clear)(Queue queue) __attribute__((nonnull));
} queues_t;

extern queues_t Queues;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
