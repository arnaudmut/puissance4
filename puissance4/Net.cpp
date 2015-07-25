//
// Created by kardudu on 13/07/15.
//


#include "Net.h"

Net::Net():m_port(35000),m_address("localhost") {}

Net::Net(int sd, struct sockaddr_in* address) : m_sd(sd) {}

