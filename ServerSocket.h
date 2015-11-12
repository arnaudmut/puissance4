//
// Created by kardudu on 11/11/15.
//

#ifndef NETSOCKET_SERVERSOCKET_H
#define NETSOCKET_SERVERSOCKET_H


// Definition of the ServerSocket class

#include "mySocket.h"


class ServerSocket : private mySocket
{
public:


    ServerSocket ( int port );
    ServerSocket (){};
    virtual ~ServerSocket();

    const ServerSocket& operator << ( const std::string& ) const;
    const ServerSocket& operator >> ( std::string& ) const;

    void accept ( ServerSocket& );

};
#endif //NETSOCKET_SERVERSOCKET_H
