#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdint.h>

typedef struct {
    int32_t len;
    volatile uint8_t* buf;
    volatile int32_t pos;
    volatile int32_t ext;
} ring_buffer_t;

// macro to write to a buffer
#define ringbuf_write( rb, x ) \
  rb.buf[ rb.ext ] = x; \
  if ( ( rb.ext + 1 ) >= rb.len ) { rb.ext = 0; } \
  else { rb.ext = rb.ext + 1; }

//read from a buffer
uint8_t ringbuf_read( ring_buffer_t* buf );

#endif
