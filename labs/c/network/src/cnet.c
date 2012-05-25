#include "cnet.h"


unsigned int		cnet_init(struct cnet_inst* net)
{

	return 0;
}
void				cnet_fin(struct cnet_inst* net)
{

	
}

void				cnet_listen(struct cnet_inst* net, struct cnet_fd* fd)
{


}

void				cnet_connect(struct cnet_inst* net, struct cnet_fd* fd)
{

}

void				cnet_accept(struct cnet_inst* net, struct cnet_fd* fd)
{

}

unsigned int		cnet_recv(struct cnet_inst* net, struct cnet_fd* fd, void* buffer, unsigned int bytes)
{

	return 0;
}
void				cnet_send(struct cnet_inst* net, struct cnet_fd* fd, void* buffer, unsigned int bytes)
{

}

unsigned int		cnet_update(struct cnet_inst* net)
{

	return 0;
}

void				cnet_close(struct cnet_inst* net, struct cnet_fd* fd)
{

}

