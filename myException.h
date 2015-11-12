//
// Created by kardudu on 10/11/15.
//

#ifndef NETSOCKET_MYEXCEPTION_H
#define NETSOCKET_MYEXCEPTION_H

#include <string>

class SocketException
{
public:
    SocketException(std::string s );;
    ~SocketException (){};

    std::string description();

private:

    std::string m_s;

};
#endif //NETSOCKET_MYEXCEPTION_H
