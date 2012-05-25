// echo_server.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

#include "..\include\cnet.h"

int main(int argc, char* argv[])
{
	struct cnet_inst net;

	if(cnet_error_ok != cnet_init(&net))
	{
		
		return -1;
	}


	while(1)
	{
		cnet_update(&net);
	}

	cnet_fin(&net);


	return 0;
}

