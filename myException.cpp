//
// Created by kardudu on 10/11/15.
//

#include "myException.h"

SocketException::SocketException(std::string s ) : m_s (s ) {}

std::string SocketException::description() { return m_s; }