#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define QUEUE_SIZE 32

typedef struct {
    uint8_t buffer[QUEUE_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} ring_buffer_t;

void    ring_buffer_init(ring_buffer_t *q);
bool    queue_push(ring_buffer_t *q, uint8_t value);
bool    queue_pop(ring_buffer_t *q, uint8_t *value);
uint8_t queue_count(ring_buffer_t *q);
bool    queue_is_full(ring_buffer_t *q);
bool    queue_is_empty(ring_buffer_t *q);

#endif