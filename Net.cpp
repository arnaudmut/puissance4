//
// Created by kardudu on 13/07/15.
//


#include "Net.h"

Net::Net():m_address("localhot"),m_port(3500) {}

Net::Net(int sd, struct sockaddr_in* address) : m_sd(sd) {}

