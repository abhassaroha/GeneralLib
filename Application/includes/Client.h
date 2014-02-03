#ifndef SMC_CLIENT_H
#define SM_CLIENT_H

#include "common.h"

void client_connect(char* ip_addr, connection_type type);
void client_connect_server(char* ip_addr);
void client_connect_peer(char* ip_addr);

void client_send_message();
void client_recv_message();

#endif
