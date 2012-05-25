#include "ring_buffer.h"
#include <stdlib.h>
#include <memory.h>


int rb_alloc(struct ring_buffer* rb, unsigned int bytes)
{
	rb->buffer = (char*)malloc(bytes + 1);

	rb->bytes = bytes + 1;
	rb->start = 0;
	rb->end = 0;

	return rb->buffer != NULL;
}
unsigned int rb_length(struct ring_buffer* rb)
{
	if(rb->start <= rb->end)
	{
		return rb->end - rb->start;
	}

	return rb->bytes - rb->start + rb->end;

}
unsigned int rb_left(struct ring_buffer* rb)
{
	return rb->bytes - rb_length(rb) - 1;
}
unsigned int rb_read(struct ring_buffer* rb, char* buffer, unsigned int bytes)
{
	unsigned int bytes_left = rb_length(rb);

	unsigned int to_read = bytes_left < bytes ? bytes_left : bytes;
	
	unsigned int to_read_1 = (rb->start + to_read) <= rb->bytes ? to_read : (rb->bytes - rb->start);
	
	unsigned int to_read_2 = to_read - to_read_1;

	memcpy(buffer, rb->buffer + rb->start, to_read_1);

	if(to_read_2 != 0)
	{
		memcpy(buffer + to_read_1, rb->buffer, to_read_2);
	}

	rb->start = (rb->start + to_read) % rb->bytes;

	return to_read;
}

unsigned int rb_write(struct ring_buffer* rb, char* buffer, unsigned int bytes)
{
	unsigned int bytes_left = rb_left(rb);

	unsigned int to_write_1 = 0;
	unsigned int to_write_2 = 0;
	
	if(bytes > bytes_left)
	{
		return 0;
	}

	to_write_1 = (rb->end + bytes) <= rb->bytes ? 	bytes : (rb->bytes - rb->end);
	to_write_2 = bytes - to_write_1;

	memcpy(rb->buffer + rb->end, buffer, to_write_1);

	if(to_write_2 != 0)
	{
		memcpy(rb->buffer, buffer + to_write_1, to_write_2);
	}

	rb->end = (rb->end + bytes) % rb->bytes;

	return bytes;
}

int	rb_is_full(struct ring_buffer* rb)
{
	return ((rb->end + 1) % rb->bytes) == rb->start;
}
int	rb_is_empty(struct ring_buffer* rb)
{
	return rb->start == rb->end;
}

void rb_free(struct ring_buffer* rb)
{
	free(rb->buffer);
}
