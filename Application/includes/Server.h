#ifndef SMC_SERVER_H
#define SMC_SERVER_H

#include "common.h"

void server_start();
void server_connect(char* ip_addr, connection_type type);

void server_send_message();
void server_recv_message();

#endif
