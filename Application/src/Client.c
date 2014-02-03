#include "Client.h"

void client_connect(char* ip_addr, connection_type type)
{
	if (type == SERVER) client_connect_server(ip_addr);
	else client_connect_peer(ip_addr);
}

void client_connect_server(char* ip_addr)
{
}

void client_connect_peer(char* ip_addr)
{
}
