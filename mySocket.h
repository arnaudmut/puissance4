//
// Created by kardudu on 10/11/15.
//

#ifndef NETSOCKET_MYSOCKET_H
#define NETSOCKET_MYSOCKET_H

// Definition of the mySocket class

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>



const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;


class mySocket
{
public:
    mySocket();
    virtual ~mySocket();

    // Server initialization
    bool create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( mySocket & ) const;

    // Client initialization
    bool connect ( const std::string host, const int port );

    // Data Transimission
    bool send ( const std::string ) const;
    int recv ( std::string& ) const;


    void set_non_blocking ( const bool );

    bool is_valid() const { return m_sock != -1; }

private:

    int m_sock;
    sockaddr_in m_addr;


};
#endif //NETSOCKET_MYSOCKET_H
