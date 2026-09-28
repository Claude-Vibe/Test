#include "ring_buffer.h"

bool rb_init(ring_buffer_t *rb, uint8_t *storage, size_t size)
{
    if (rb == NULL || storage == NULL || size == 0) {
        return false;
    }
    rb->buf  = storage;
    rb->size = size;
    rb_clear(rb);
    return true;
}

bool rb_push(ring_buffer_t *rb, uint8_t data)
{
    if (rb_is_full(rb)) {
        return false;
    }
    rb->buf[rb->head] = data;
    rb->head = (rb->head + 1) % rb->size;
    rb->count++;
    return true;
}

bool rb_pop(ring_buffer_t *rb, uint8_t *out)
{
    if (out == NULL || rb_is_empty(rb)) {
        return false;
    }
    *out = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    rb->count--;
    return true;
}

bool rb_peek(const ring_buffer_t *rb, uint8_t *out)
{
    if (out == NULL || rb_is_empty(rb)) {
        return false;
    }
    *out = rb->buf[rb->tail];
    return true;
}

size_t rb_count(const ring_buffer_t *rb)
{
    return rb->count;
}

bool rb_is_empty(const ring_buffer_t *rb)
{
    return rb->count == 0;
}

bool rb_is_full(const ring_buffer_t *rb)
{
    return rb->count == rb->size;
}

void rb_clear(ring_buffer_t *rb)
{
    rb->head  = 0;
    rb->tail  = 0;
    rb->count = 0;
}
