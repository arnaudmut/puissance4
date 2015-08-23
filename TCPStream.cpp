/*
Created by kardudu on 10/07/15.

   TCPStream.h

   TCPStream class definition. TCPStream provides methods to trasnfer
   data between peers over a TCP/IP connection.

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

#include <arpa/inet.h>
#include "TCPStream.h"


TCPStream::TCPStream(int sd, struct sockaddr_in *address) : Net(sd,address) {
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip)-1);
    m_peerIP = ip;
    m_peerPort = ntohs(address->sin_port);
}

TCPStream::~TCPStream() {
    close(Net::m_sd);
}

ssize_t TCPStream::send(const char *buffer, size_t len) {
    return write(Net::m_sd, buffer, len);
}

ssize_t TCPStream::receive(char *buffer, size_t len, int timeout) {
    if (timeout <= 0) return read(m_sd, buffer, len);

    return waitForReadEvent(timeout) ? read(m_sd, buffer, len) : connectionTimedOut;

}

std::string TCPStream::getPeerIP() {
    return m_peerIP;
}

int TCPStream::getPeerPort() {
    return m_peerPort;
}

bool TCPStream::waitForReadEvent(int timeout) {
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(m_sd, &sdset);
    return select(m_sd + 1, &sdset, NULL, NULL, &tv) > 0;
}
