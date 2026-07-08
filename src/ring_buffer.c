#include "ring_buffer.h"
#include <string.h>

void ring_buffer_init(ring_buffer_t *q) {
    q->head  = 0;
    q->tail  = 0;
    q->count = 0;
    memset(q->buffer, 0, sizeof(q->buffer));
}

bool queue_push(ring_buffer_t *q, uint8_t value) {
    if (q->count >= QUEUE_SIZE) {
        return false;
    }
    q->buffer[q->tail] = value;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;
    return true;
}

bool queue_pop(ring_buffer_t *q, uint8_t *value) {
    if (q->count == 0) {
        return false;
    }
    *value = q->buffer[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;
    return true;
}

uint8_t queue_count(ring_buffer_t *q) {
    return q->count;
}

bool queue_is_full(ring_buffer_t *q) {
    return q->count >= QUEUE_SIZE;
}

bool queue_is_empty(ring_buffer_t *q) {
    return q->count == 0;
}