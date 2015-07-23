//
// Created by kardudu on 13/07/15.
//

#ifndef PUISSANCE4_NET_H
#define PUISSANCE4_NET_H
#include <string>
#ifdef __unix__
#include <netinet/in.h>
#include <arpa/inet.h>

class Net {

protected:
    int m_sd;
    uint16_t m_port ;
    std::string m_address;

public:



protected:
    Net();
   // Net(uint16_t port, std::string address){};
    Net(int sd, struct sockaddr_in *address);//TCPStream

    Net(int sd);
};

#endif
#ifdef _WIN32
using uint16_t = _Uint32t;

class Net {

protected:
	int m_sd;
	uint16_t m_port;
	std::string m_address;

public:



protected:
	Net();
	// Net(uint16_t port, std::string address){};
	Net(int sd, struct sockaddr_in *address);//TCPStream

	Net(int sd);
};
#endif //_WIN32

#endif //PUISSANCE4_NET_H
