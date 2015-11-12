//
// Created by kardudu on 11/11/15.
//

// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "myException.h"


ClientSocket::ClientSocket ( std::string host, int port )
{
    if ( ! mySocket::create() )
    {
        throw SocketException ( "Could not create client socket." );
    }

    if ( ! mySocket::connect (host, port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }

}


const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    if ( ! mySocket::send (s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! mySocket::recv (s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}