#include <ringbuffer.h>

uint8_t ringbuf_read( ring_buffer_t* buf ) {
  if ( buf->pos == buf->ext ) { return '\0'; }
  char read = buf->buf[ buf->pos ];
  buf->pos = ( buf->pos < ( buf->len - 1 ) ) ? ( buf->pos + 1 ) : 0;
  return read;
}
