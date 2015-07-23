//
// Created by kardudu on 13/07/15.
//


#include "Net.h"

Net::Net():m_port(3500),m_address("localhot") {}

Net::Net(int sd, struct sockaddr_in* address) : m_sd(sd) {}

