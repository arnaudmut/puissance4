//
// Created by kardudu on 11/07/15.
//
/*
   TCPAcceptor.h

   TCPAcceptor class interface. TCPAcceptor provides methods to passively
   establish TCP/IP connections with clients.

   ------------------------------------------

   Copyright © 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef PUISSANCE4_TCPACCEPTOR_H
#define PUISSANCE4_TCPACCEPTOR_H


#include <string>
#include <netinet/in.h>
#include "TCPStream.h"

using namespace std;

class TCPAcceptor : Net{
   int m_lsd;
//    uint16_t m_port;
//    string m_address;
    bool m_listening;

public:
    TCPAcceptor(uint16_t port, const char *address = "");

    ~TCPAcceptor();

    int start();

    TCPStream *accept();

    TCPAcceptor();

private:

};

#endif //PUISSANCE4_TCPACCEPTOR_H