//
// Created by kardudu on 11/11/15.
//

#include "ServerSocket.h"
// Implementation of the ServerSocket class
#include "myException.h"



ServerSocket::ServerSocket ( int port )
{
    if ( ! mySocket::create() )
    {
        throw SocketException ( "Could not create server socket." );
    }

    if ( ! mySocket::bind (port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }

    if ( ! mySocket::listen() )
    {
        throw SocketException ( "Could not listen to socket." );
    }

}

ServerSocket::~ServerSocket()
{
}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
    if ( ! mySocket::send (s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
    if ( ! mySocket::recv (s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}

void ServerSocket::accept ( ServerSocket& sock )
{
    if ( ! mySocket::accept (sock ) )
    {
        throw SocketException ( "Could not accept socket." );
    }
    else{
        std::cout <<"serv accept...."<<std::endl;
    }
}