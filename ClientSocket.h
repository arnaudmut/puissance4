//
// Created by kardudu on 11/11/15.
//

#ifndef NETSOCKET_CLIENTSOCKET_H
#define NETSOCKET_CLIENTSOCKET_H


// Definition of the ClientSocket class

#include "mySocket.h"


class ClientSocket : private mySocket
{
public:

    ClientSocket ( std::string host, int port );
    virtual ~ClientSocket(){};

    const ClientSocket& operator << ( const std::string& ) const;
    const ClientSocket& operator >> ( std::string& ) const;

};
#endif //NETSOCKET_CLIENTSOCKET_H
