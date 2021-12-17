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

#include "../queue.h"

void testQueue() {
    printf("--- %s ---\n", __func__);

    // Create queue
    Queue queue = Queues.create(64);
    assert(queue->itemCount == 0);

    // Add item
    assert(Queues.add(queue, 'a'));
    assert(queue->itemCount == 1);

    // Peek
    assert(Queues.peek(queue) == 'a');

    // Remove
    assert(Queues.remove(queue) == 'a');
    assert(queue->itemCount == 0);

    // Add multiple
    assert(Queues.add(queue, 'b'));
    assert(Queues.add(queue, 'c'));
    assert(queue->itemCount == 2);
    assert('b' == Queues.peek(queue));
    assert('b' == Queues.remove(queue));
    assert(queue->itemCount == 1);
    assert('c' == Queues.peek(queue));
    assert(Queues.add(queue, 'd'));
    assert('c' == Queues.remove(queue));
    assert('d' == Queues.remove(queue));
    assert(queue->itemCount == 0);
    assert(!Queues.remove(queue));
    assert(queue->itemCount == 0);

    // Clear
    Queues.add(queue, 'x');
    Queues.add(queue, 'y');
    Queues.add(queue, 'z');
    assert(queue->itemCount == 3);
    Queues.clear(queue);
    assert(!queue->itemCount);

    // Free up queue
    queue = Queues.destroy(queue);
    assert(NULL == queue);
}
