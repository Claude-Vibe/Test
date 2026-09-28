#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Fixed-size byte FIFO. Caller supplies the storage (no malloc). */
typedef struct {
    uint8_t *buf;
    size_t   size;   /* capacity in bytes */
    size_t   head;   /* next write index */
    size_t   tail;   /* next read index */
    size_t   count;  /* bytes currently stored */
} ring_buffer_t;

bool   rb_init(ring_buffer_t *rb, uint8_t *storage, size_t size);
bool   rb_push(ring_buffer_t *rb, uint8_t data);
bool   rb_pop(ring_buffer_t *rb, uint8_t *out);
bool   rb_peek(const ring_buffer_t *rb, uint8_t *out);
size_t rb_count(const ring_buffer_t *rb);
bool   rb_is_empty(const ring_buffer_t *rb);
bool   rb_is_full(const ring_buffer_t *rb);
void   rb_clear(ring_buffer_t *rb);

#endif /* RING_BUFFER_H */
