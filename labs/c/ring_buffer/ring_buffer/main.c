// ring_buffer.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

#include "ring_buffer.h"



int main(int argc, char* argv[])
{
	unsigned int left = 0;
	unsigned int size = 0;
	unsigned int i = 0;
	struct ring_buffer rb;
	char buffer[100];

	for(i = 0; i < 100; ++i)
	{
		buffer[i] = i;
	}
	
	rb_alloc(&rb, 100);

	for(i = 0; i < 100; ++i)
	{
		rb_write(&rb, buffer, 33);
		rb_read(&rb, buffer, 32);
	}
	

	printf("%d,%d  %d,%d\n", rb_length(&rb), rb_left(&rb), rb_is_full(&rb), rb_is_empty(&rb));

	rb_free(&rb);

	
	return 0;
}

