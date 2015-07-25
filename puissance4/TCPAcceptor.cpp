//
// Created by kardudu on 11/07/15.
//

/*
   TCPAcceptor.cpp

   TCPAcceptor class definition. TCPAcceptor provides methods to passively
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

#include <cstdio>
#include <cstring>
#include <iostream>
#include "TCPAcceptor.h"
#ifdef __unix__
#include <arpa/inet.h>


TCPAcceptor::TCPAcceptor(uint16_t port, const char *address)
        : Net() {port,address, m_lsd =0, m_listening= false;}

TCPAcceptor::TCPAcceptor() : Net(),m_lsd(0), m_listening(false){}

TCPAcceptor::~TCPAcceptor() {
    if (m_lsd > 0) {
        close(m_lsd);
    }
}

int TCPAcceptor::start() {
    if (m_listening) {
        return 0;
    }

    m_lsd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(m_port);
    if (m_address.size() > 0) {
        std::cout << "madress : " + m_address <<std::endl;
        inet_pton(PF_INET, m_address.c_str(), &(address.sin_addr));
    }
    else {
        std::cout << "madress"<<std::endl;
        address.sin_addr.s_addr = INADDR_ANY;
    }

    int optval = 1;
    setsockopt(m_lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    int result = bind(m_lsd, (struct sockaddr *) &address, sizeof(address));
    if (result != 0) {
        perror("bind() failed");
        return result;
    }

    result = listen(m_lsd, 5);
    if (result != 0) {
        perror("listen() failed");
        return result;
    }
    m_listening = true;
    std::cout << "adresse : " << inet_ntoa(address.sin_addr);
    std::cout << " port :" << ntohs(address.sin_port) << std::endl;
    std::cout<< m_listening<<std::endl;
    return result;
}

TCPStream *TCPAcceptor::accept() {
    if (!m_listening) {
        return NULL;
    }

    struct sockaddr_in address;
    socklen_t len = sizeof(address);
    memset(&address, 0, sizeof(address));
    int sd = ::accept(m_lsd, (struct sockaddr *) &address, &len);
    if (sd < 0) {
        perror("accept() failed");
        return NULL;
    }
    return new TCPStream(sd, &address);
}
#endif
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h> //inet_pton
WSADATA WSAData;

TCPAcceptor::TCPAcceptor(uint16_t port, const char *address)
: Net() {
	port, address, m_lsd = 0, m_listening = false;
}

TCPAcceptor::TCPAcceptor() : Net(), m_lsd(0), m_listening(false){}

TCPAcceptor::~TCPAcceptor() {
	if (m_lsd > 0) {
		closesocket(m_lsd);
		WSACleanup();
	}
}

int TCPAcceptor::start() {
	if (m_listening) {
		return 0;
	}

	m_lsd = socket(PF_INET, SOCK_STREAM, 0);
	if (m_lsd == SOCKET_ERROR) {
		perror("erreur creation socket : ");
		exit(1);
	}
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = PF_INET;
	address.sin_port = htons(m_port);
	if (m_address.size() > 0) {
		std::cout << "madress : " + m_address << std::endl;
		inet_pton(PF_INET, m_address.c_str(), &(address.sin_addr));
	}
	else {
		std::cout << "madress" << std::endl;
		address.sin_addr.s_addr = INADDR_ANY;
	}

	int optval = 1;
	setsockopt(m_lsd, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof optval);

	int result = bind(m_lsd, (struct sockaddr *) &address, sizeof(address));
	if (result !=0) {
		perror("bind() failed");
		return result;
	}

	result = listen(m_lsd, 5);
	if (result != 0) {
		perror("listen() failed");
		return result;
	}
	m_listening = true;
	char ip[INET_ADDRSTRLEN];
	std::cout << "adresse : " << inet_ntop(AF_INET,&(address.sin_addr),ip,INET_ADDRSTRLEN);
	std::cout << " port :" << ntohs(address.sin_port) << std::endl;
	std::cout << m_listening << std::endl;
	return result;
}

TCPStream *TCPAcceptor::accept() {
	if (!m_listening) {
		return nullptr;
	}

	struct sockaddr_in address;
	socklen_t len = sizeof(address);
	memset(&address, 0, sizeof(address));
	int sd = ::accept(m_lsd, (struct sockaddr *) &address, &len);
	if (sd < 0) {
		perror("accept() failed");
		return nullptr;
	}
	return new TCPStream(sd, &address);
}
#endif

