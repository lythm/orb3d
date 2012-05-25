#pragma once



struct ring_buffer
{
	unsigned int				bytes;
	int							start;
	int							end;
	char*						buffer;
};


int								rb_alloc(struct ring_buffer* rb, unsigned int bytes);

unsigned int					rb_read(struct ring_buffer* rb, char* buffer, unsigned int bytes);
unsigned int					rb_write(struct ring_buffer* rb, char* buffer, unsigned int bytes);

int								rb_is_full(struct ring_buffer* rb);
int								rb_is_empty(struct ring_buffer* rb);

unsigned int					rb_length(struct ring_buffer* rb);
unsigned int					rb_left(struct ring_buffer* rb);

void							rb_free(struct ring_buffer* rb);





